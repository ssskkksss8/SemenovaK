cmake_minimum_required(VERSION 3.10)
project(lab_3)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic")


add_executable(main
    main.cpp
    figure.hpp
    point.hpp
    point.cpp
    rectangle.hpp
    rectangle.cpp
    trapezoid.hpp
    trapezoid.cpp
    rhomb.hpp
    rhomb.cpp
    vector.hpp
    vector.cpp)

enable_testing()
add_executable(test_lab3
    main.cpp
    figure.hpp
    point.hpp
    point.cpp
    rectangle.hpp
    rectangle.cpp
    trapezoid.hpp
    trapezoid.cpp
    rhomb.hpp
    rhomb.cpp
    vector.hpp
    vector.cpp)

target_link_libraries(test_lab3 ${GTEST_LIBRARIES})
add_test(NAME counter_test COMMAND test_lab3)

