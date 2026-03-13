#include <stdio.h>
#include <windows.h> // Sleep 함수 사용 (리눅스의 경우 <unistd.h> 추가)
#include "active_rescue.h"

int main() {
    SetConsoleOutputCP(CP_UTF8);

    RescueState currentState = STATE_IDLE;
    
    // 초기 센서 상태 세팅 (시나리오: 시동 OFF, 운전자 이탈)
    SensorData currentSensors = {
        .engineOff = true,
        .driverAway = true,
        .temperature = 25,
        .abnormalBreathing = false,
        .qrScanned = false,
        .authSuccess = false
    };

    printf("=== UC-02 생체신호 연동 비상 대응 시스템 시뮬레이션 ===\n");

    // 시스템 무한 루프 (실제 차량 제어기처럼 동작)
    while (currentState != STATE_RESCUED) {
        // 상태별 로직 실행
        runSystem(&currentState, &currentSensors);

        // 시나리오 시뮬레이션을 위한 데이터 변경 (시간 경과 가정)
        if (currentState == STATE_MONITORING) {
            printf("[센서] 현재 실내 온도: %d도\n", currentSensors.temperature);
            currentSensors.temperature += 5; // 온도가 점점 오르는 상황 가정
        } 
        else if (currentState == STATE_WAIT_SCAN) {
            // 구조자가 접근하여 QR을 스캔하고 인증에 성공한 상황 가정
            Sleep(2000); 
            currentSensors.qrScanned = true;
            currentSensors.authSuccess = true;
        }

        Sleep(1000); // 1초 대기
    }

    printf("=== 구조 완료! 시스템 종료 ===\n");

    return 0;
}