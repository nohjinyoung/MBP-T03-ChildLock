#ifndef CRASH_SAFETY_SYSTEM_HPP
#define CRASH_SAFETY_SYSTEM_HPP

#include <iomanip>
#include <iostream>
#include <string>

struct VehicleContext {
    std::string scenario_id;
    // 상황 A: 충돌 데이터
    bool airbag_signal;
    float accel_l;      // 단위: G
    float accel_r;      // 단위: G
    // 상황 B: 후방 감지 데이터
    bool rear_hazard;   // 접근 물체 유무
    float hazard_dist;  // 단위: m (미터)
    // 상황 C: 전원 데이터
    float main_vcc;     // 메인 전압 (정상: 12.0V~14.4V)
    float cap_voltage;  // 예비 커패시터 전압 (최소: 5.0V 이상 필요)
};

class CrashSafetySystem {
private:
    const float G_THRESHOLD = 15.0f;
    const float VOLTAGE_CRITICAL = 9.0f; // 메인 전원 상실 판단 기준
    const float CAP_MIN_REQUIRED = 5.0f; // 하드와이어링 작동 최소 전압

    static void logAction(const std::string& msg)
    {
        std::cout << "  [ACTION] >>> " << msg << std::endl;
    }

public:
    void processSafetyProtocol(const VehicleContext& ctx) const
    {
        std::cout << "\n[" << ctx.scenario_id << "] 시퀀스 모니터링 시작" << std::endl;
        std::cout << std::fixed << std::setprecision(1);

        // --- 상황 C: 전원 상태 수치 검증 ---
        std::cout << "  [DATA] 전원 모니터링: Main=" << ctx.main_vcc
                  << "V, Backup=" << ctx.cap_voltage << "V" << std::endl;
        if (ctx.main_vcc < VOLTAGE_CRITICAL) {
            std::cout << "  [CRITICAL] 메인 전원 상실 감지 (V < "
                      << VOLTAGE_CRITICAL << "V)" << std::endl;
            if (ctx.cap_voltage >= CAP_MIN_REQUIRED) {
                logAction("ACU 예비 전원 기반 Hard-wired 해제 신호 송출 (Status: Emergency)");
                return;
            } else {
                std::cout << "  [FATAL] 시스템 완전 무력화: 예비 전압 부족" << std::endl;
                return;
            }
        }

        // --- 상황 A: 충돌 센서 수치 검증 ---
        std::cout << "  [DATA] 충돌 감지: Airbag="
                  << (ctx.airbag_signal ? "ON" : "OFF")
                  << ", Accel_L=" << ctx.accel_l
                  << "G, Accel_R=" << ctx.accel_r << "G" << std::endl;

        const bool is_physics_valid =
            (ctx.accel_l > G_THRESHOLD) && (ctx.accel_r > G_THRESHOLD);

        if (ctx.airbag_signal && is_physics_valid) {
            logAction("Crash Unlock 조건 충족: 도어 잠금 해제 실행");

            // --- 상황 B: 후방 위험 수치 검증 ---
            if (ctx.rear_hazard) {
                std::cout << "  [DATA] 후방 장애물 접근 감지: 거리 "
                          << ctx.hazard_dist << "m" << std::endl;
                logAction("외부 경고 활성화: 비상등/실내등 Max-Intensity 점멸 (상황 B 대응)");
            }
        } else {
            // 노이즈 상황 분석 로그
            if (!is_physics_valid &&
                (ctx.accel_l > G_THRESHOLD || ctx.accel_r > G_THRESHOLD)) {
                std::cout << "  [ANALYSIS] 편차 발생: 단일 센서 임계값 초과(노이즈 가능성 99%)."
                          << std::endl;
            }
            logAction("조건 미충족: 도어 잠금 상태 유지 (Unintended Operation 방어)");
        }
    }
};

#endif
