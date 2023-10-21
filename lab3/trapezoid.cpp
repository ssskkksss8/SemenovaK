#include "trapezoid.hpp"
#include <stdlib.h>

Trapezoid::Trapezoid() : angles{Point(), Point(), Point(), Point()} {}

Trapezoid::Trapezoid(Point& p1, Point& p2, Point& p3, Point& p4) : angles{p1, p2, p3, p4}  {}

Point Trapezoid::center() const {
    //std::cout << "Trapezoid center() " << std::endl;
    double xc = 0, yc = 0;
    for(size_t i = 0; i < 4; ++i){
        xc += angles[i].x_;
        yc += angles[i].y_;
    }
    return Point(xc / 4.0, yc / 4.0);
}

double Trapezoid::area() const {
    //std::cout << "Trapezoid area() " << std::endl;
    double x1 = angles[0].x_; double y1 = angles[0].y_;
    double x2 = angles[1].x_; double y2 = angles[1].y_;
    double x3 = angles[2].x_; double y3 = angles[2].y_;
    double x4 = angles[3].x_; double y4 = angles[3].y_;
    double a = sqrt(pow((x1 - x2),2) + pow((y1 - y2),2));
    double b = sqrt(pow((x3 - x4),2) + pow((y3 - y4),2));
    double c = sqrt(pow((x1 - x4),2) + pow((y1 - y4),2));
    int maxa, mina = 0;
    if (a > b){
        maxa = a;
        mina = b;
    }
    else {
        maxa = b;
        mina = a;
    }
    double h = sqrt(pow(c,2) - pow((maxa - mina) / 2,2));
    double area = (a + b) / 2 * h;
    return area;
}

Trapezoid& Trapezoid::operator=(const Trapezoid& right){
    if (this != &right) {
        for(size_t i = 0; i < 4; ++i){
            angles[i] = right.angles[i];
        }
    }
    return *this;
}

Trapezoid& Trapezoid::operator=(Trapezoid&& right){
    if (this != &right) {
        for(size_t i = 0; i < 4; ++i){
            angles[i] = std::move(right.angles[i]);
        }
    }
    return *this;
}

bool Trapezoid::operator==(const Trapezoid& right){
    for(size_t i = 0; i < 4; ++i){
        if(angles[i] != right.angles[i]){
            return false;
        }
    }
    return true;
}

std::ostream& operator<<(std::ostream& os, const Trapezoid& f){
    os << "Trapezoid's coordinates:"<< std::endl;
    for(size_t i = 0; i < 4; ++i){
        os << f.angles[i] << std::endl;
    }
    return os;

}
std::istream& operator>>(std::istream& is, Trapezoid& f) {
    std::cout << "|Enter Trapezoid's coordinates|" << std::endl;
    for (size_t i = 0; i < 4; ++i) {
         is >> f.angles[i];
    }
    return is;
}

Trapezoid::operator double() const{
    return area();
}

Point Trapezoid::get_point(const int i) const{
    if ( i <= 0 || i >= 4){
        throw std::invalid_argument("Out of index range");
    }
    return angles[i];
}