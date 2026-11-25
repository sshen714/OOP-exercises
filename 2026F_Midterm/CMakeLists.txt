# ! ------------------------------------------------------------------ !
# ! Changing this file incorrectly can cause your program to not build !
# ! If you don't know CMake well DO NOT touch this file                !
# ! ------------------------------------------------------------------ !

cmake_minimum_required(VERSION 3.20)
project(OOP VERSION 0.1.0)
enable_testing()

set(CMAKE_CXX_STANDARD 17)


#### GTest
option(FETCH_GOOGLETEST "Download googletest source" ON)
if(FETCH_GOOGLETEST)
    # reference: https://google.github.io/googletest/quickstart-cmake.html
    include(FetchContent)
    FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.12.1
    )
    # For Windows: Prevent overriding the parent project's compiler/linker settings
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)
else()
    message("Using custom googletest installation")
    # reference: https://cmake.org/cmake/help/latest/module/FindGTest.html
    find_package(GTest REQUIRED)
endif()

include(files.cmake)

set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)
set(TEST_DIR ${CMAKE_SOURCE_DIR}/test)

list(TRANSFORM SRC_FILES PREPEND ${SRC_DIR}/)
list(TRANSFORM INCLUDE_FILES PREPEND ${INCLUDE_DIR}/)
list(TRANSFORM TEST_FILES PREPEND ${TEST_DIR}/)

find_program(MEMORYCHECK_COMMAND valgrind)
set(MEMORYCHECK_COMMAND_OPTIONS
    "--error-exitcode=1 --track-origins=yes --leak-check=full"
)
include(CTest)

option(COVERAGE "Enable coverage" OFF)

if(COVERAGE)
    set(CMAKE_C_FLAGS "--coverage -g -O0")
    set(CMAKE_CXX_FLAGS "--coverage -g -O0")

    include(scripts/CodeCoverage.cmake)
    set(CODE_COVERAGE_VERBOSE ON)
    set(COVERAGE_EXCLUDE
        ${CMAKE_BINARY_DIR}/_deps/*
        ${PROJECT_SOURCE_DIR}/test/*
    )

    if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
        set(GCOVR_ADDITIONAL_ARGS
            --gcov-executable "llvm-cov gcov"
        )
    endif()

    append_coverage_compiler_flags()
    setup_target_for_coverage_gcovr_html(
        NAME ut_all_coverage
        DEPENDENCIES ut_all
        EXCLUDE ${COVERAGE_EXCLUDE}
    )
endif()

if(MSVC)
    set(TARGET_COMPILER_OPTIONS
        /W4
    )
else()
    set(TARGET_COMPILER_OPTIONS
        -Wall -Wextra -Wpedantic
        -Werror=return-type
        -Werror=uninitialized
        -Wfatal-errors
    )
endif()

add_executable(ut_all
    ${SRC_FILES}
    ${INCLUDE_FILES}
    ${TEST_FILES}
)
target_link_libraries(ut_all
    GTest::gtest_main
)
target_include_directories(ut_all PRIVATE
    ${INCLUDE_DIR}
)
target_compile_options(ut_all PRIVATE
    ${TARGET_COMPILER_OPTIONS}
)

add_executable(ut_character
        ${SRC_FILES}
        ${INCLUDE_FILES}
        test/ut_character.cpp
)
target_link_libraries(ut_character
        GTest::gtest_main
)
target_include_directories(ut_character PRIVATE
        ${INCLUDE_DIR}
)
target_compile_options(ut_character PRIVATE
        ${TARGET_COMPILER_OPTIONS}
)

add_executable(ut_gingerbread_man
        ${SRC_FILES}
        ${INCLUDE_FILES}
        test/ut_gingerbread_man.cpp
)
target_link_libraries(ut_gingerbread_man
        GTest::gtest_main
)
target_include_directories(ut_gingerbread_man PRIVATE
        ${INCLUDE_DIR}
)
target_compile_options(ut_gingerbread_man PRIVATE
        ${TARGET_COMPILER_OPTIONS}
)

add_executable(ut_water_cookie
        ${SRC_FILES}
        ${INCLUDE_FILES}
        test/ut_water_cookie.cpp
)
target_link_libraries(ut_water_cookie
        GTest::gtest_main
)
target_include_directories(ut_water_cookie PRIVATE
        ${INCLUDE_DIR}
)
target_compile_options(ut_water_cookie PRIVATE
        ${TARGET_COMPILER_OPTIONS}
)

add_executable(ut_plant_cookie
        ${SRC_FILES}
        ${INCLUDE_FILES}
        test/ut_plant_cookie.cpp
)
target_link_libraries(ut_plant_cookie
        GTest::gtest_main
)
target_include_directories(ut_plant_cookie PRIVATE
        ${INCLUDE_DIR}
)
target_compile_options(ut_plant_cookie PRIVATE
        ${TARGET_COMPILER_OPTIONS}
)

add_executable(ut_fire_cookie
        ${SRC_FILES}
        ${INCLUDE_FILES}
        test/ut_fire_cookie.cpp
)
target_link_libraries(ut_fire_cookie
        GTest::gtest_main
)
target_include_directories(ut_fire_cookie PRIVATE
        ${INCLUDE_DIR}
)
target_compile_options(ut_fire_cookie PRIVATE
        ${TARGET_COMPILER_OPTIONS}
)

add_executable(ut_gingerbread_group
        ${SRC_FILES}
        ${INCLUDE_FILES}
        test/ut_gingerbread_group.cpp
)
target_link_libraries(ut_gingerbread_group
        GTest::gtest_main
)
target_include_directories(ut_gingerbread_group PRIVATE
        ${INCLUDE_DIR}
)
target_compile_options(ut_gingerbread_group PRIVATE
        ${TARGET_COMPILER_OPTIONS}
)

include(GoogleTest)
gtest_discover_tests(ut_all)