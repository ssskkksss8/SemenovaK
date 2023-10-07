#include  "five.hpp"
#include <algorithm>
#include <exception>

bool fivv(char c){
    return (0 <= c - '0') && (c - '0' < 5);
}

Five::Five() : _size{0}, _array{nullptr} {}

Five::Five(const size_t &n, unsigned char t)
{
    _array = new unsigned char[n];
    for (size_t i = 0; i < n; i++)
        _array[i] = t;
    _size = n;
}

//Initializer list constructor
Five::Five(const std::initializer_list<unsigned char> &t){
    _array = new unsigned char[t.size()];
    _size = t.size();
    size_t i{0};
    for (unsigned char c: t){
        if (!fivv(c)) throw std::logic_error("not five-base system");
        _array[i++] = c;
    }
}

//Copy string constructor
Five::Five(const std::string &t){
    _array = new unsigned char[t.size()];
    _size = t.size();
    for(size_t i{0}; i < _size; i++){
        if (!fivv(t[i])) throw std::logic_error("not five-base system");
        _array[i] = t[i];
    }
}

//Copy constructor
Five::Five(const Five &other) noexcept{
    _size  = other._size;
    _array = new unsigned char[_size];
    for(size_t i{0};i<_size;++i) _array[i] = other._array[i];
} 

//Move constructor
Five::Five(Five&& other) noexcept{
    _size = other._size;
    _array = other._array;
    other._size = 0;
    other._array = nullptr;
}

Five::~Five() noexcept {
    if (_size > 0) {
        _size = 0;
        delete[] _array;
        _array = nullptr;
    }
}

size_t Five::size() const noexcept {
    return _size;
}

unsigned char* Five::array() const noexcept {
    return _array;
}

std::ostream& operator<<(std::ostream & os, const Five & t) {
    size_t i = t.size();
    while(i--) {
        os << t.array()[i];
    }
    return os;
}

bool Five::operator==(const Five & t) const {
    if (_size != t._size) {
        return false;
    }
    for (size_t i = 0; i < _size; i++) {
        if (_array[i] != t._array[i]) {
            return false;
        }
    }
    return true;
}

bool Five::operator==(const std::string & t) const {
    if (_size != t.size()) {
        return false;
    }
    size_t i = _size - 1;
    for (char c : t) {
        if (c != _array[i]) {
            return false;
        }
        --i;
    }
    return true;
}

bool Five::operator!=(const Five & t) const {
    return !(*this == t);
}

bool Five::operator!=(const std::string & t) const {
    return !(*this == t);
}

bool Five::operator>(const Five & t) const {
    if (_size != t.size()){
        return _size > t.size();
    }
    for (size_t i{_size - 1}; i >= 0; i++){
        if (_array[i] < t.array()[i]){
            return false;
        }
        return true;
    }
}

bool Five::operator>=(const Five & t) const {
    return (*this > t) || (*this == t);
}

bool Five::operator<(const Five &t) const {
    return !(*this >= t);
}

bool Five::operator<=(const Five & t) const {
    return !(*this > t);
}

void del_nul(std::string & s) {
    int zer = 0;
    size_t i = 0;
    while(s[i] == '0') {
        ++zer;
        ++i;
        }
    s.erase(0, zer);
    std::reverse(s.begin(), s.end());
}

Five Five::operator+(const Five & t) const {
    size_t len = std::max(_size, t.size()) + 1;
    std::string summ(len, '0');
    for (size_t i{0}; i < len - 1; i++){
        int summa = (((i < _size) ? _array[i] - '0' : 0) + ((i < t._size) ? t._array[i] - '0' : 0));
        summ[i + 1] = (summa / 5) + '0';
        summ[i] = (summ[i] - '0' + summa) % 5 + '0';
    }
    std::reverse(summ.begin(), summ.end());
    del_nul(summ);
    return Five(summ);
}

Five Five::operator-(const Five & t) const {
    if (*this < t){
        throw std::logic_error("can't be negative");
    }
    if (*this == t){
        return Five("0");
    }
    size_t len = std::max(_size, t.size());
    std::string raz(len, '0');
    for (size_t i{0}; i < len - 1; i++){
        raz[i] += _array[i] - '0' - ((i < t._size) ? t._array[i] - '0' : 0);
        if (raz[i] - '0' < 0) {
            raz[i] += 5;
            raz[i + 1] -= 1;
        }
    }
    raz[len - 1] += _array[len - 1] - '0' - ((len == t._size) ? t._array[len - 1] - '0' : 0);
    std::reverse(raz.begin(), raz.end());
    del_nul(raz);
    return Five(raz);
}