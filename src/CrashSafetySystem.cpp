#ifndef CRASH_SAFETY_SYSTEM_CPP
#define CRASH_SAFETY_SYSTEM_CPP

#include <iostream>
#include <string>

// 센서 데이터 구조체
struct VehicleSensorData {
    std::string scenario_name;
    bool airbag_deployed;
    float accel_l;
    float accel_r;
};

class CrashSafetySystem {
private:
    const float G_THRESHOLD = 15.0f; // 임계값 고정

public:
    CrashSafetySystem() {
        std::cout << "[SYSTEM] Crash Safety Module 초기화 완료." << std::endl;
        std::cout << "[SYSTEM] 가속도 검증 임계값: " << G_THRESHOLD << "G" << std::endl;
    }

    // UC-04: 크래시 언락 판단 핵심 로직
    bool evaluateUnlockCondition(const VehicleSensorData& data) {
        std::cout << "  [LOG] " << data.scenario_name << " 분석 중..." << std::endl;

        // 1. 에어백 신호 확인
        if (!data.airbag_deployed) {
            std::cout << "  [LOG] Step 1: 에어백 전개 신호 없음 (Normal)" << std::endl;
            return false;
        }

        // 2. 가속도 센서 중복 검증 (AND 조건)
        bool is_accel_valid = (data.accel_l > G_THRESHOLD) && (data.accel_r > G_THRESHOLD);
        
        std::cout << "  [LOG] Step 2: Accel Check (L:" << data.accel_l << "G, R:" << data.accel_r << "G)" << std::endl;

        if (!is_accel_valid) {
            if (data.accel_l > G_THRESHOLD || data.accel_r > G_THRESHOLD) {
                std::cout << "  [WARN] 단일 센서 노이즈 감지! (Unintended Operation 방어)" << std::endl;
            }
            return false;
        }

        std::cout << "  [LOG] Step 3: 모든 안전 조건 충족. Unlock 승인." << std::endl;
        return true;
    }
};

#endif
