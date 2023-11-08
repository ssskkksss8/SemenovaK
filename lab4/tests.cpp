#include <gtest.h>
#include "point.hpp"
#include "rhomb.hpp"
#include "rectangle.hpp"
#include "trapezoid.hpp"


TEST(point_test, def_constructor){
    Point<int> p;
    ASSERT_EQ(p.x_, 0);
    ASSERT_EQ(p.y_, 0);
}

TEST(point_test, double_constructor){
    Point<double> p(1.0,3.0);
    ASSERT_EQ(p.x_, 1.0);
    ASSERT_EQ(p.y_, 3.0);
}

TEST(point_test, point_constructor){
    Point<double> p1(3.6, 3.4);
    Point<double> p(p1);
    ASSERT_EQ(p.x_, p1.x_);
    ASSERT_EQ(p.y_, p1.y_);
}

TEST(point_test, assignment_empty){
    Point<double> p1;
    Point<double> p;
    p = p1;
    ASSERT_EQ(p.x_, p1.x_);
    ASSERT_EQ(p.y_, p1.y_);
}

TEST(point_test, assignment){
    Point<double> p1(3.6, 3.4);
    Point<double> p;
    p = p1;
    ASSERT_EQ(p.x_, p1.x_);
    ASSERT_EQ(p.y_, p1.y_);
}

TEST(point_test, equality_empty){
    Point<double> p1;
    Point<double> p;
    ASSERT_TRUE(p == p1);
}

TEST(point_test, equality){
    Point<double> p1(3.6, 3.4);
    Point<double> p(p1);
    ASSERT_TRUE(p == p1);
}

TEST(point_test, addition_empty){
    Point<double> p1;
    Point<double> p;
    ASSERT_EQ(p + p1, p);
}

TEST(point_test, addition){
    Point<double> p1{2.3, -10};
    Point<double> p{3.4, 10.5};
    Point<double> p3 = p + p1;
    
    ASSERT_EQ(p1 + p, p3);
}

TEST(point_test, subtraction_empty){
    Point<double> p1;
    Point<double> p;
    ASSERT_EQ(p - p1, p);
}

TEST(point_test, subtraction){
    Point<double> p1{2.3,-10};
    Point<double> p{3.4, 10.05};
    Point<double> rez{1.1, 20.05};
    ASSERT_EQ(p - p1, rez);
}

TEST(point_test, input) {
    std::stringstream input("1 1");
    Point<int> tr1{1, 1};
    Point<int> tr2;
    input >> tr2;
    ASSERT_TRUE(tr1 == tr2);
}

TEST(point_test, input1) {
    Point<int> tr1{1,3};
    std::stringstream input("1 1");

    Point<int> tr2;
    input >> tr2;
    ASSERT_FALSE(tr1 == tr2);
}

TEST(point_test, output) {
    Point<int> p1(1, 3);

    std::ostringstream os;
    os << p1;
    std::string output = "(x: 1; y: 3)";
    ASSERT_EQ(os.str(), output);
}

TEST(point_test, output_empty) {
    Point<int> p1;

    std::ostringstream os;
    os << p1;
    std::string output = "(x: 0; y: 0)";
    ASSERT_EQ(os.str(), output);
}

TEST(point_test, less) {
    Point<double> p1(1, 4);
    Point<double> p2(2, 5);
    ASSERT_TRUE(p1 < p2);
}

TEST(point_test, greater) {
    Point<double> p1(1, 4);
    Point<double> p2(2, 5);
    ASSERT_TRUE(p2 > p1);
}


int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}