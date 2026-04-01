/**
 * @file test_advanced_sea.c
 * @brief C-based unit tests for UC-01 Advanced SEA.
 * @date 2026-04-01
 * @note Implemented by OpenAI Codex GPT-5
 */

#include <stdbool.h>
#include <stdio.h>

#include "advanced_sea.h"

/**
 * @brief Record a test failure when the condition is false.
 * @param condition Condition to validate.
 * @param message Message printed on failure.
 * @return 0 on success, 1 on failure.
 * @date 2026-04-01
 * @note Implemented by OpenAI Codex GPT-5
 */
static int expect_true(bool condition, const char *message)
{
    if (condition) {
        return 0;
    }

    printf("[FAIL] %s\n", message);
    return 1;
}

/**
 * @brief Verify that the output remains in the default non-blocking state.
 * @param output Output structure to validate.
 * @return Number of failures detected.
 * @date 2026-04-01
 * @note Implemented by OpenAI Codex GPT-5
 */
static int expect_default_output(const AdvancedSeaOutput *output)
{
    int failures = 0;

    failures += expect_true(!output->keep_locked, "keep_locked should be false");
    failures += expect_true(output->unlock_allowed, "unlock_allowed should be true");
    failures += expect_true(!output->cluster_warning, "cluster_warning should be false");
    failures += expect_true(!output->audible_warning, "audible_warning should be false");
    return failures;
}

/**
 * @brief Verify that the output blocks unlocking because of a hazard.
 * @param output Output structure to validate.
 * @return Number of failures detected.
 * @date 2026-04-01
 * @note Implemented by OpenAI Codex GPT-5
 */
static int expect_hazard_block_output(const AdvancedSeaOutput *output)
{
    int failures = 0;

    failures += expect_true(output->keep_locked, "keep_locked should be true");
    failures += expect_true(!output->unlock_allowed, "unlock_allowed should be false");
    failures += expect_true(output->cluster_warning, "cluster_warning should be true");
    failures += expect_true(output->audible_warning, "audible_warning should be true");
    return failures;
}

/**
 * @brief Verify the fail-safe output for a sensor diagnostic fault.
 * @param output Output structure to validate.
 * @return Number of failures detected.
 * @date 2026-04-01
 * @note Implemented by OpenAI Codex GPT-5
 */
static int expect_sensor_fault_output(const AdvancedSeaOutput *output)
{
    int failures = 0;

    failures += expect_true(output->keep_locked, "sensor fault should keep the lock");
    failures += expect_true(!output->unlock_allowed, "sensor fault should block unlock");
    failures += expect_true(output->cluster_warning, "sensor fault should raise cluster warning");
    failures += expect_true(!output->audible_warning, "sensor fault should not force audible warning");
    return failures;
}

/**
 * @brief Verify that non-hazard cases keep the default output.
 * @param None.
 * @return Number of failures detected.
 * @date 2026-04-01
 * @note Implemented by OpenAI Codex GPT-5
 */
static int test_safe_cases_keep_default_output(void)
{
    const AdvancedSeaInput no_hazard = { true, true, false, 0, false };
    const AdvancedSeaInput child_lock_off = { false, true, true, 40, false };
    const AdvancedSeaInput no_request = { true, false, true, 100, false };
    AdvancedSeaOutput output = { false, false, false, false };
    int failures = 0;

    advanced_sea_evaluate(&no_hazard, &output);
    failures += expect_default_output(&output);

    advanced_sea_evaluate(&child_lock_off, &output);
    failures += expect_default_output(&output);

    advanced_sea_evaluate(&no_request, &output);
    failures += expect_default_output(&output);
    return failures;
}

/**
 * @brief Verify that a dangerous approach blocks the unlock request.
 * @param None.
 * @return Number of failures detected.
 * @date 2026-04-01
 * @note Implemented by OpenAI Codex GPT-5
 */
static int test_keeps_lock_when_fast_object_approaches(void)
{
    const AdvancedSeaInput input = {
        true,
        true,
        true,
        advanced_sea_get_danger_speed_threshold(),
        false
    };
    AdvancedSeaOutput output = { false, false, false, false };

    advanced_sea_evaluate(&input, &output);
    return expect_hazard_block_output(&output);
}

/**
 * @brief Verify the threshold boundary around dangerous approach speed.
 * @param None.
 * @return Number of failures detected.
 * @date 2026-04-01
 * @note Implemented by OpenAI Codex GPT-5
 */
static int test_threshold_boundary_behavior(void)
{
    const int threshold = advanced_sea_get_danger_speed_threshold();
    const AdvancedSeaInput below_threshold = { true, true, true, threshold - 1, false };
    const AdvancedSeaInput at_threshold = { true, true, true, threshold, false };
    AdvancedSeaOutput output = { false, false, false, false };
    int failures = 0;

    advanced_sea_evaluate(&below_threshold, &output);
    failures += expect_default_output(&output);

    advanced_sea_evaluate(&at_threshold, &output);
    failures += expect_hazard_block_output(&output);
    return failures;
}

/**
 * @brief Verify that a sensor diagnostic fault triggers the safe state.
 * @param None.
 * @return Number of failures detected.
 * @date 2026-04-01
 * @note Implemented by OpenAI Codex GPT-5
 */
static int test_sensor_fault_enters_safe_state(void)
{
    const AdvancedSeaInput input = { true, true, false, 0, true };
    AdvancedSeaOutput output = { false, true, false, true };

    advanced_sea_evaluate(&input, &output);
    return expect_sensor_fault_output(&output);
}

/**
 * @brief Verify that null pointers do not modify the existing output.
 * @param None.
 * @return Number of failures detected.
 * @date 2026-04-01
 * @note Implemented by OpenAI Codex GPT-5
 */
static int test_null_input_does_not_change_output(void)
{
    AdvancedSeaOutput output = { true, false, true, false };

    advanced_sea_evaluate(0, &output);

    return expect_true(output.keep_locked, "null input should not modify output");
}

/**
 * @brief Entry point for the UC-01 unit tests.
 * @param None.
 * @return 0 on success, 1 on failure.
 * @date 2026-04-01
 * @note Implemented by OpenAI Codex GPT-5
 */
int main(void)
{
    int failures = 0;

    printf("=== UC-01 Advanced SEA unit test start ===\n");
    failures += test_safe_cases_keep_default_output();
    failures += test_keeps_lock_when_fast_object_approaches();
    failures += test_threshold_boundary_behavior();
    failures += test_sensor_fault_enters_safe_state();
    failures += test_null_input_does_not_change_output();

    if (failures != 0) {
        printf("=== Advanced SEA unit test failed: %d issue(s) ===\n", failures);
        return 1;
    }

    printf("=== Advanced SEA unit test passed ===\n");
    return 0;
}
