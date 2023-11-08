#pragma once

#include "figure.hpp"
#include <iostream>
#include "point.hpp"

template<class T>
class Trapezoid : public Figure<T> 
{
    template<class F>
    friend std::ostream& operator<<(std::ostream& os, const Trapezoid<F>& f);

    template<class F>
    friend std::istream& operator>>(std::istream& is, Trapezoid<F>& f);

public:
    Trapezoid();
    Trapezoid(Point<T>& p1, Point<T>& p2, Point<T>& p3, Point<T>& p4);
    Trapezoid(const Trapezoid<T>& other);

    virtual T area() const override;
    virtual Point<T>  center() const override;

    Point<T>  get_point(const int i) const;
    size_t size() const;

    Trapezoid<T>& operator=(const Trapezoid<T>& right);
    Trapezoid<T>& operator=(Trapezoid<T>&& right);
    bool     operator==(const Trapezoid<T>& right) ;
    virtual  operator double() const override;

    ~Trapezoid(){};

    Point<T> angles[4];
    size_t size_;
};

template <class T>
Trapezoid<T>::Trapezoid() : angles{Point<T>(), Point<T>(), Point<T>(), Point<T>()}, size_{0} {}

template <class T>
Trapezoid<T>::Trapezoid(Point<T>& p1, Point<T>& p2, Point<T>& p3, Point<T>& p4) {
    std::array<Point<T>, 4> points = {p1, p2, p3, p4};
    for (int i = 0; i < 4; i++) {
        for (int j = i + 1; j < 4; j++) {
            if (points[i] == points[j]) {
                throw std::logic_error("Same coordinates for different angles");
            }
        }
        angles[i] = points[i];
    }
    size_ = 4;
}

template <class T>
Trapezoid<T>::Trapezoid(const Trapezoid<T>& other){
    if (this != &other) {
        for(size_t i = 0; i < 4; ++i){
            angles[i] = other.angles[i];
        }
        size_ = other.size_;
    }
}

template <class T>
Point<T> Trapezoid<T>::center() const {
    std::cout << "Trapezoid center() " << std::endl;
    T x_c = 0, y_c = 0;
    for(size_t i = 0; i < size_; ++i){
        x_c += angles[i].x_;
        y_c += angles[i].y_;
    }
    return Point(x_c / 4.0, y_c / 4.0);
}

template <class T>
T Trapezoid<T>::area() const {
    T x1 = angles[0].x_; T y1 = angles[0].y_;
    T x2 = angles[1].x_; T y2 = angles[1].y_;
    T x3 = angles[2].x_; T y3 = angles[2].y_;
    T x4 = angles[3].x_; T y4 = angles[3].y_;
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

template <class T>
Trapezoid<T>& Trapezoid<T>::operator=(const Trapezoid<T>& right){
    if (this != &right) {
        for(size_t i = 0; i < 4; ++i){
            angles[i] = right.angles[i];
        }
        size_ = right.size_;
    }
    return *this;
}

template <class T>
Trapezoid<T>& Trapezoid<T>::operator=(Trapezoid<T>&& right){
    if (this != &right) {
        for(size_t i = 0; i < 4; ++i){
            angles[i] = std::move(right.angles[i]);
        }
        size_ = right.size_;
    }
    return *this;
}

template <class T>
bool Trapezoid<T>::operator==(const Trapezoid<T>& right) {
    for(size_t i = 0; i < 4; ++i){
        if(angles[i] != right.angles[i]){
            return false;
        }
    }
    return true;
}

template <class T>
std::ostream& operator<<(std::ostream& os, const Trapezoid<T>& f){
    for(size_t i = 0; i < 4; ++i){
        os << f.angles[i] << std::endl;
    }
    return os;

}

template <class T>
std::istream& operator>>(std::istream& is, Trapezoid<T>& f){
    for(size_t i = 0; i < 4; ++i){
        is >> f.angles[i];
        if (is.fail()) {
            throw std::invalid_argument("Input must be a number");
        }
    }
    for (int i = 0; i < 4; i++) {
        for (int j = i + 1; j < 4; j++) {
            if (f.angles[i] == f.angles[j]) {
                throw std::logic_error("Same coordinates for different angles");
            }
        }
    }
    f.size_ = 4;
    return is;
}

template <class T>
Trapezoid<T>::operator double() const{
    return area();
}

template <class T>
size_t Trapezoid<T>::size() const{
    return size_;
}

template <class T>
Point<T> Trapezoid<T>::get_point(const int i) const{
    if ( i < 0 || i > 3){
        throw std::invalid_argument("Out of index range");
    }
    return angles[i];
}
