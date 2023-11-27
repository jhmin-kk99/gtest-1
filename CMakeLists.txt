cmake_minimum_required(VERSION 3.10)
project(testing_test)

set(SOURCE_FILE main.c)
add_executable(origin_run ${SOURCE_FILE})

include_directories(origin_lib)
add_subdirectory(origin_lib)

target_link_libraries(origin_run origin_lib)

add_subdirectory(Google_tests)

