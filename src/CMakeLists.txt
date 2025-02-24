cmake_minimum_required(VERSION 3.0)
project(toy_db)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES
        main.cpp
        Field.cpp
        Tuple.h
)

add_executable(toy_db ${SOURCE_FILES})

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.13.0.zip
)
FetchContent_MakeAvailable(googletest)


enable_testing()

file(GLOB TEST_SOURCES "tests/*.cpp")

add_executable(toy_db_tests ${TEST_SOURCES})
target_link_libraries(toy_db_tests GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(toy_db_tests)