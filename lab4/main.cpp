#include <iostream>
#include <string>
#include "vector.hpp"

#include "point.hpp"
#include "figure.hpp"
#include "trapezoid.hpp"
#include "rhomb.hpp"
#include "rectangle.hpp"


template<typename T>
double sum_area(const Vector<T>& arr){
    double sum = 0;
    for(int i = 0; i < arr.size(); ++i){
        sum += arr.get(i)->area();
    }
    return sum;
}


int main(){
    try{
        std::unique_ptr<Rhomb<double>> t = std::make_unique<Rhomb<double>>();
        std::unique_ptr<Trapezoid<double>> h = std::make_unique<Trapezoid<double>>();
        std::unique_ptr<Rectangle<double>> o = std::make_unique<Rectangle<double>>();
        
        std::cin >> *t >> *h >> *o;
        std::cout << *t << *h << *o;


        Vector<std::unique_ptr<Figure<double>>> arr;

        arr.push_back(std::move(t));
        arr.push_back(std::move(h));
        arr.push_back(std::move(o));

        for (int i = 0; i < arr.size(); ++i) {
            std::cout << "Geometric center of figure " << i + 1 << ": " << arr.get(i)->center() << std::endl;
            std::cout << "Area of figure " << i + 1 << ": " << arr.get(i)->area() << std::endl;
        }

        std::cout << "Total area of figures: " << sum_area(arr) << std::endl;
        arr.remove(0);
        std::cout << "Total area of figures: " << sum_area(arr) << std::endl;
        
        Point<double> p1(1,2), p2(-1,4), p3(3,2), p4(1,-2), p5(-1,2) ,p6(-4,2), p7(3,-1), p8(-1,-4);

        auto h_p1 = std::make_unique<Trapezoid<double>>(p3,p7,p5,p1);
        auto o_p1 = std::make_unique<Rectangle<double>>(p1,p2,p3,p4);
        arr.push_back(std::move(o_p1));
        arr.push_back(std::move(h_p1));
        return 0;
    } catch(const std::exception& e) {
        std::cerr << e.what() << '\n';
    }
}
