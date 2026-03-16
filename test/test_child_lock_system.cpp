/**
 * @file test.cpp
 * @brief Child Lock System 최종 통합 단위 테스트 (0~3단계)
 */

#include "pch.h"
#include "child_lock_system.h"

// 0~2단계 통합 테스트 (기존 유지)
TEST(ChildLockTest, Integrated_Step_0_1_2) {
    initialize_system();
    set_vehicle_speed(30);
    process_detail_control_event_with_safety(DOOR_LEFT, LOCK_CMD_RELEASE);
    EXPECT_EQ(get_door_status(DOOR_LEFT), STATUS_UNLOCKED); // 초기값 UNLOCKED 유지 확인
}

// 3단계 테스트: 도어 개폐 상태 및 긴급 상황
TEST(ChildLockTest, Step3_HardwareAndEmergencyTest) {
    initialize_system();

    // 시나리오 1: 문이 열린 상태에서 잠금 시도 (거부되어야 함)
    set_door_physical_state(DOOR_RIGHT, DOOR_OPENED);
    process_master_button_event(LOCK_CMD_SET);
    EXPECT_EQ(get_door_status(DOOR_RIGHT), STATUS_UNLOCKED); // 문이 열려있어 여전히 UNLOCKED

    // 시나리오 2: 긴급 상황 발생 (강제 해제)
    process_master_button_event(LOCK_CMD_SET); // 일단 잠금 가능한 문 다 잠금
    set_vehicle_speed(100); // 초고속 주행 중이라도
    trigger_emergency_unlock(); // 충돌 발생 시
    
    EXPECT_EQ(get_door_status(DOOR_LEFT), STATUS_UNLOCKED); // 모든 문이 열려야 함
}
