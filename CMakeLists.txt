cmake_minimum_required(VERSION 3.00)
project(lab01)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

set(CMAKE_CXX_STANDART 17)
set(CMAKE_CXX_STANDART_REQUIRED ON) 

add_executable(lab first.cpp my_foo1.cpp)

enable_testing()
add_executable(tests tests.cpp  my_foo1.cpp)
target_link_libraries(tests ${GTEST_LIBRARIES})

add_test(NAME BASIC COMMAND tests)