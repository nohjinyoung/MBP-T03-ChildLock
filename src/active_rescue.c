#include <stdio.h>
#include "active_rescue.h"

// --- [보조 함수들] ---

// 1. 센서 값을 읽기만 하므로 안전을 위해 const 추가
static void handleStateIdle(RescueState *state, const SensorData *sensors) {
    if (sensors->engineOff && sensors->driverAway) {
        printf("[시스템] 선행 조건 만족. 실내 모니터링을 시작합니다.\n");
        *state = STATE_MONITORING;
    }
}

// 2. 센서 값을 읽기만 하므로 안전을 위해 const 추가
static void handleStateMonitoring(RescueState *state, const SensorData *sensors) {
    if (sensors->temperature >= 35 || sensors->abnormalBreathing) {
        *state = STATE_ACTIVE_RESCUE;
    }
}

// 3. 여기서는 센서 값을 변경(qrScanned = false)하므로 const를 붙이지 않음!
static void handleStateWaitScan(RescueState *state, SensorData *sensors) {
    if (sensors->qrScanned) {
        printf("\n[시스템] 외부 구조자 QR 스캔 감지. 인증을 시도합니다...\n");
        if (sensors->authSuccess) {
            printf("[시스템] 인증 성공! 도어 잠금을 강제 해제(Unlock)합니다.\n");
            *state = STATE_RESCUED;
        } else {
            printf("[시스템] 인증 실패! 구조용 QR을 다시 스캔해 주세요.\n");
            sensors->qrScanned = false; // 재스캔 대기
        }
    }
}

void executeRescueActions() {
    printf("\n[경고] 위험 상황 감지! 능동적 구조 모드를 실행합니다.\n");
    printf(" 1. [윈도우 제어] 창문 일부 개방 (환기 진행)\n");
    printf(" 2. [알림 제어] 비상등 점멸 및 경적 작동\n");
    printf(" 3. [디스플레이 제어] B필러 디스플레이 구조용 QR/NFC 활성화\n");
}


// --- [메인 함수] ---

void runSystem(RescueState *state, SensorData *sensors) {
    switch (*state) {
        case STATE_IDLE:
            handleStateIdle(state, sensors);
            break;

        case STATE_MONITORING:
            handleStateMonitoring(state, sensors);
            break;

        case STATE_ACTIVE_RESCUE:
            executeRescueActions();
            *state = STATE_WAIT_SCAN;
            break;

        case STATE_WAIT_SCAN:
            handleStateWaitScan(state, sensors);
            break;

        case STATE_RESCUED:
            printf("[시스템] 도어 개방 완료. 승객 구조가 진행 중입니다. (시스템 종료)\n");
            break;
    }
}