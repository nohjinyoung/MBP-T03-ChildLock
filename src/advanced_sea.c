/**
 * @file advanced_sea.c
 * @brief Implementation of UC-01 Advanced SEA lock override logic.
 * @date 2026-04-01
 * @note Implemented by OpenAI Codex GPT-5
 */

#include "advanced_sea.h"

enum {
    ADVANCED_SEA_DANGER_SPEED_KPH = 20
};

/**
 * @brief Set the default safe output when no hazard is active.
 * @param output Output structure to initialize.
 * @return None.
 * @date 2026-04-01
 * @note Implemented by OpenAI Codex GPT-5
 */
static void set_default_output(AdvancedSeaOutput *output)
{
    output->keep_locked = false;
    output->unlock_allowed = true;
    output->cluster_warning = false;
    output->audible_warning = false;
}

/**
 * @brief Set the output for a detected rear-side hazard.
 * @param output Output structure to update.
 * @return None.
 * @date 2026-04-01
 * @note Implemented by OpenAI Codex GPT-5
 */
static void set_hazard_block_output(AdvancedSeaOutput *output)
{
    output->keep_locked = true;
    output->unlock_allowed = false;
    output->cluster_warning = true;
    output->audible_warning = true;
}

/**
 * @brief Set the fail-safe output for a sensor diagnostic fault.
 * @param output Output structure to update.
 * @return None.
 * @date 2026-04-01
 * @note Implemented by OpenAI Codex GPT-5
 */
static void set_sensor_fault_output(AdvancedSeaOutput *output)
{
    output->keep_locked = true;
    output->unlock_allowed = false;
    output->cluster_warning = true;
    output->audible_warning = false;
}

/**
 * @brief Check whether the detected object is a dangerous approach.
 * @param input Current input signals for the unlock request.
 * @return true when a dangerous approach is detected, otherwise false.
 * @date 2026-04-01
 * @note Implemented by OpenAI Codex GPT-5
 */
static bool is_danger_detected(const AdvancedSeaInput *input)
{
    return input->object_detected &&
           input->object_speed_kph >= ADVANCED_SEA_DANGER_SPEED_KPH;
}

/**
 * @brief Return the dangerous approach threshold used by UC-01.
 * @param None.
 * @return Dangerous approach threshold in km/h.
 * @date 2026-04-01
 * @note Implemented by OpenAI Codex GPT-5
 */
int advanced_sea_get_danger_speed_threshold(void)
{
    return ADVANCED_SEA_DANGER_SPEED_KPH;
}

/**
 * @brief Evaluate whether Advanced SEA must override the unlock request.
 * @param input Current input signals for the unlock request.
 * @param output Output structure that receives the decision result.
 * @return None.
 * @date 2026-04-01
 * @note Implemented by OpenAI Codex GPT-5
 */
void advanced_sea_evaluate(
    const AdvancedSeaInput *input,
    AdvancedSeaOutput *output
)
{
    if (input == 0 || output == 0) {
        return;
    }

    set_default_output(output);

    if (input->sensor_fault) {
        set_sensor_fault_output(output);
        return;
    }

    if (!input->unlock_request) {
        return;
    }

    if (!input->child_lock_enabled) {
        return;
    }

    if (!is_danger_detected(input)) {
        return;
    }

    set_hazard_block_output(output);
}
