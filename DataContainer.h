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

/**
 * A class for augmenting a double std::array. Defines operators for +, -, /,
 * +=, and -=, along with Pow and Sqrt functions.
 *
 */
template<size_t T_width>
class DataContainer : public std::array<double, T_width> {
public:
    /**
     * Returns a new DataContainer from the addition of two DataContainers. 
     * The DataContainers must be the same length.
     * This method simply calls the += operator.
     *
     * Example: d3 = d1 + d2;
     *
     * "this" is the left-hand-side of the + operator.
     * @param rhs   the DataContainer instance on the right-hand-side of the + operator.
     * @return      the new DataContainer containing the results
     */
    const DataContainer<T_width> operator + (const DataContainer<T_width> &rhs);

    /**
     * Returns a new DataContainer from the subtraction of two DataContainers. 
     * The DataContainers must be the same length.
     * This method simply calls the -= operator.
     *
     * Example: d3 = d1 - d2;
     *
     * "this" is the left-hand-side of the - operator.
     * @param rhs   the DataContainer instance on the right-hand-side of the - operator.
     * @return      the new DataContainer containing the results
     */
    const DataContainer<T_width> operator - (const DataContainer<T_width> &rhs);

    /**
     * Returns a new DataContainer from the division of a DataContainer by a constant.
     *
     * Example: d3 = d1 / 5;
     *
     * "this" is the left-hand-side of the / operator.
     * @param rhs   the constant on the right-hand-side of the / operator.
     * @return      the new DataContainer containing the reuslts
     */
    const DataContainer<T_width> operator / (const double constant);

    /**
     * Adds a DataContainer to the current DataContainer.
     * The DataContainers must be the same length.
     *
     * Example: d3 += d2;
     *
     * "this" is the left-hand-side of the += operator.
     * @param rhs   the DataContainer instance on the right-hand-side of the += operator.
     * @return      returns reference to "this"
     */
    DataContainer<T_width>& operator += (const DataContainer &rhs);

    /**
     * Subtracts a DataContainer from the current DataContainer.
     * The DataContainers must be the same length.
     *
     * Example: d3 -= d2;
     *
     * "this" is the left-hand-side of the -= operator.
     * @param rhs   the DataContainer instance on the right-hand-side of the -= operator.
     * @return      returns reference to "this"
     */
    DataContainer<T_width>& operator -= (const DataContainer &rhs);

    /**
     * Returns a new DataContainer with each element to the power of the exponent parameter.
     *
     * Example: d3 = d2.Pow(2);
     *
     * @param exponent   the exponent to be applied
     * @return           a new DataContainer containing the results
     */
    const DataContainer<T_width> Pow(const double exponent);

    /**
     * Returns a new DataContainer with the square-root of each element.
     *
     * Example: d3 = d2.Sqrt();
     *
     * @return           a new DataContainer containing the results
     */
    const DataContainer<T_width> Sqrt(); 


    /**
     * Returns an ostream object with a print-out of the DataContainer.
     * Defined as friend-function to allow chaining.
     *
     * Example: std::cout << data;
     *
     * @param os    ostream object, the left-hand side of the operator
     * @param data  DataContainer to be printed
     * @return      reference to the same input ostream object with added content
     */
    template <size_t T>
    friend std::ostream& operator << (std::ostream &os, const DataContainer<T> &data);
};

#include "DataContainer_impl.h"
