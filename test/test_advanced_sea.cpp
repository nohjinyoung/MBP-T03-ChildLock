/**
 * @file test_advanced_sea.cpp
 * @brief Google Test cases for the Advanced SEA use case.
 * @date 2026-03-16
 * @note Implemented by OpenAI Codex GPT-5.
 */

#include <gtest/gtest.h>

#include "advanced_sea.h"

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
