# Company 표준 GitHub 협업 및 CI/CD 정책

## 1. 브랜치 전략 (Branching Strategy)
안정적인 배포와 병렬 개발을 위해 **Git Flow**를 기반으로 한 전략을 사용합니다.

* `main`: 상용 환경에 배포 가능한 가장 안정적인 상태를 유지하는 브랜치
* `develop`: 다음 출시 버전을 위해 개발(Feature)들이 모이는 통합 브랜치
* `feature/`: 새로운 기능 개발 및 버그 수정을 위한 브랜치 (반드시 `develop`에서 분기)
  * **네이밍 규칙**: `feature/[이슈번호]-[작업내용]` (예: `feature/#12-login-api`)
* `hotfix/`: 상용 배포(`main`) 후 발생한 긴급 버그 수정 브랜치

## 2. 커밋 메시지 규칙 (Conventional Commits)
히스토리 파악과 자동화된 릴리스 노트 작성을 위해 아래의 접두어(Prefix)를 준수합니다.

* `feat:` : 새로운 기능 추가
* `fix:` : 버그 수정
* `docs:` : 문서 수정 (README.md 등)
* `test:` : 테스트 코드 추가 및 수정 (프로덕션 코드 변경 없음)
* `refactor:` : 코드 리팩토링 (기능 변경 없이 구조 개선)
* `style:` : 코드 포맷팅, 세미콜론 누락 등 (코드 로직 변경 없음)
* `chore:` : 빌드 업무 수정, 패키지 매니저 설정, CI/CD 스크립트 수정 등

**[작성 예시]**
> feat: Google Test 기반 사용자 인증 단위 테스트 추가 (#12)

## 3. Pull Request (PR) 및 코드 리뷰 정책
`develop` 및 `main` 브랜치로 코드를 병합(Merge)하기 위해서는 반드시 PR을 거쳐야 합니다.

* **리뷰어(Reviewer) 지정**: 최소 1명 이상의 팀원에게 코드 리뷰 승인(Approve)을 받아야 합니다.
* **CI/CD 상태 체크 통과 필수**: PR 생성 시 GitHub Actions가 자동 실행되며, 아래 항목이 모두 **Pass** 되어야 Merge가 활성화됩니다.
  * GCC Build 성공 여부
  * CppCheck 정적 분석 (Error, Warning 0건)
  * Google Test 전체 케이스 통과
  * Gcov 테스트 커버리지 최소 기준(예: 80%) 달성
* **Merge 전략**: 
  * Feature -> Develop: `Squash and Merge` (자잘한 커밋들을 하나로 깔끔하게 묶어서 병합)
  * Develop -> Main: `Create a Merge Commit` (버전 기록을 남기기 위함)

## 4. 브랜치 보호 규칙 (Branch Protection Rules)
GitHub 저장소 `Settings > Branches`에서 `main`과 `develop` 브랜치에 대해 다음 규칙을 활성화합니다.

* **Require a pull request before merging**: 직접 Push 금지 (PR 필수)
* **Require approvals**: 최소 1명 이상의 리뷰 승인 강제
* **Require status checks to pass before merging**: CI 파이프라인 통과 전 Merge 버튼 비활성화
* **Do not allow bypassing the above settings**: 관리자(Admin)도 이 규칙을 우회할 수 없도록 설정