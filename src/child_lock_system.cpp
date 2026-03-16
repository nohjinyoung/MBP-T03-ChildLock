/**
 * @file child_lock_system.cpp
 * @brief 하이브리드 차일드 락 제어 시스템 최종 통합 구현부
 */

#include "child_lock_system.h"
#include <stdio.h>

// 내부 상태 관리 변수
static LockStatus g_door_locks[DOOR_MAX];
static DoorPhysicalState g_door_physical[DOOR_MAX]; 
static int g_vehicle_speed = 0;

/** [0단계] 시스템 초기화 */
void initialize_system(void) {
    for (int i = 0; i < DOOR_MAX; i++) {
        g_door_locks[i] = STATUS_UNLOCKED;
        g_door_physical[i] = DOOR_CLOSED; 
    }
    printf("[SYS] 시스템 초기화 완료.\n");
}

/** [2단계] HMI 상태 업데이트 (로그 출력) */
void update_hmi_display(void) {
    printf("[HMI] 계기판 -> L:%s(%s) | R:%s(%s) | Speed:%dkm/h\n",
        (g_door_locks[DOOR_LEFT] == STATUS_LOCKED ? "LOCKED" : "OFF"),
        (g_door_physical[DOOR_LEFT] == DOOR_OPENED ? "OPEN" : "CLOSE"),
        (g_door_locks[DOOR_RIGHT] == STATUS_LOCKED ? "LOCKED" : "OFF"),
        (g_door_physical[DOOR_RIGHT] == DOOR_OPENED ? "OPEN" : "CLOSE"),
        g_vehicle_speed);
}

/** [0&3단계] 마스터 버튼 제어 (문 열림 체크 포함) */
void process_master_button_event(LockCommand cmd) {
    for (int i = 0; i < DOOR_MAX; i++) {
        // 문이 열려있을 때 잠금 명령이 들어오면 해당 도어는 무시
        if (cmd == LOCK_CMD_SET && g_door_physical[i] == DOOR_OPENED) {
            printf("[WARN] 도어 %d번 열림 감지: 잠금 명령을 수행하지 않습니다.\n", i);
            continue;
        }
        g_door_locks[i] = (LockStatus)cmd;
    }
    update_hmi_display();
}

/** [0단계] 개별 도어 제어 */
void process_detail_control_event(DoorIndex door, LockCommand cmd) {
    if (door < DOOR_MAX) {
        g_door_locks[door] = (LockStatus)cmd;
        update_hmi_display();
    }
}

/** [1단계] 차량 속도 설정 */
void set_vehicle_speed(int speed) {
    g_vehicle_speed = speed;
}

/** [1단계] 안전 로직 포함 개별 제어 */
void process_detail_control_event_with_safety(DoorIndex door, LockCommand cmd) {
    if (g_vehicle_speed > 20 && cmd == LOCK_CMD_RELEASE) {
        printf("[SAFETY] 주행 중 해제 불가! (속도: %dkm/h)\n", g_vehicle_speed);
        return;
    }
    process_detail_control_event(door, cmd);
}

/** [3단계] 도어 물리 상태 설정 */
void set_door_physical_state(DoorIndex door, DoorPhysicalState state) {
    if (door < DOOR_MAX) {
        g_door_physical[door] = state;
    }
}

/** [3단계] 긴급 충돌 해제 로직 */
void trigger_emergency_unlock(void) {
    printf("[EMERGENCY] 충돌 감지! 모든 도어 강제 해제.\n");
    for (int i = 0; i < DOOR_MAX; i++) {
        g_door_locks[i] = STATUS_UNLOCKED;
    }
    update_hmi_display();
}

/** 도어 상태 반환 */
LockStatus get_door_status(DoorIndex door) {
    return g_door_locks[door];
}
