#ifndef ACTIVE_RESCUE_H
#define ACTIVE_RESCUE_H

#include <stdbool.h>

// 시스템 상태 정의
typedef enum {
    STATE_IDLE,             // 대기 상태
    STATE_MONITORING,       // 승객 모니터링 상태
    STATE_ACTIVE_RESCUE,    // 능동적 구조 모드 상태
    STATE_WAIT_SCAN,        // QR 스캔 대기 상태
    STATE_RESCUED           // 구조 완료 상태
} RescueState;

// 가상의 차량 센서 데이터 구조체
typedef struct {
    bool engineOff;         // 시동 OFF 여부
    bool driverAway;        // 운전자 이석 여부
    int temperature;        // 실내 온도 (고체온 기준: 예 35도 이상)
    bool abnormalBreathing; // 이상 호흡 감지 여부
    bool qrScanned;         // QR 코드 스캔 여부
    bool authSuccess;       // 인증 성공 여부
} SensorData;

// 함수 원형 선언
void runSystem(RescueState *state, SensorData *sensors);

#endif