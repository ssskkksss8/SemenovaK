#include <iostream>
#include <map>
#include "allocator.h"
#include "forward_list.h"

int factorial(int n) {
    if (n == 0 || n == 1) {
        return 1;
    } else {
        return n * factorial(n - 1);
    }
}

int main() {
    std::map<int, int, std::less<>, MyAllocator<std::pair<const int, int>, 10>> map_;
    
    for (int i = 0; i < 10; i++) {
        map_[i] = factorial(i);
        if(i == 6){
            map_.erase(2);
        }
        std::cout << "i = " << i << "\n";
    }
     
    for (const auto& pair : map_) {
        std::cout << pair.first << " " << pair.second << std::endl;
    }
    
    MyForwardList<int, 100, MyAllocator<int, 100>> list;
    
    for (int i = 0; i < 10; i++) {
        list.push_front(i);
    }
    
    for (const auto& value : list) {
        std::cout << value << " ";
    }
    std::cout << std::endl;
    
    return 0;
}