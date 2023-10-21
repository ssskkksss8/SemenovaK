#pragma once

#include "figure.hpp"
#include <iostream>

class Rectangle : public Figure
{

    friend std::ostream& operator<<(std::ostream& os, const Rectangle& f);
    friend std::istream& operator>>(std::istream& is,Rectangle& f);

public:
   Rectangle();
   Rectangle(Point& p1, Point& p2, Point& p3, Point& p4);
    virtual double area() const override;
    virtual Point center() const override;

    Point get_point(const int i) const;

   Rectangle& operator=(const Rectangle& right);
   Rectangle& operator=(Rectangle&& right);
    bool operator==(const Rectangle& right);
    virtual operator double() const override;



    ~Rectangle(){};

private:
    Point angles[4];
};