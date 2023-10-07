cmake_minimum_required(VERSION 3.0)
project(lab02)
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
set(CMAKE_CXX_STANDART 17)
set(CMAKE_CXX_STANDART_REQUIRED ON) 

add_executable(lab2 main2.cpp five.cpp)
#target_include_directories(lab C:/googletest/googletest/include)

include_directories(C:/googletest/googletest/include)


enable_testing()
add_executable(tests test.cpp  main2.cpp)
target_link_libraries(tests ${GTEST_LIBRARIES})

add_test(NAME BASIC COMMAND tests)