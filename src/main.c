#include <stdio.h>
#include "active_rescue.h"

// 운영체제(OS)에 따른 헤더 및 Sleep 함수 분기 처리
#ifdef _WIN32
    #include <windows.h>
    #define DELAY_1SEC() Sleep(1000) // 윈도우는 밀리초 단위
    #define DELAY_2SEC() Sleep(2000)
#else
    #include <unistd.h>
    #define DELAY_1SEC() sleep(1)    // 리눅스는 초 단위
    #define DELAY_2SEC() sleep(2)
#endif

int main() {
    // 터미널 한글 깨짐 방지는 윈도우 환경에서만 실행
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif

    RescueState currentState = STATE_IDLE;
    
    // 초기 센서 상태 세팅
    SensorData currentSensors = {
        .engineOff = true,
        .driverAway = true,
        .temperature = 25,
        .abnormalBreathing = false,
        .qrScanned = false,
        .authSuccess = false
    };

    printf("=== UC-02 생체신호 연동 비상 대응 시스템 시뮬레이션 ===\n");

    while (currentState != STATE_RESCUED) {
        runSystem(&currentState, &currentSensors);

        if (currentState == STATE_MONITORING) {
            printf("[센서] 현재 실내 온도: %d도\n", currentSensors.temperature);
            currentSensors.temperature += 5; 
        } 
        else if (currentState == STATE_WAIT_SCAN) {
            DELAY_2SEC(); 
            currentSensors.qrScanned = true;
            currentSensors.authSuccess = true;
        }

        DELAY_1SEC();
    }

    printf("=== 구조 완료! 시스템 종료 ===\n");

    return 0;
}