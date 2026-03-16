/**
 * @file advanced_sea.c
 * @brief Advanced SEA unlock protection implementation.
 * @date 2026-03-16
 * @note Implemented by OpenAI Codex GPT-5.
 */

#include "advanced_sea.h"

enum {
    ADVANCED_SEA_DANGER_SPEED_KPH = 20
};

/**
 * @brief Builds the default safe response.
 * @param output Output object that receives the default values.
 * @return None.
 * @date 2026-03-16
 * @note Implemented by OpenAI Codex GPT-5.
 */
static void set_safe_output(AdvancedSeaOutput *output)
{
    output->keep_locked = false;
    output->unlock_allowed = true;
    output->cluster_warning = false;
    output->audible_warning = false;
}

/**
 * @brief Checks whether the detected object should be treated as dangerous.
 * @param input Input signal bundle for the current request.
 * @return true if danger is detected, otherwise false.
 * @date 2026-03-16
 * @note Implemented by OpenAI Codex GPT-5.
 */
static bool is_danger_detected(const AdvancedSeaInput *input)
{
    return input->object_detected &&
           input->object_speed_kph >= ADVANCED_SEA_DANGER_SPEED_KPH;
}

int advanced_sea_get_danger_speed_threshold(void)
{
    return ADVANCED_SEA_DANGER_SPEED_KPH;
}

void advanced_sea_evaluate(
    const AdvancedSeaInput *input,
    AdvancedSeaOutput *output
)
{
    if (input == 0 || output == 0) {
        return;
    }

    set_safe_output(output);

    if (!input->unlock_request) {
        return;
    }

    if (!input->child_lock_enabled) {
        return;
    }

    if (!is_danger_detected(input)) {
        return;
    }

    output->keep_locked = true;
    output->unlock_allowed = false;
    output->cluster_warning = true;
    output->audible_warning = true;
}
