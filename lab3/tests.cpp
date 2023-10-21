#include <gtest/gtest.h>
#include "rectangle.hpp"
#include "trapezoid.hpp"
#include "rhomb.hpp"

TEST(rectangle_test, area_of_empty){
    Rectangle tr;
    ASSERT_EQ(tr.area(), 0.0);
}

TEST(rectangle_test, area){
    Point p1(4, 2);
    Point p2(0, 2);
    Point p3(0, -1);
    Point p4(4, -1);

    Rectangle tr(p1,p2,p3, p4);
    ASSERT_EQ(tr.area(), 6.25);
}

TEST(trapezoid_test, area_of_empty){
    Trapezoid tr;
    ASSERT_EQ(tr.area(), 0.0);
}

TEST(trapezoid_test, area){
    Point p1(3, 3);
    Point p2(-1, 3);
    Point p3(-3, -2);
    Point p4(5, -2);

    Trapezoid tr(p1, p2, p3, p4);
    ASSERT_EQ(tr.area(), 30);
    
}

TEST(rhomb_test, area_of_empty){
    Rhomb tr;
    ASSERT_EQ(tr.area(), 0);
}


TEST(rhomb_test, area){
    Point p1(2, 7);
    Point p2(-1, 3);
    Point p3(2, -1);
    Point p4(5, 3);

    Rhomb tr(p1, p2, p3, p4);
    ASSERT_EQ(tr.area(), 24);
    
}



int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
