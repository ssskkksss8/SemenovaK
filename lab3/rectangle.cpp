#include "rectangle.hpp"

Rectangle::Rectangle() : angles{Point(), Point(), Point(), Point()} {}

Rectangle::Rectangle(Point& p1, Point& p2, Point& p3, Point& p4) :
         angles{p1, p2, p3, p4} {}

Point Rectangle::center() const {
    //std::cout << "Rectangle center() " << std::endl;
    double xc = 0, yc = 0;
    for(size_t i = 0; i < 4; ++i){
        xc += angles[i].x_;
        yc += angles[i].y_;
    }
    return Point(xc / 4.0, yc / 4.0);
}

double Rectangle::area() const {
    double x1 = angles[0].x_; double y1 = angles[0].y_;
    double x2 = angles[1].x_; double y2 = angles[1].y_;
    double x3 = angles[2].x_; double y3 = angles[2].y_;
    double x4 = angles[3].x_; double y4 = angles[3].y_;
    Point center = this->center();
    double a = sqrt(pow((x1 - center.x_),2) + pow((y1 - center.y_),2));
    double b = sqrt(pow((x2 - center.x_),2) + pow((y2 - center.y_),2));
    double area = a * b;
    return area;
}

Rectangle&Rectangle::operator=(const Rectangle& right){
    if (this != &right) {
        for(size_t i = 0; i < 4; ++i){
            angles[i] = right.angles[i];
        }
    }
    return *this;
}

Rectangle&Rectangle::operator=(Rectangle&& right){
    if (this != &right) {
        for(size_t i = 0; i < 4; ++i){
            angles[i] = std::move(right.angles[i]);
        }
    }
    return *this;
}

bool Rectangle::operator==(const Rectangle& right){
    for(size_t i = 0; i < 4; ++i){
        if(angles[i] != right.angles[i]){
            return false;
        }
    }
    return true;
}


std::ostream& operator<<(std::ostream& os, const Rectangle& f){
    os << "Rectangle's coordinates:"<< std::endl;
    for(size_t i = 0; i < 4; ++i){
        os << f.angles[i] << std::endl;
    }
    return os;

}
std::istream& operator>>(std::istream& is,Rectangle& f){
    std::cout << "|EnterRectangle's coordinates|" << std::endl;
    for(size_t i = 0; i < 4; ++i){
        is >> f.angles[i];
    }
    return is;
}

Rectangle::operator double() const{
    return area();
}

Point Rectangle::get_point(const int i) const{
    if ( i <= 0 || i >= 4){
        throw std::invalid_argument("Out of index range");
    }
    return angles[i];
}