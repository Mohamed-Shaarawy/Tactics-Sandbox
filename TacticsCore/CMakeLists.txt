cmake_minimum_required(VERSION 3.24)
project(TacticsCore LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ---------- Library ----------
add_library(TacticsCore STATIC
    src/core.cpp
)
target_include_directories(TacticsCore PUBLIC include)

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

include(GoogleTest)
gtest_discover_tests(TacticsCoreTests)
