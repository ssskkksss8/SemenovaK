
#include "five.hpp"
#include <iostream>

int main(){
    try {
        Five a = {'0', '0', '1'};
        std::cout << a << std::endl;
        Five b = {'4', '0', '2'};
        std::cout << (a + b) << std::endl;
        std::cout << (a == b) << std::endl;
        std::cout << (a != b) << std::endl;
        std::cout << (a > b) << std::endl;
        std::cout << (a - b) << std::endl;
    } catch(const std::exception& e) {
        std::cerr << e.what() << '\n';
    }
    return 0;
}
