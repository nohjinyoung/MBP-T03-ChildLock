cmake_minimum_required(VERSION 3.16)
project(ChildLockSystem LANGUAGES C CXX)

include(FetchContent)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(MSVC)
    add_compile_options(/utf-8)
endif()

if(ENABLE_COVERAGE)
    add_library(coverage_flags INTERFACE)
    target_compile_options(coverage_flags INTERFACE --coverage -O0 -g)
    target_link_options(coverage_flags INTERFACE --coverage)
endif()

add_library(active_rescue STATIC src/active_rescue.c)
target_include_directories(active_rescue PUBLIC include)
if(ENABLE_COVERAGE)
    target_link_libraries(active_rescue PUBLIC coverage_flags)
endif()

add_library(advanced_sea STATIC src/advanced_sea.c)
target_include_directories(advanced_sea PUBLIC include)
if(ENABLE_COVERAGE)
    target_link_libraries(advanced_sea PUBLIC coverage_flags)
endif()

add_executable(main src/main.c)
target_include_directories(main PRIVATE include)
target_link_libraries(main PRIVATE active_rescue)

enable_testing()

add_executable(test_rescue test/test_active_rescue.c)
target_link_libraries(test_rescue PRIVATE active_rescue)
if(ENABLE_COVERAGE)
    target_link_libraries(test_rescue PRIVATE coverage_flags)
endif()
add_test(NAME RescueLogicTest COMMAND test_rescue)

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

include(GoogleTest)

add_executable(test_advanced_sea test/test_advanced_sea.cpp)
target_link_libraries(test_advanced_sea PRIVATE advanced_sea GTest::gtest_main)
if(ENABLE_COVERAGE)
    target_link_libraries(test_advanced_sea PRIVATE coverage_flags)
endif()
gtest_discover_tests(test_advanced_sea)
