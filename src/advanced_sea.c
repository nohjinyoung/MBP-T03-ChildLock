/**
 * @file advanced_sea.c
 * @brief 지능형 하차 보조(Advanced SEA) 잠금 유지 로직 구현부
 * @date 2026-03-16
 * @note Implemented by OpenAI Codex GPT-5
 */

#include "advanced_sea.h"

enum {
    ADVANCED_SEA_DANGER_SPEED_KPH = 20
};

/**
 * @brief 기본 안전 상태의 출력값을 설정
 * @param output 기본값을 기록할 출력 구조체
 * @return 없음
 * @date 2026-03-16
 * @note Implemented by OpenAI Codex GPT-5
 */
static void set_safe_output(AdvancedSeaOutput *output)
{
    output->keep_locked = false;
    output->unlock_allowed = true;
    output->cluster_warning = false;
    output->audible_warning = false;
}

/**
 * @brief 감지된 물체를 위험 접근으로 볼지 판단
 * @param input 현재 잠금 해제 요청에 대한 입력 신호
 * @return 위험 상황이면 true, 아니면 false
 * @date 2026-03-16
 * @note Implemented by OpenAI Codex GPT-5
 */
static bool is_danger_detected(const AdvancedSeaInput *input)
{
    return input->object_detected &&
           input->object_speed_kph >= ADVANCED_SEA_DANGER_SPEED_KPH;
}

/**
 * @brief 위험 접근 속도 기준값을 반환
 * @param 없음
 * @return 위험 속도 기준값(km/h)
 * @date 2026-03-16
 * @note Implemented by OpenAI Codex GPT-5
 */
int advanced_sea_get_danger_speed_threshold(void)
{
    return ADVANCED_SEA_DANGER_SPEED_KPH;
}

/**
 * @brief 잠금 해제 요청을 차단해야 하는지 평가
 * @param input 현재 잠금 해제 요청에 대한 입력 신호
 * @param output 판단 결과를 기록할 출력 구조체
 * @return 없음
 * @date 2026-03-16
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
