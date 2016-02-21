/* Author: Adam Werries, Email: awerries@cmu.edu
 *
 * Header for StatisticsBuffer class. Unfortunately, templated functions must be
 * visible to the compiler, so implementations of the functions are included
 * directly by this header.
 * 
 * StatisticsBuffer provides a circular buffer of DataContainer rows which
 * incrementally computes the mean and standard deviation. Algorithm taken from
 * https://en.wikipedia.org/wiki/Algorithms_for_calculating_variance#Computing_shifted_data
 */
#pragma once

#include <array>
#include <assert.h>
#include "DataContainer.h"

template <size_t T_length, size_t T_width>
class StatisticsBuffer {
public:
    StatisticsBuffer();
    void addRow(const DataContainer<T_width> & data);
    StatisticsBuffer & operator += (const DataContainer<T_width> & rhs);
    const DataContainer<T_width> getRow(unsigned int backIndex);
    const DataContainer<T_width> getLatestRow();

    const DataContainer<T_width> getMean();
    const DataContainer<T_width> getStdDev();
    size_t maxLength();
    size_t currentLength();

    enum {
        BUFFER_EMPTY = -1
    };

private:
    std::array<DataContainer<T_width>, T_length> circularBuffer_;
    int bufferIndex_ = BUFFER_EMPTY; // Will init to zero on first addition
    unsigned int n_ = 0; // current size

    DataContainer<T_width> K_;
    DataContainer<T_width> Ex_;
    DataContainer<T_width> Ex2_;
};

#include "StatisticsBuffer_impl.h"
