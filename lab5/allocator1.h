
#include <iostream>
#include <vector>
#include <memory>

template <typename T, size_t Block_size>
class MyAllocator {
public:
    using value_type = T;
    using pointer = T*;
    using size_type = size_t;

    template <typename U>
    struct rebind {
        using other = MyAllocator<U, Block_size>;
    };

    MyAllocator() noexcept {}

    template <typename U>
    MyAllocator(const MyAllocator<U, Block_size>&) noexcept {}

    pointer allocate(size_type n) {
        if (n != 1)
            throw std::bad_alloc();
        if (pos == nullptr || static_cast<size_type>(end - pos) < n){
            data_.push_back(new value_type[Block_size]);
            pos = data_.back();
            end = pos + Block_size;
            //std::cout << "pos & end : " << pos << " " << end << "diff : " << static_cast<size_type>(end - pos) << "\n";
        }
        auto p = pos;
        pos += n;
        return p;
    }

    void deallocate(pointer p, size_type n) {
        //std::cout << "dealloc: " << pos << "p: "<< p <<"\n";
        if (n != 1) return;
        if (p == pos - n) {
            pos -= n;
            return;
        }
        auto it = std::find(data_.begin(), data_.end(), p);
        if (it != data_.end()) {
            delete[] *it;
            data_.erase(it);
        }
    }

private:
    std::vector<pointer> data_;
    pointer pos = nullptr;
    pointer end = nullptr;
};