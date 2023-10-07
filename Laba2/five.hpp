#pragma once

#include <string>
#include <iostream>

class Five {
public:
    Five();
    Five(const std::initializer_list<unsigned char> & t);
    Five(const std::string & t);
    Five(const Five & other) noexcept;
    Five(Five&& other) noexcept;
    Five(const size_t & n, unsigned char t = 0);
    bool operator==(const Five & t) const;
    bool operator==(const std::string & t) const;
    bool operator!=(const Five & t) const;
    bool operator!=(const std::string & t) const;
    bool operator>(const Five & t) const;
    bool operator>=(const Five & t) const;
    bool operator<(const Five & t) const;
    bool operator<=(const Five & t) const;
    Five operator+(const Five & t) const;
    Five operator-(const Five & t) const;
    size_t size() const noexcept;
    unsigned char* array() const noexcept;
    virtual ~Five() noexcept;
private:
    size_t _size;
    unsigned char* _array;
};

std::ostream& operator<<(std::ostream & os, const Five & t);