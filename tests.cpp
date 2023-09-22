#include <gtest/gtest.h>
#include "my_foo1.hpp"

TEST(test01, my_foo1) {
    ASSERT_TRUE(foo("") == "");
}

TEST(test02, my_foo1) {
    ASSERT_TRUE(foo("abbcc") == "baacc");
}

TEST(test03, my_foo1) {
    ASSERT_TRUE(foo("aabba") == "bbaab");
}

TEST(test04, my_foo1) {
    ASSERT_TRUE(foo("ababc") == "babac");
}

TEST(test05, my_foo1) {
    ASSERT_TRUE(foo("abn") == "invalid input data");
}

TEST(test06, my_foo1) {
    ASSERT_TRUE(foo("abc8") == "invalid input data");
}

TEST(test07, my_foo1) {
    ASSERT_TRUE(foo("abas!") == "invalid input data");
}
int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}