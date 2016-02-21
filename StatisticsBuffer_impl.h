#include "StatisticsBuffer.h"

template <size_t T_length, size_t T_width>
StatisticsBuffer<T_length, T_width>::StatisticsBuffer() {
    this->K_.fill(0);
    this->Ex_.fill(0);
    this->Ex2_.fill(0);
}


template <size_t T_length, size_t T_width>
void StatisticsBuffer<T_length, T_width>::addRow(const DataContainer<T_width> &data) {

    double diff;

    if (this->numRows_ == 0) {
        // K must be initialized to a value within the sample range.
        // Close to mean is preferable, but not required.
        this->K_ = data;
    }

    this->tailIndex_ = (this->tailIndex_ + 1) % T_length;

    // if buffer isn't full yet, just mark that we're increasing in size
    if (this->numRows_ < T_length) {
       this->numRows_++;
    } else {
    // if buffer is full, we need to remove the current head from estimator, and move the head
        for (unsigned int i = 0; i < T_width; i++) {
            diff = this->circularBuffer_[this->headIndex_][i] - this->K_[i];
            this->Ex_[i] -= diff;
            this->Ex2_[i] -= diff*diff;
        }
        this->headIndex_ = (this->headIndex_ + 1) % T_length;
    }

    // Adds new data or replaces old
    this->circularBuffer_[this->tailIndex_] = data;
    // Add data to mean/variance
    for (unsigned int i = 0; i < T_width; i++) {
        diff = this->circularBuffer_[this->tailIndex_][i] - this->K_[i];
        this->Ex_[i] += diff;
        this->Ex2_[i] += diff*diff;
    }
}

template <size_t T_length, size_t T_width>
void StatisticsBuffer<T_length, T_width>::removeRow() {
    this->removeRows(1);
}
template <size_t T_length, size_t T_width>
void StatisticsBuffer<T_length, T_width>::removeRows(unsigned int numRowsToRemove) {
    assert(!this->isEmpty());

    double diff;
    for (unsigned int k = 0; k < numRowsToRemove && this->numRows_ != 0; k++)  {
        this->numRows_--;
        for (unsigned int i = 0; i < T_width; i++) {
            diff = this->circularBuffer_[this->headIndex_][i] - this->K_[i];
            this->Ex_[i] -= diff;
            this->Ex2_[i] -= diff*diff;
        }
        this->headIndex_ = (this->headIndex_ + 1) % T_length;
    }
}

template <size_t T_length, size_t T_width>
StatisticsBuffer<T_length, T_width> & StatisticsBuffer<T_length, T_width>::operator+=(const DataContainer<T_width> &data) {
    this->addRow(data);
    return *this;
}

template <size_t T_length, size_t T_width>
const DataContainer<T_width> StatisticsBuffer<T_length, T_width>::getRow(unsigned int index) { 
    assert(!this->isEmpty());
    return this->circularBuffer_[(this->headIndex_ + index) % T_length];
}

template <size_t T_length, size_t T_width>
const DataContainer<T_width> StatisticsBuffer<T_length, T_width>::getLatestRow() {
    assert(!this->isEmpty());
    return this->circularBuffer_[this->tailIndex_];
}

template <size_t T_length, size_t T_width>
const DataContainer<T_width> StatisticsBuffer<T_length, T_width>::getMean() {
    assert(!this->isEmpty());
    DataContainer<T_width> mean;
    for (unsigned int i = 0; i < T_width; i++) {
        mean[i] = this->K_[i] + this->Ex_[i] / this->numRows_;
    }
    return mean;
}

template <size_t T_length, size_t T_width>
const DataContainer<T_width> StatisticsBuffer<T_length, T_width>::getStdDev() {
    assert(!this->isEmpty());
    DataContainer<T_width> variance;
    for (unsigned int i = 0; i < T_width; i++) {
        // could use Pow here, but would require another variable
        variance[i] = (this->Ex2_[i] - (this->Ex_[i]*this->Ex_[i]) / this->numRows_) / (this->numRows_-1);
    }
    return variance.Sqrt();
}

template <size_t T_length, size_t T_width>
size_t StatisticsBuffer<T_length, T_width>::maxLength() {
    return T_length;
}

template <size_t T_length, size_t T_width>
size_t StatisticsBuffer<T_length, T_width>::currentLength() {
    return this->numRows_;
}

template <size_t T_length, size_t T_width>
bool StatisticsBuffer<T_length, T_width>::isEmpty() {
    return this->numRows_ == 0;
}

template <size_t T_length, size_t T_width>
bool StatisticsBuffer<T_length, T_width>::isFull() {
    return this->numRows_ == T_length;
}
