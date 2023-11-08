#pragma once

#include "figure.hpp"
#include <iostream>
#include "point.hpp"

template<class T>
class Rhomb : public Figure<T> 
{
    template<class F>
    friend std::ostream& operator<<(std::ostream& os, const Rhomb<F>& f);

    template<class F>
    friend std::istream& operator>>(std::istream& is, Rhomb<F>& f);

public:
    Rhomb();
    Rhomb(Point<T>& p1, Point<T>& p2, Point<T>& p3, Point<T>& p4);
    Rhomb(const Rhomb<T>& other);

    virtual T area() const override;
    virtual Point<T>  center() const override;

    Point<T>  get_point(const int i) const;
    size_t size() const;

    Rhomb<T>& operator=(const Rhomb<T>& right);
    Rhomb<T>& operator=(Rhomb<T>&& right);
    bool     operator==(const Rhomb<T>& right) ;
    virtual  operator double() const override;

    ~Rhomb(){};

    Point<T> angles[4];
    size_t size_;
};

template <class T>
Rhomb<T>::Rhomb() : angles{Point<T>(), Point<T>(), Point<T>(), Point<T>()}, size_{0} {}

template <class T>
Rhomb<T>::Rhomb(Point<T>& p1, Point<T>& p2, Point<T>& p3, Point<T>& p4) {
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
Rhomb<T>::Rhomb(const Rhomb<T>& other){
    if (this != &other) {
        for(size_t i = 0; i < 4; ++i){
            angles[i] = other.angles[i];
        }
        size_ = other.size_;
    }
}

template <class T>
Point<T> Rhomb<T>::center() const {
    std::cout << "Rhomb center() " << std::endl;
    T x_c = 0, y_c = 0;
    for(size_t i = 0; i < size_; ++i){
        x_c += angles[i].x_;
        y_c += angles[i].y_;
    }
    return Point(x_c / 4.0, y_c / 4.0);
}

template <class T>
T Rhomb<T>::area() const {
    T x1 = angles[0].x_; T y1 = angles[0].y_;
    T x2 = angles[1].x_; T y2 = angles[1].y_;
    Point center = this->center();
    double d1 = sqrt(pow((x1 - center.x_),2) + pow((y1 - center.y_),2));
    double d2 = sqrt(pow((x2 - center.x_),2) + pow((y2 - center.y_),2));
    double area = (d1 * d2) * 2;
    return area;
}

template <class T>
Rhomb<T>& Rhomb<T>::operator=(const Rhomb<T>& right){
    if (this != &right) {
        for(size_t i = 0; i < 4; ++i){
            angles[i] = right.angles[i];
        }
        size_ = right.size_;
    }
    return *this;
}

template <class T>
Rhomb<T>& Rhomb<T>::operator=(Rhomb<T>&& right){
    if (this != &right) {
        for(size_t i = 0; i < 4; ++i){
            angles[i] = std::move(right.angles[i]);
        }
        size_ = right.size_;
    }
    return *this;
}

template <class T>
bool Rhomb<T>::operator==(const Rhomb<T>& right) {
    for(size_t i = 0; i < 4; ++i){
        if(angles[i] != right.angles[i]){
            return false;
        }
    }
    return true;
}

template <class T>
std::ostream& operator<<(std::ostream& os, const Rhomb<T>& f){
    for(size_t i = 0; i < 4; ++i){
        os << f.angles[i] << std::endl;
    }
    return os;

}

template <class T>
std::istream& operator>>(std::istream& is, Rhomb<T>& f){
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
Rhomb<T>::operator double() const{
    return area();
}

template <class T>
size_t Rhomb<T>::size() const{
    return size_;
}

template <class T>
Point<T> Rhomb<T>::get_point(const int i) const{
    if ( i < 0 || i > 3){
        throw std::invalid_argument("Out of index range");
    }
    return angles[i];
}
