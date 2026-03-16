/**
 * @file child_lock_system.h
 * @brief 하이브리드 차일드 락 제어 시스템 (0~3단계 최종 통합본)
 */

#ifndef CHILD_LOCK_SYSTEM_H
#define CHILD_LOCK_SYSTEM_H

typedef enum { DOOR_LEFT = 0, DOOR_RIGHT = 1, DOOR_MAX } DoorIndex;
typedef enum { STATUS_UNLOCKED = 0, STATUS_LOCKED = 1 } LockStatus;
typedef enum { LOCK_CMD_RELEASE = 0, LOCK_CMD_SET = 1 } LockCommand;
typedef enum { DOOR_CLOSED = 0, DOOR_OPENED = 1 } DoorPhysicalState;

// [0단계] 기본 제어
void initialize_system(void);
void process_master_button_event(LockCommand cmd);
void process_detail_control_event(DoorIndex door, LockCommand cmd);
LockStatus get_door_status(DoorIndex door);

// [1~2단계] 속도 및 HMI 시각화
void set_vehicle_speed(int speed);
void update_hmi_display(void);
void process_detail_control_event_with_safety(DoorIndex door, LockCommand cmd);

// [3단계] 하드웨어 연동 및 긴급 로직
void set_door_physical_state(DoorIndex door, DoorPhysicalState state);
void trigger_emergency_unlock(void); // 충돌 시 강제 해제

#endif
