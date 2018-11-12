cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 14)

project(my_cat)

add_subdirectory(.gtest)
enable_testing()

include_directories(include)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(my_cat src/main.cc
                      src/cmd_args.cc)

add_executable(test_cmd_args test/cmd_args.cc
                             src/cmd_args.cc)
target_link_libraries(test_cmd_args gtest gtest_main)
add_test(run_cmd_args_test test_cmd_args)
