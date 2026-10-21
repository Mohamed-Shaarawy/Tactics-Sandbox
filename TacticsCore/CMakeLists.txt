cmake_minimum_required(VERSION 3.24)
project(TacticsCore LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ---------- Sanitizers ----------
# Off by default; CI turns them on. Example: -DTACTICS_SANITIZE=address,undefined
# Applied globally (before GoogleTest is fetched) so every object is instrumented.
set(TACTICS_SANITIZE "" CACHE STRING "Comma-separated sanitizers: address, undefined")
if(TACTICS_SANITIZE)
    if(MSVC)
        if(NOT TACTICS_SANITIZE STREQUAL "address")
            message(FATAL_ERROR "MSVC only supports TACTICS_SANITIZE=address")
        endif()
        add_compile_options(/fsanitize=address /Zi)
        add_link_options(/INCREMENTAL:NO)
        # /RTC1 (on by default in Debug) is incompatible with ASan.
        string(REPLACE "/RTC1" "" CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}")
    else()
        add_compile_options(-fsanitize=${TACTICS_SANITIZE} -fno-omit-frame-pointer -fno-sanitize-recover=all)
        add_link_options(-fsanitize=${TACTICS_SANITIZE})
    endif()
endif()

# Warnings for our own targets only (not third-party code).
function(tactics_set_warnings target)
    if(MSVC)
        target_compile_options(${target} PRIVATE /W4 /permissive-)
    else()
        target_compile_options(${target} PRIVATE -Wall -Wextra -Wpedantic)
    endif()
endfunction()

# ---------- Library ----------
add_library(TacticsCore STATIC
    src/core.cpp
)
target_include_directories(TacticsCore PUBLIC include)
tactics_set_warnings(TacticsCore)

# ---------- Tests ----------
include(FetchContent)
FetchContent_Declare(googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.15.2.tar.gz
)
# Match the MSVC runtime used by our targets.
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()
add_executable(TacticsCoreTests
    tests/core_test.cpp
)
target_link_libraries(TacticsCoreTests PRIVATE TacticsCore GTest::gtest_main)
tactics_set_warnings(TacticsCoreTests)

include(GoogleTest)
gtest_discover_tests(TacticsCoreTests)
