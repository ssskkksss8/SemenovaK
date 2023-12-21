#include <gtest/gtest.h>
#define DEBUG
#include "forward_list.h"
#include "allocator.h"

TEST(forward_list, constructor) {
    MyForwardList<int, 10, MyAllocator<int, 10>> list;
    ASSERT_TRUE(list.empty());
}

TEST(forward_list, push_front) {
    MyForwardList<int, 100, MyAllocator<int, 100>> list;
    for(auto i = 0; i < 19; ++i){
        list.push_front(i);
    }
    ASSERT_EQ(list.front(), 18);
}

TEST(forward_list, pop_front) {
    MyForwardList<int, 100, MyAllocator<int, 100>> list;
    for(auto i = 0; i < 19; ++i){
        list.push_front(i);
    }
    for(auto i = 1; i < 19; ++i){
        list.pop_front();
        ASSERT_EQ(list.front(), 19 - i - 1);
    }
    list.pop_front();
    ASSERT_TRUE(list.empty());
}

TEST(forward_list, empty) {
    MyForwardList<int, 100, MyAllocator<int, 100>> list;
    for(auto i = 0; i < 1; ++i){
        list.push_front(i);
    }
    ASSERT_FALSE(list.empty());
    list.pop_front();
    ASSERT_TRUE(list.empty());
}

TEST(forward_list, front) {
    MyForwardList<int, 10, MyAllocator<int, 10>> list;
    for(auto i = 0; i < 1; ++i){
        list.push_front(i);
    }
    ASSERT_EQ(list.front(), 0);
    list.pop_front();
    ASSERT_THROW(list.front(), std::out_of_range);
}

TEST(forward_list, clear) {
    MyForwardList<int, 10, MyAllocator<int, 10>> list;
    for(auto i = 1; i < 4; ++i){
        list.push_front(i);
    }

    list.clear();
    ASSERT_TRUE(list.empty());
}

TEST(forward_list, exp_front) {
    MyForwardList<int, 10, MyAllocator<int, 10>> list;
    ASSERT_THROW(list.front(), std::out_of_range);
}

TEST(forward_list, exp_insert_after) {
    MyForwardList<int, 10, MyAllocator<int, 10>> list;
    list.push_front(1);
    list.push_front(2);
    MyForwardList<int, 10, MyAllocator<int, 10> >::Node ptr1(1, nullptr);
    MyForwardList<int, 10, MyAllocator<int, 10> >::Node ptr2(2, &ptr1);
    MyForwardList<int, 10, MyAllocator<int, 10> >::MyIterator it1(&ptr2);
    ASSERT_THROW(list.insert_after(it1, 3), std::out_of_range);
}

TEST(forward_list_iterator, begin_n_end) {
    MyForwardList<int, 10, MyAllocator<int, 10>> list;
    for(auto i = 1; i < 4; ++i){
        list.push_front(i);
    }

    auto it = list.begin();
    ASSERT_EQ(*it, 3);
    MyForwardList<int, 10, MyAllocator<int, 10> >::MyIterator it1(nullptr);
    ASSERT_EQ(list.end(),it1);
}

TEST(forward_list_iterator, pre_increment) {
    MyForwardList<int, 10, MyAllocator<int, 10>> list;
    for(auto i = 1; i < 4; ++i){
        list.push_front(i);
    }

    auto it = list.begin();
    ++it;
    ASSERT_EQ(*it, 2);
    ++it;
    ASSERT_EQ(*it, 1);
    ++it;
    ASSERT_EQ(it, list.end());
}

TEST(forward_list_iterator, post_increment) {
    MyForwardList<int, 10, MyAllocator<int, 10>> list;
    for(auto i = 1; i < 4; ++i){
        list.push_front(i);
    }

    auto it = list.begin();
    auto it2 = it++;
    ASSERT_EQ(*it, 2);
    ASSERT_EQ(*it2, 3);
    auto it3 = it++;
    ASSERT_EQ(*it, 1);
    ASSERT_EQ(*it3, 2);
    auto it4 = it++;
    ASSERT_EQ(it, list.end());
    ASSERT_EQ(*it3, 2);
    ASSERT_EQ(*it4, 1);
}

TEST(forward_list_iterator, before_begin) {
    MyForwardList<int, 10, MyAllocator<int, 10>> list;
    for(auto i = 1; i < 4; ++i){
        list.push_front(i);
    }

    auto it = list.before_begin();
    ASSERT_EQ(*(++it), list.front());
}

TEST(forward_list_iterator, insert_after) {
    MyForwardList<int, 10, MyAllocator<int, 10>> list;
    list.push_front(1);
    list.push_front(2);
    list.push_front(3);

    list.insert_after(list.before_begin(), 1000);
    ASSERT_EQ(*(list.begin()), list.front());

    list.insert_after(list.begin(), 777);
    ASSERT_EQ(777, *(++list.begin()));
}

TEST(forward_list_iterator, loop_w_iterator) {
    MyForwardList<int, 100, MyAllocator<int, 100>> list;

    std::ostringstream os;
    std::string output = "8 7 6 5 4 3 2 1 ";

    for (auto i = 1; i < 9; ++i) {
        list.push_front(i);
    }
    for (auto it = list.begin(); it != list.end(); ++it) {
        os << *(it) << " ";
    }

    ASSERT_EQ(os.str(), output);
}

TEST(allocator_test, allocate_deallocate) {
    MyAllocator<int, 10> allocator;
    ASSERT_EQ(0, (MyAllocator<int, 10>::allocation_count));

    
    int* ptr1 = allocator.allocate(1);
    ASSERT_EQ(1, (MyAllocator<int, 10>::allocation_count));

    int* ptr2 = allocator.allocate(1);
    ASSERT_EQ(2, (MyAllocator<int, 10>::allocation_count));

    allocator.deallocate(ptr1, 1);
    ASSERT_EQ(1, (MyAllocator<int, 10>::allocation_count));

    allocator.deallocate(ptr2, 1);
    ASSERT_EQ(0, (MyAllocator<int, 10>::allocation_count));
}
TEST(allocator_test, exp_construct) {
    ASSERT_THROW((MyAllocator<int, 0>()), std::logic_error);
}

TEST(allocator_test, exp_allocate1) { 
    MyAllocator<int, 4> allocator;
    ASSERT_THROW(allocator.allocate(2), std::bad_alloc); 
}
TEST(allocator_test, exp_allocate2) { 
    MyAllocator<int, 1> allocator;
    allocator.allocate(1);
    ASSERT_THROW(allocator.allocate(1), std::bad_alloc); 
}
TEST(allocator_test, exp_deallocate) {
    MyAllocator<int, 1> allocator;
    allocator.allocate(1);
    ASSERT_THROW(allocator.deallocate(nullptr, 1), std::invalid_argument); 
}
 


int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}