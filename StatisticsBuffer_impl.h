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

    if (this->bufferIndex_ == BUFFER_EMPTY) {
        // K must be initialized to a value within the sample range.
        // Close to mean is preferable, but not required.
        this->K_ = data;
    }

    this->bufferIndex_ = (this->bufferIndex_ + 1) % T_length;

    // if buffer isn't full yet, just mark that we're increasing in size
    if (this->n_ < T_length) {
       this->n_++;
    } else {
    // if buffer is full, we need to remove the current index from estimator
        for (unsigned int i = 0; i < T_width; i++) {
            diff = this->circularBuffer_[this->bufferIndex_][i] - this->K_[i];
            this->Ex_[i] -= diff;
            this->Ex2_[i] -= diff*diff;
        }
    }

    // Adds new data or replaces old
    this->circularBuffer_[this->bufferIndex_] = data;
    // Add data to mean/variance
    for (unsigned int i = 0; i < T_width; i++) {
        diff = this->circularBuffer_[this->bufferIndex_][i] - this->K_[i];
        this->Ex_[i] += diff;
        this->Ex2_[i] += diff*diff;
    }
}

template <size_t T_length, size_t T_width>
StatisticsBuffer<T_length, T_width> & StatisticsBuffer<T_length, T_width>::operator+=(const DataContainer<T_width> &data) {
    this->addRow(data);
    return *this;
}

template <size_t T_length, size_t T_width>
const DataContainer<T_width> StatisticsBuffer<T_length, T_width>::getRow(unsigned int index) { 
    unsigned int tempIndex;
    assert(this->bufferIndex_ != BUFFER_EMPTY);
    if (this->n_ < T_length) {
        tempIndex = index;
    } else {
        tempIndex = (this->bufferIndex_ + index + 1) % T_length;            
    }
    return this->circularBuffer_[tempIndex];
}

template <size_t T_length, size_t T_width>
const DataContainer<T_width> StatisticsBuffer<T_length, T_width>::getLatestRow() {
    assert(this->bufferIndex_ != BUFFER_EMPTY);
    return this->circularBuffer_[this->bufferIndex_];
}

template <size_t T_length, size_t T_width>
const DataContainer<T_width> StatisticsBuffer<T_length, T_width>::getMean() {
    DataContainer<T_width> mean;
    assert(this->bufferIndex_ != BUFFER_EMPTY);
    for (unsigned int i = 0; i < T_width; i++) {
        mean[i] = this->K_[i] + this->Ex_[i] / this->n_;
    }
    return mean;
}

template <size_t T_length, size_t T_width>
const DataContainer<T_width> StatisticsBuffer<T_length, T_width>::getStdDev() {
    DataContainer<T_width> variance;
    assert(this->bufferIndex_ != BUFFER_EMPTY);
    for (unsigned int i = 0; i < T_width; i++) {
        // could use Pow here, but would require another variable
        variance[i] = (this->Ex2_[i] - (this->Ex_[i]*this->Ex_[i]) / this->n_) / (this->n_-1);
    }
    return variance.Sqrt();
}

template <size_t T_length, size_t T_width>
size_t StatisticsBuffer<T_length, T_width>::maxLength() {
    return T_length;
}

template <size_t T_length, size_t T_width>
size_t StatisticsBuffer<T_length, T_width>::currentLength() {
    return this->n_;
}

