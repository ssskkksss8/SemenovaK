#pragma once
#include<iostream>
#include "figure.hpp"

class Vector
{
public:
    Vector();

    bool          is_empty() const;
    void          resize(int new_size);
    int           size() const;
    void          push_back(Figure* val);
    void          pop_back();
    void          set(int ind, Figure* val);
    const Figure* get(int ind) const;
    void          remove(int ind);

    ~Vector();

private:
    Figure** buf;
    int size_;
    int cap;
    int head;
};