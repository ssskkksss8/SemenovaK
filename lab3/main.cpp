#include <iostream>
#include <string>
#include "vector.hpp"

#include "point.hpp"
#include "figure.hpp"
#include "rectangle.hpp"
#include "trapezoid.hpp"
#include "rhomb.hpp"


double sum_area(const Vector& arr){
    double sum = 0;
    for(int i = 0; i < arr.size(); ++i){
        sum += arr.get(i)->area();
    }
    return sum;
}


int main(){
    Rhomb t;
    Rectangle h;
    Trapezoid o;
    std::cin >> t >> h >> o; // >> o;

    Vector arr;

    arr.push_back(&t);
    arr.push_back(&h);
    arr.push_back(&o);

    for (int i = 0; i < arr.size(); ++i) {
        std::cout << "Geometric center of figure " << i + 1 << ": " << arr.get(i)->center() << std::endl;
        std::cout << "Area of figure " << i + 1 << ": " << arr.get(i)->area() << std::endl;
    }

    std::cout << "Total area of figures: " << sum_area(arr) << std::endl;
    arr.remove(0);
    std::cout << "Total area of figures: " << sum_area(arr) << std::endl;
    return 0;
}
