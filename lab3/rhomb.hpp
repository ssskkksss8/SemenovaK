#pragma once

#include "figure.hpp"
#include <iostream>

class Rhomb : public Figure
{

    friend std::ostream& operator<<(std::ostream& os, const Rhomb& f);
    friend std::istream& operator>>(std::istream& is, Rhomb& f);

public:
    Rhomb();
    Rhomb(Point& p1, Point& p2, Point& p3, Point& p4);

    virtual double area() const override;
    virtual Point center() const override;

    Point get_point(const int i) const;

    Rhomb& operator=(const Rhomb& right);
    Rhomb& operator=(Rhomb&& right);
    bool operator==(const Rhomb& right);
    virtual operator double() const override;



    ~Rhomb(){};

private:
    Point angles[4];
};