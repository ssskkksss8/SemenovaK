#pragma once

#include <iostream>
#include <string>

template<class T>
class Point{
    template<class F>
    friend Point<F> operator+(const Point<F>& left, const Point<F>& right);
    template<class F>
    friend Point<F> operator-(const Point<F>& left, const Point<F>& right);
    template<class F>
    friend bool operator==(const Point<F>& left, const Point<F>& right);
    template<class F>
    friend bool operator!=(const Point<F>& left, const Point<F>& right);
    template<class F>
    friend bool operator>(const Point<F>& left, const Point<F>& right);
    template<class F>
    friend bool operator<(const Point<F>& left, const Point<F>& right);
    template<class F>
    friend bool operator>=(const Point<F>& left, const Point<F>& right);
    template<class F>
    friend bool operator<=(const Point<F>& left, const Point<F>& right);
    template<class F>
    friend std::istream& operator>>(std::istream& is, Point<F>& p);
    template<class F>
    friend std::ostream& operator<<(std::ostream& os, const Point<F>& p);

public:
    Point();
    Point(T x, T y);
    Point(const Point<T>& other);

    Point<T>& operator=(const Point<T>& right);

    T x_{};
    T y_{};
};

template<class T>
Point<T>::Point() : x_{0}, y_{0} {}

template<class T>
Point<T>::Point(T x, T y): x_{x}, y_{y} {}

template<class T>
Point<T>::Point(const Point<T>& other) : x_(other.x_), y_(other.y_) {}

template<class T>
Point<T> operator+(const Point<T>& left, const Point<T>& right){
    return Point<T>(left.x_ + right.x_, left.y_ + right.y_);
}

template<class T>
Point<T> operator-(const Point<T>& left, const Point<T>& right){
    return Point<T>(left.x_ - right.x_, left.y_ - right.y_);
}

template<class T>
bool operator==(const Point<T>& left, const Point<T>& right){
    return (left.x_ == right.x_) && (left.y_ == right.y_);
}

template<class T>
bool operator!=(const Point<T>& left, const Point<T>& right){
    return (left.x_ != right.x_) || (left.y_ != right.y_);
}

template<class T>
Point<T>& Point<T>::operator=(const Point<T>& right){
    if (this != &right) {
        x_ = right.x_;
        y_ = right.y_;
    }
    return *this;
}

template<class T>
bool operator<(const Point<T>& left, const Point<T>& right) {
    return (left.x_ < right.x_) || ((left.x_ == right.x_) && (left.y_ < right.y_));
}

template<class T>
bool operator>(const Point<T>& left, const Point<T>& right) {
    return (left.x_ > right.x_) || ((left.x_ == right.x_) && (left.y_ > right.y_));
}

template<class T>
bool operator<=(const Point<T>& left, const Point<T>& right) {
    return (left < right) || (left == right);
}

template<class T>
bool operator>=(const Point<T>& left, const Point<T>& right) {
    return (left > right) || (left == right);
}

template<class T>
std::istream& operator>>(std::istream& is, Point<T>& p){
    T x, y;
    std::cout << "Enter 'x' and 'y' :" << std::endl;
    is >> x >> y;

    p.x_ = x;
    p.y_ = y;
    return is;
}

template<class T>
std::ostream& operator<<(std::ostream& os, const Point<T>& p){
    os << "(x: " << p.x_ << "; y: " << p.y_ << ")";
    return os;
}