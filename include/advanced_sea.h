/**
 * @file advanced_sea.h
 * @brief 지능형 하차 보조(Advanced SEA) 잠금 유지 로직의 공개 인터페이스
 * @date 2026-03-16
 * @note Implemented by OpenAI Codex GPT-5
 */

#ifndef ADVANCED_SEA_H
#define ADVANCED_SEA_H

#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 잠금 해제 요청 판단에 필요한 입력 신호 집합
 * @param child_lock_enabled 차일드 락 활성화 상태
 * @param unlock_request 운전자 잠금 해제 버튼 입력 여부
 * @param object_detected 후측방 레이더의 접근 물체 감지 여부
 * @param object_speed_kph 접근 물체의 속도(km/h)
 * @return 없음
 * @date 2026-03-16
 * @note Implemented by OpenAI Codex GPT-5
 */
typedef struct {
    bool child_lock_enabled;
    bool unlock_request;
    bool object_detected;
    int object_speed_kph;
} AdvancedSeaInput;

/**
 * @brief 지능형 하차 보조 판단 결과
 * @param keep_locked 시스템이 강제로 잠금 상태를 유지해야 하는지 여부
 * @param unlock_allowed 잠금 해제 요청 허용 여부
 * @param cluster_warning 계기판 경고 팝업 표시 여부
 * @param audible_warning 경고음 출력 여부
 * @return 없음
 * @date 2026-03-16
 * @note Implemented by OpenAI Codex GPT-5
 */
typedef struct {
    bool keep_locked;
    bool unlock_allowed;
    bool cluster_warning;
    bool audible_warning;
} AdvancedSeaOutput;

/**
 * @brief 위험 접근으로 판단하는 속도 기준값을 반환
 * @param 없음
 * @return 위험 속도 기준값(km/h)
 * @date 2026-03-16
 * @note Implemented by OpenAI Codex GPT-5
 */
int advanced_sea_get_danger_speed_threshold(void);

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
);

#ifdef __cplusplus
}
#endif

#endif
