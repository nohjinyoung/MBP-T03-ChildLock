#include <stdio.h>
#include "active_rescue.h"

int main() {
    printf("=== UC-02 생체신호 연동 비상 대응 단위 테스트 시작 ===\n");
    
    RescueState state = STATE_IDLE;
    SensorData sensors = { 
        .engineOff = true, .driverAway = true, 
        .temperature = 25, .abnormalBreathing = false, 
        .qrScanned = false, .authSuccess = false 
    };

    // 1. 대기 -> 모니터링 상태 전환 테스트
    runSystem(&state, &sensors);
    if (state != STATE_MONITORING) return 1; // 테스트 실패 시 1 반환 (CI 실패 처리)

    // 2. 위험 감지 (온도 상승) -> 구조 모드 전환 테스트
    sensors.temperature = 36; 
    runSystem(&state, &sensors);
    if (state != STATE_ACTIVE_RESCUE) return 1;

    // 3. 구조 액션 실행 -> 스캔 대기 상태 전환 테스트
    runSystem(&state, &sensors);
    if (state != STATE_WAIT_SCAN) return 1;

    // 4. 구조자 접근 및 스캔 (인증 실패 케이스) -> 대기 유지
    sensors.qrScanned = true;
    sensors.authSuccess = false;
    runSystem(&state, &sensors);
    if (state != STATE_WAIT_SCAN) return 1;

    // 5. 구조자 인증 성공 -> 구조 완료 상태 전환 테스트
    sensors.qrScanned = true;
    sensors.authSuccess = true;
    runSystem(&state, &sensors);
    if (state != STATE_RESCUED) return 1;

    // 6. 구조 완료 후 메시지 출력 로직 커버리지 충족
    runSystem(&state, &sensors);

    printf("=== 단위 테스트 모두 통과 (Coverage 100%% 예상) ===\n");
    return 0; // 0 반환 시 CTest(CI) 성공 처리됨
}