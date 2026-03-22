# ChildLock Functional Test Cases

This document contains functional test cases for the MBP-T03-ChildLock system, generated based on Use Cases (UC-01 to UC-08), exception scenarios (Fail-Safe, power loss, sensor errors, etc.), and translated logic from unit tests (`test_active_rescue.c` and `test_advanced_sea.cpp`) to HILS or real-vehicle test environments.

| Test ID | 연관 UC | 테스트 시나리오 (항목) | 선행 조건 (Pre-condition) | 테스트 절차 (Action) | 예상 결과 (Expected Result) | 비고 (Fail-Safe 여부 등) |
|---------|---------|-------------------------|---------------------------|----------------------|-----------------------------|---------------------------|
| TC-01-01 | UC-01 | 정상 고속 접근 물체 감지 시 잠금 유지 | 차량 정지, SEA 모드 활성화, 센서 정상 | 고속 물체가 접근하도록 시뮬레이션 (HILS: 센서 입력 조작) | 잠금 유지, 경고음 발생 | 정상 동작 |
| TC-01-02 | UC-01 | 센서 에러 시 Fail-Safe 잠금 해제 | 차량 정지, SEA 모드 활성화, 센서 에러 발생 | 센서 에러를 유발 (HILS: 센서 신호 끊기) | 잠금 해제, 안전 모드 전환 | Fail-Safe: 예 |
| TC-01-03 | UC-01 | 전원 상실 시 잠금 유지 | 차량 정지, SEA 모드 활성화, 전원 정상 | 전원 공급 중단 (실차: 배터리 분리) | 잠금 유지, 백업 전원으로 최소 기능 유지 | Fail-Safe: 예 |
| TC-02-01 | UC-02 | 정상 고체온 감지 시 창문 개방 및 구조 모드 | 승객 존재, Active Rescue 모드 활성화, 센서 정상 | 고체온 신호 입력 (HILS: 센서 데이터 조작) | 창문 개방, 구조 모드 활성화, 알림 전송 | 정상 동작 |
| TC-02-02 | UC-02 | 센서 에러 시 Fail-Safe 구조 모드 비활성화 | 승객 존재, Active Rescue 모드 활성화, 센서 에러 | 센서 에러 유발 (HILS: 신호 노이즈 추가) | 구조 모드 비활성화, 수동 개입 필요 | Fail-Safe: 예 |
| TC-02-03 | UC-02 | 전원 상실 시 구조 모드 유지 | 승객 존재, Active Rescue 모드 활성화, 전원 정상 | 전원 중단 (실차: 배터리 테스트) | 구조 모드 유지, 백업으로 최소 시간 동안 기능 | Fail-Safe: 예 |
| TC-03-01 | UC-03 | 승객 구분 시 스마트 잠금 적용 | 승객 감지, Smart Lock 모드 활성화, 센서 정상 | 승객 유형 입력 (HILS: 카메라 데이터 시뮬) | 적절한 잠금 레벨 적용 | 정상 동작 |
| TC-03-02 | UC-03 | 센서 에러 시 기본 잠금 | 승객 감지, Smart Lock 모드 활성화, 센서 에러 | 센서 실패 (HILS: 데이터 손실) | 기본 잠금 적용, 경고 | Fail-Safe: 예 |
| TC-04-01 | UC-04 | 충돌 감지 시 자동 해제 | 차량 충돌, Crash Unlock 모드 활성화, 센서 정상 | 충돌 시뮬레이션 (HILS: 가속도 센서 트리거) | 잠금 해제, 비상 모드 | 정상 동작 |
| TC-04-02 | UC-04 | 센서 에러 시 수동 해제 필요 | 차량 충돌, Crash Unlock 모드 활성화, 센서 에러 | 센서 에러 (HILS: 신호 오류) | 잠금 유지, 수동 개입 | Fail-Safe: 예 |
| TC-05-01 | UC-05 | 압착 방지 시 창문 정지 | 창문 이동 중, Anti-Pinch 모드 활성화, 센서 정상 | 압착 감지 (HILS: 압력 센서 조작) | 창문 정지, 역방향 이동 | 정상 동작 |
| TC-05-02 | UC-05 | 센서 에러 시 창문 정지 | 창문 이동 중, Anti-Pinch 모드 활성화, 센서 에러 | 센서 실패 (HILS: 노이즈) | 창문 정지, 안전 우선 | Fail-Safe: 예 |
| TC-06-01 | UC-06 | 하이브리드 제어 및 상태 표시 | 시스템 활성화, 센서 정상 | 제어 입력 (HILS: CAN 버스 시뮬) | 상태 시각화, 제어 응답 | 정상 동작 |
| TC-06-02 | UC-06 | 전원 상실 시 상태 유지 | 시스템 활성화, 전원 정상 | 전원 끊기 (실차: 테스트) | 최소 상태 표시 유지 | Fail-Safe: 예 |
| TC-07-01 | UC-07 | 위치 기반 자동 해제 | 지정 위치 진입, Geo-Fencing 모드 활성화, GPS 정상 | 위치 변경 (HILS: GPS 시뮬) | 잠금 해제 | 정상 동작 |
| TC-07-02 | UC-07 | GPS 에러 시 잠금 유지 | 지정 위치 진입, Geo-Fencing 모드 활성화, GPS 에러 | GPS 실패 (HILS: 신호 끊기) | 잠금 유지, 경고 | Fail-Safe: 예 |
| TC-08-01 | UC-08 | 실내 조작 감지 및 알림 | 실내 조작, 감지 모드 활성화, 센서 정상 | 조작 시뮬 (HILS: 터치 센서) | 알림 전송 | 정상 동작 |
| TC-08-02 | UC-08 | 센서 에러 시 알림 실패 | 실내 조작, 감지 모드 활성화, 센서 에러 | 센서 에러 (HILS: 오류) | 알림 실패, 로그 기록 | Fail-Safe: 예 |