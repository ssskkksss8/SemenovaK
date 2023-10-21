#include "point.hpp"

Point::Point() : x_{0}, y_{0} {}

Point::Point(double x, double y): x_{x}, y_{y} {}

Point::Point(const Point& other) : x_(other.x_), y_(other.y_) {}

Point operator+(const Point& left, const Point& right){
    return Point(left.x_ + right.x_, left.y_ + right.y_);
}

Point operator-(const Point& left, const Point& right){
    return Point(left.x_ - right.x_, left.y_ - right.y_);
}

bool operator==(const Point& left, const Point& right){
    return (left.x_ == right.x_) && (left.y_ == right.y_);
}

bool operator!=(const Point& left, const Point& right){
    return (left.x_ != right.x_) || (left.y_ != right.y_);
}

Point& Point::operator=(const Point& right){
    if (this != &right) {
        x_ = right.x_;
        y_ = right.y_;
    }
    std::cout << "This : " << this << std::endl;
    std::cout << "*This : " << *this << std::endl;
    return *this;
}

std::istream& operator>>(std::istream& is, Point& p){
    double x,y;
    std::cout << "Enter 'x' and 'y' :" << std::endl;
    is >> x >> y;
    p.x_ = x;
    p.y_ = y;
    return is;
}

std::ostream& operator<<(std::ostream& os, const Point& p){
    os << "(x: " << p.x_ << "; y: " << p.y_ << ")";
    return os;
}