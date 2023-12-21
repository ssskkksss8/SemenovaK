#pragma once

#include <iostream>
#include <vector>
#include <memory>

template <typename T, size_t Block_count>
class MyAllocator {
public:

    #ifdef DEBUG
        static size_t allocation_count;
        static size_t block_allocation_count;
    #endif

    template <typename U>
    struct rebind {
        using other = MyAllocator<U, Block_count>;
    };
    
    using value_type = T;
    using pointer = T*;
    using const_pointer = const T*;
    using size_type = size_t;

    MyAllocator() {
        if(Block_count == 0){
            throw std::logic_error("Block size must be positive");
        }
        buffer = new value_type[Block_count];
        for(size_t i = 0; i < Block_count; ++i){
            free_blocks.push_back(std::make_pair(buffer + i, false));//контейнер для отлеживания блоков памяти
        }
    }

    ~MyAllocator(){
        delete[] buffer;
    }

    template <typename U>
    MyAllocator(const MyAllocator<U, Block_count>&) noexcept {}

    pointer allocate(size_type n) {
        #ifdef DEBUG
            allocation_count += n;
        #endif

        if (n != 1)
            throw std::bad_alloc();
        
        auto it = std::find_if(free_blocks.begin(), free_blocks.end(), [](const auto& pair) {
            return !pair.second;
        });
        
        if (it == free_blocks.end()) {
            throw std::bad_alloc();
        }
        
        it->second = true;
        return it->first;
    }

    void deallocate(pointer p, size_type n) {
        #ifdef DEBUG
            allocation_count -= n;
        #endif

        if (n != 1)
            return;
        
        auto it = std::find_if(free_blocks.begin(), free_blocks.end(), [p](const auto& pair) {
            return pair.first == p;
        });
        
        if (it == free_blocks.end()) {
            throw std::invalid_argument("Invalid pointer");
        }
        
        it->second = false;
    }

    template <typename U, typename... Args>
    void construct(U *p, Args &&...args){
        new (p) U(std::forward<Args>(args)...);
    }

    void destroy(pointer p) {
        p->~T();
    }

private:
    std::vector<std::pair<pointer, bool>> free_blocks;
    pointer buffer;
};

#ifdef DEBUG
    template <typename T, size_t Block_count>
    size_t MyAllocator<T, Block_count>::allocation_count = 0;
#endif