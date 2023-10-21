#include "rhomb.hpp"

Rhomb::Rhomb() : angles{Point(), Point(), Point(), Point()} {}

Rhomb::Rhomb(Point& p1, Point& p2, Point& p3, Point& p4) : angles{p1, p2, p3, p4} {}

Point Rhomb::center() const {
    //std::cout << "Rhomb center() " << std::endl;
    double xc = 0, yc = 0;
    for(size_t i = 0; i < 4; ++i){
        xc += angles[i].x_;
        yc += angles[i].y_;
    }
    return Point(xc / 4.0, yc / 4.0);
}

double Rhomb::area() const {
    //std::cout << "Rhomb area() " << std::endl;
    double x1 = angles[0].x_; double y1 = angles[0].y_;
    double x2 = angles[1].x_; double y2 = angles[1].y_;
    Point center = this->center();
    double d1 = sqrt(pow((x1 - center.x_),2) + pow((y1 - center.y_),2));
    double d2 = sqrt(pow((x2 - center.x_),2) + pow((y2 - center.y_),2));
    double area = (d1 * d2) * 2;
    return area;
}

Rhomb& Rhomb::operator=(Rhomb&& right){
    if (this != &right) {
        for(size_t i = 0; i < 4; ++i){
            angles[i] = std::move(right.angles[i]);
        }
    }
    return *this;
}

Rhomb& Rhomb::operator=(const Rhomb& right){
    if (this != &right) {
        for(size_t i = 0; i < 4; ++i){
            angles[i] = right.angles[i];
        }
    }
    return *this;
}


bool Rhomb::operator==(const Rhomb& right){
    for(size_t i = 0; i < 4; ++i){
        if(angles[i] != right.angles[i]){
            return false;
        }
    }
    return true;
}


std::ostream& operator<<(std::ostream& os, const Rhomb& f){
    os << "Rhomb's coordinates:"<< std::endl;
    for(size_t i = 0; i < 4; ++i){
        os << f.angles[i] << std::endl;
    }
    return os;

}

std::istream& operator>>(std::istream& is, Rhomb& f){
    std::cout << "|Enter Rhomb's coordinates|" << std::endl;
    for(size_t i = 0; i < 4; ++i){
         is >> f.angles[i];
    }
    return is;
}

Rhomb::operator double() const{
    return area();
}

Point Rhomb::get_point(const int i) const{
    if ( i <= 0 || i >= 4){
        throw std::invalid_argument("Out of index range");
    }
    return angles[i];
}