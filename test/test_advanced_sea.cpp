/**
 * @file test_advanced_sea.cpp
 * @brief 지능형 하차 보조(Advanced SEA) Google Test 단위 테스트
 * @date 2026-03-16
 * @note Implemented by OpenAI Codex GPT-5
 */

#include <gtest/gtest.h>

#include "advanced_sea.h"

// 위험 물체가 감지되지 않을 때 잠금 해제가 허용되는지 검증
TEST(AdvancedSeaTest, AllowsUnlockWhenNoHazardIsDetected)
{
    const AdvancedSeaInput input = { true, true, false, 0 };
    AdvancedSeaOutput output = { false, false, false, false };

    advanced_sea_evaluate(&input, &output);

    EXPECT_TRUE(output.unlock_allowed);
    EXPECT_FALSE(output.keep_locked);
    EXPECT_FALSE(output.cluster_warning);
    EXPECT_FALSE(output.audible_warning);
}

// 고속 접근 물체가 감지되면 잠금이 유지되는지 검증
TEST(AdvancedSeaTest, KeepsLockWhenFastObjectApproaches)
{
    const AdvancedSeaInput input = {
        true,
        true,
        true,
        advanced_sea_get_danger_speed_threshold()
    };
    AdvancedSeaOutput output = { false, false, false, false };

    advanced_sea_evaluate(&input, &output);

    EXPECT_FALSE(output.unlock_allowed);
    EXPECT_TRUE(output.keep_locked);
    EXPECT_TRUE(output.cluster_warning);
    EXPECT_TRUE(output.audible_warning);
}

// 차일드 락이 꺼져 있으면 위험 감지와 무관하게 해제가 허용되는지 검증
TEST(AdvancedSeaTest, IgnoresHazardLogicWhenChildLockIsOff)
{
    const AdvancedSeaInput input = {
        false,
        true,
        true,
        advanced_sea_get_danger_speed_threshold() + 10
    };
    AdvancedSeaOutput output = { false, false, false, false };

    advanced_sea_evaluate(&input, &output);

    EXPECT_TRUE(output.unlock_allowed);
    EXPECT_FALSE(output.keep_locked);
}

// 잠금 해제 요청이 없으면 출력 상태가 기본값으로 유지되는지 검증
TEST(AdvancedSeaTest, DoesNothingWhenUnlockWasNotRequested)
{
    const AdvancedSeaInput input = { true, false, true, 100 };
    AdvancedSeaOutput output = { false, false, false, false };

    advanced_sea_evaluate(&input, &output);

    EXPECT_TRUE(output.unlock_allowed);
    EXPECT_FALSE(output.keep_locked);
    EXPECT_FALSE(output.cluster_warning);
    EXPECT_FALSE(output.audible_warning);
}
