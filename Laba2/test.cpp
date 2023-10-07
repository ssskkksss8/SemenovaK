#include <gtest/gtest.h>
#include "five.hpp"

TEST(equal, test01) {
    Five num1("1044"), num2("1044");
    ASSERT_TRUE(num1 == num2);
}

TEST(equal, test02) {
    Five num1("100"), num2("100");
    ASSERT_FALSE(num1 != num2);
}


TEST(not_equal, test01) {
    Five num1("21"), num2("21");
    ASSERT_FALSE(num1 > num2);
}

TEST(not_equal, test02) {
    Five num1("2"), num2("100");
    ASSERT_TRUE(num1 <= num2);
}



TEST (operations, test01) {
    Five num1("104"), num2("103");
    ASSERT_TRUE(num1 + num2 == Five("212"));
}

TEST(operations, test02) {
    Five num1("144"), num2("102");
    ASSERT_TRUE(num1 + num2 == Five("42"));
}
TEST(operations, test03) {
    Five num1("144432"), num2("102112");
    ASSERT_TRUE(num1 - num2 == Five("42320"));
}

TEST(operations, test04) {
    Five num1("32"), num2("102");
    ASSERT_TRUE(num1 - num2 == "can't be negative");
}

int main2(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}