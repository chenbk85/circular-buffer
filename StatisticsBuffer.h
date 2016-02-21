/* Author: Adam Werries, Email: awerries@cmu.edu
 *
 * Header for StatisticsBuffer class. Unfortunately, templated functions must be
 * visible to the compiler, so implementations of the functions are included
 * directly by this header.
 * 
 */
#pragma once
#include <array>
#include <assert.h>
#include "DataContainer.h"

/**
 * A class providing a circular buffer of DataContainer rows, incrementally 
 * computing the mean and standard deviation for each column. Algorithm taken from
 * https://en.wikipedia.org/wiki/Algorithms_for_calculating_variance#Computing_shifted_data
 */
template <size_t T_length, size_t T_width>
class StatisticsBuffer {
public:
    /**
     * Constructor, initializes internal K_, Ex_, and Ex2_ variables used for incrementally
     * keeping track of mean and standard-deviation.
     */
    StatisticsBuffer();

    /**
     * Adds a copy of the input row to the circular buffer, cycling out the oldest entry if necessary.
     * Incrementally adds the new entries to the stats, and removes old entries.
     *
     * @param data  the DataContainer instance to be added.
     */
    void addRow(const DataContainer<T_width> & data);

    /**
     * Removes the oldest row from the circular buffer. Simply calls removeRows(1);
     * Decrementally removes old entries from the stats.
     *
     */
    void removeRow();

    /**
     * Removes the oldest numRowsToRemove from the circular buffer.
     * Decrementally removes old entries from the stats. If there are less rows than
     * specified, it stops after removing what it can.
     *
     */
    void removeRows(unsigned int numRowsToRemove);

    /**
     * Adds a copy of the input row to the circular buffer, cycling out the oldest entry if necessary.
     * Simply calls the addRow() method.
     *
     * @param rhs  the DataContainer instance to be added
     * @return     a reference to the current StatisticsBuffer
     * @see #addRow(const DataContainer<T_width> & data)
     */
    StatisticsBuffer & operator += (const DataContainer<T_width> & rhs);

    /**
     * Returns the row specified by the index, in chronological order from oldest to newest.
     * Asserts that the current instance is not empty! Avoid this by checking isEmpty() yourself.
     *
     * @param index  the instance to be returned
     * @return       a copy of the DataContainer requested
     */
    const DataContainer<T_width> getRow(unsigned int index);

    /**
     * Returns the row most recently added. Equivalent to getRow(currentLength() - 1).
     * Asserts that the current instance is not empty! Avoid this by checking isEmpty() yourself.
     *
     * @return       a copy of the DataContainer requested
     */
    const DataContainer<T_width> getLatestRow();

    /**
     * Returns the current mean of each column of the StatisticsBuffer as a DataContainer.
     * Asserts that the current instance is not empty! Avoid this by checking isEmpty() yourself.
     *
     * @return a new DataContainer containing the mean of each column.
     */
    const DataContainer<T_width> getMean();

    /**
     * Returns the current standard deviation of each column of the StatisticsBuffer as a DataContainer.
     * Asserts that the current instance is not empty! Avoid this by checking isEmpty() yourself.
     *
     * @return a new DataContainer containing the standard deviation of each column.
     */
    const DataContainer<T_width> getStdDev();

    /**
     * Returns the maximum length (number of rows) of the StatisticsBuffer. 
     *
     * @return a size_t value of the maximum number of rows.
     */
    size_t maxLength();

    /**
     * Returns the current length (number of rows) of the StatisticsBuffer. 
     *
     * @return a size_t value of the current number of rows.
     */
    size_t currentLength();

    /**
     * Returns true if the StatisticsBuffer no longer contains any entries, otherwise false.
     *
     * @return boolean result of test
     */
    bool isEmpty();

    /**
     * Returns true if the StatisticsBuffer is full, otherwise false.
     * Note that this does NOT imply that entries cannot be added.
     *
     * @return boolean result of test
     */
    bool isFull();

private:
    /**
     * The internal representation of the circular buffer.
     */
    std::array<DataContainer<T_width>, T_length> circularBuffer_;
    /**
     * Index of the circularBuffer corresponding to the oldest entry.
     */
    int headIndex_ = 0;
    /**
     * Index of the circularBuffer corresponding to the newest entry.
     */
    int tailIndex_ = -1; // -1 so we can pre-increment in addRow
    /**
     * Current length of the buffer. Easier to keep track of than trying to find
     * differences between headIndex and tailIndex
     */
    unsigned int numRows_ = 0; // current size

    /**
     * Internal "location parameter", used to ensure subtractions are not too far from the mean.
     */
    DataContainer<T_width> K_;
    /**
     * Internal parameter containing the difference between the datapoint and the location parameter
     */
    DataContainer<T_width> Ex_;
    /**
     * Internal parameter containing the square of Ex_
     */
    DataContainer<T_width> Ex2_;
};

#include "StatisticsBuffer_impl.h"
