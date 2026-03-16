/**
 * @file advanced_sea.h
 * @brief Public interface for the Advanced SEA unlock protection logic.
 * @date 2026-03-16
 * @note Implemented by OpenAI Codex GPT-5.
 */

#ifndef ADVANCED_SEA_H
#define ADVANCED_SEA_H

#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Input signals needed to evaluate an unlock request.
 * @param child_lock_enabled Child lock feature enable state.
 * @param unlock_request Driver unlock button request state.
 * @param object_detected Rear-side radar detection state.
 * @param object_speed_kph Approaching object speed in km/h.
 * @return None.
 * @date 2026-03-16
 * @note Implemented by OpenAI Codex GPT-5.
 */
typedef struct {
    bool child_lock_enabled;
    bool unlock_request;
    bool object_detected;
    int object_speed_kph;
} AdvancedSeaInput;

/**
 * @brief Result of the Advanced SEA evaluation.
 * @param keep_locked Whether the system must keep the lock engaged.
 * @param unlock_allowed Whether the unlock request is accepted.
 * @param cluster_warning Whether the cluster popup should be shown.
 * @param audible_warning Whether the warning buzzer should sound.
 * @return None.
 * @date 2026-03-16
 * @note Implemented by OpenAI Codex GPT-5.
 */
typedef struct {
    bool keep_locked;
    bool unlock_allowed;
    bool cluster_warning;
    bool audible_warning;
} AdvancedSeaOutput;

/**
 * @brief Returns the danger speed threshold used by the module.
 * @param None.
 * @return Danger threshold in km/h.
 * @date 2026-03-16
 * @note Implemented by OpenAI Codex GPT-5.
 */
int advanced_sea_get_danger_speed_threshold(void);

/**
 * @brief Evaluates whether an unlock request should be blocked.
 * @param input Input signal bundle for the current request.
 * @param output Evaluation result written by the module.
 * @return None.
 * @date 2026-03-16
 * @note Implemented by OpenAI Codex GPT-5.
 */
void advanced_sea_evaluate(
    const AdvancedSeaInput *input,
    AdvancedSeaOutput *output
);

#ifdef __cplusplus
}
#endif

#endif
