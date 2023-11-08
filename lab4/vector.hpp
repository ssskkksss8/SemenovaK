#pragma once
#include <iostream>
#include <memory>

template <class T>
class Vector
{
public:
    Vector();
    bool is_empty() const;
    void resize(int new_size);
    int size() const;
    void push_back(T val);
    void pop_back();
    void set(int ind, T val);
    const T& get(int ind) const;
    void remove(int ind);

    ~Vector();

private:
    std::unique_ptr<T[]> buf;
    int size_;
    int cap;
};

template <class T>
Vector<T>::Vector()
    : buf(nullptr), size_(0), cap(0)
{
}

template <class T>
bool Vector<T>::is_empty() const
{
    return size_ == 0;
}

template <class T>
void Vector<T>::resize(int new_size)
{
    std::unique_ptr<T[]> new_buf = std::make_unique<T[]>(new_size);
    for (int i = 0; i < size_ && i < new_size; ++i)
    {
        new_buf[i] = std::move(buf[i]);
    }
    buf = std::move(new_buf);
    cap = new_size;
    if (size_ > cap)
    {
        size_ = cap;
    }
}

template <class T>
int Vector<T>::size() const
{
    return size_;
}

template <class T>
void Vector<T>::push_back(T val)
{
    if (size_ == cap)
    {
        int new_cap = (cap == 0) ? 1 : cap * 2;
        resize(new_cap);
    }
    buf[size_] = std::move(val);
    ++size_;
}

template <class T>
void Vector<T>::pop_back()
{
    if (size_ > 0)
    {
        --size_;
    }
}

template <class T>
void Vector<T>::set(int ind, T val)
{
    if (ind >= 0 && ind < size_)
    {
        buf[ind] = std::move(val);
    }
}

template <class T>
const T& Vector<T>::get(int ind) const
{
    static T null_val;
    if (ind >= 0 && ind < size_)
    {
        return buf[ind];
    }
    return null_val;
}

template <class T>
void Vector<T>::remove(int ind)
{
    if (ind >= 0 && ind < size_)
    {
        for (int i = ind; i < size_ - 1; ++i)
        {
            buf[i] = std::move(buf[i + 1]);
        }
        --size_;
    }
}

template <class T>
Vector<T>::~Vector()
{
}