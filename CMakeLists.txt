cmake_minimum_required(VERSION 3.10)
project(ChildLockSystem C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

if(MSVC)
    add_compile_options(/utf-8)
endif()

# ---------------------------------------------------
# 1. 커버리지 측정 옵션 (GitHub Actions 연동)
# ---------------------------------------------------
if(ENABLE_COVERAGE)
    # GCC/Clang 컴파일러에 코드 커버리지 추적 지시
    add_compile_options(--coverage -O0 -g)
    add_link_options(--coverage)
endif()

# ---------------------------------------------------
# 2. 메인 실행 파일 설정
# ---------------------------------------------------
add_executable(main src/main.c src/active_rescue.c)
target_include_directories(main PRIVATE include)

# ---------------------------------------------------
# 3. 단위 테스트 (CTest) 환경 설정
# ---------------------------------------------------
enable_testing() # ctest 명령어 활성화

# 테스트용 실행 파일 생성 (main.c는 제외하고 로직과 테스트 코드만 연결)
add_executable(test_rescue test/test_active_rescue.c src/active_rescue.c)
target_include_directories(test_rescue PRIVATE include)

# CTest가 실행할 테스트 등록
add_test(NAME RescueLogicTest COMMAND test_rescue)