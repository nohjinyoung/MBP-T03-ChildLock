# 🧪 요구사항 기반 기능 테스트 케이스 생성 및 등록 가이드 (ReqTest.md)

본 문서는 **MBP-T03-ChildLock** 시스템의 요구사항 정의서(SwRS)와 구현된 소스 코드를 바탕으로, AI Agent를 활용해 기능 테스트 케이스(Functional Test Case)를 자동으로 생성하고 이를 엑셀(Excel) 형식으로 문서화하여 저장소에 등록하는 프로세스를 안내합니다.

---

## 🤖 1. 기능 테스트 케이스 생성을 위한 AI Agent 프롬프트

AI 모델(ChatGPT, Claude, Gemini 등)에게 QA 엔지니어의 역할을 부여하여 테스트 케이스를 생성하도록 지시하는 프롬프트(명령어) 템플릿입니다. 아래 내용을 복사하여 AI 채팅창에 입력하세요.

### 📋 프롬프트 복사 영역
```text
당신은 자동차 전장 시스템(특히 차일드락 및 안전 제어 로직)의 전문 QA(Quality Assurance) 엔지니어입니다.
아래에 제공된 [요구사항 및 Use Case]와 [단위 테스트 코드 로직]을 분석하여, 소프트웨어 기능 테스트 케이스(Functional Test Case)를 도출해 주세요.

[요구사항 및 Use Case 요약]
- UC-01: 지능형 하차 보조 (Advanced SEA) - 고속 접근 물체 감지 시 잠금 유지
- UC-02: 생체 신호 연동 비상 대응 (Active Rescue) - 고체온 감지 시 창문 개방 및 구조 모드
- UC-03: 승객 구분형 스마트 잠금 (Smart Lock)
- UC-04: 크래시 언락 (Crash Unlock)
- UC-05: 세이프티 리버싱 (Anti-Pinch)
- UC-06: 하이브리드 제어 및 상태 시각화
- UC-07: 위치 기반 자동 해제 (Geo-Fencing)
- UC-08: 실내 조작 감지 및 알림

[작업 지시사항]
1. 각 Use Case와 예외 상황(Fail-Safe, 전원 상실, 센서 에러 등)을 모두 포함하는 테스트 시나리오를 작성하세요.
2. 단위 테스트 코드(`test_active_rescue.c`, `test_advanced_sea.cpp`)의 검증 논리를 실제 기능 테스트 환경(HILS 또는 실차 테스트)에 맞게 번역하세요.
3. 결과물은 반드시 엑셀로 복사하기 쉬운 **마크다운 표(Table) 형식**으로 출력해 주세요.
4. 결과물은 test/test_cases/ChildLock_Functional_TestCases.md (또는 .csv) 파일로 직접 생성하여 저장해 주세요.

[출력 형식 (테이블 컬럼)]
| Test ID | 연관 UC | 테스트 시나리오 (항목) | 선행 조건 (Pre-condition) | 테스트 절차 (Action) | 예상 결과 (Expected Result) | 비고 (Fail-Safe 여부 등) |