cmake_minimum_required(VERSION 3.16)
project(ChildLockSystem LANGUAGES C CXX)

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

add_executable(test_advanced_sea test/test_advanced_sea.c)
target_link_libraries(test_advanced_sea PRIVATE advanced_sea)
if(ENABLE_COVERAGE)
    target_link_libraries(test_advanced_sea PRIVATE coverage_flags)
endif()
add_test(NAME AdvancedSeaLogicTest COMMAND test_advanced_sea)
