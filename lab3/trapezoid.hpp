#pragma once

#include "figure.hpp"
#include <iostream>

class Trapezoid : public Figure
{

    friend std::ostream& operator<<(std::ostream& os, const Trapezoid& f);
    friend std::istream& operator>>(std::istream& is, Trapezoid& f);

public:
    Trapezoid();
    Trapezoid(Point& p1, Point& p2, Point& p3, Point& p4);

    virtual double area() const override;
    virtual Point center() const override;

    Point get_point(const int i) const;

    Trapezoid& operator=(const Trapezoid& right);
    Trapezoid& operator=(Trapezoid&& right);
    bool operator==(const Trapezoid& right);
    virtual operator double() const override;



    ~Trapezoid(){};

private:
    Point angles[4];
};