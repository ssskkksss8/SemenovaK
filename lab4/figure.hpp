#pragma once

#include <iostream>
#include <string>
#include <cmath>
#include <array>
#include <algorithm>
#include "point.hpp"

template <typename T>
concept Number = std::integral<T> || std::floating_point<T>;
template <Number T>
class Figure {
public:

    Figure() = default;

    virtual T area() const = 0;
    virtual Point<T> center() const = 0;
    virtual operator double() const = 0;
    
    virtual ~Figure() = default;
};