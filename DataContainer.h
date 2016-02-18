/* Author: Adam Werries, Email: awerries@cmu.edu
 *
 * Header for DataContainer class. Unfortunately, templated functions must be
 * visible to the compiler, so implementations of the functions are included
 * directly by this header.
 */
#pragma once
#include <array>
#include <cstdlib>
#include <iterator>
#include <iostream>
#include <algorithm>

template<size_t T_width>
class DataContainer : public std::array<double, T_width> {
public:
    DataContainer<T_width>& operator + (const DataContainer<T_width> &data);
    DataContainer<T_width>& operator - (const DataContainer<T_width> &data);
    DataContainer<T_width>& operator / (const double constant);
    DataContainer<T_width>& operator += (const DataContainer &rhs);
    DataContainer<T_width>& operator -= (const DataContainer &data);
    DataContainer<T_width> Pow(const double exponent);
    DataContainer<T_width> Sqrt();
    void Print();
};

#include "DataContainer_impl.h"
