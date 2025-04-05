cmake_minimum_required(VERSION 3.0)
project(toy_db)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES
        main.cpp
        core/Field.cpp
        core/Tuple.h
        core/StorageManager.h
        core/StorageManager.cpp
        core/BTree.cpp
        core/BufferManager.h
)

add_library(toy_db_core
        core/Field.cpp
        core/Tuple.h
        core/StorageManager.h
        core/StorageManager.cpp
        core/BTree.cpp
        core/BufferManager.h
        core/Config.h
)

target_include_directories(toy_db_core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})


add_executable(toy_db main.cpp)
target_link_libraries(toy_db toy_db_core)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.13.0.zip
)
FetchContent_MakeAvailable(googletest)


enable_testing()

file(GLOB TEST_SOURCES "tests/*.cpp")
add_executable(toy_db_tests ${TEST_SOURCES})
target_link_libraries(toy_db_tests
        toy_db_core
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(toy_db_tests)