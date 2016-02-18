
template <size_t T_width>
DataContainer<T_width> & DataContainer<T_width>::operator + (const DataContainer<T_width> &rhs) {
    return DataContainer<T_width>(*this) += rhs;
}
template <size_t T_width>
DataContainer<T_width> & DataContainer<T_width>::operator - (const DataContainer<T_width> &rhs) {
    return DataContainer<T_width>(*this) -= rhs;
}

template <size_t T_width>
DataContainer<T_width> & DataContainer<T_width>::operator / (const double constant) {
    DataContainer<T_width> result = *this;
    for (auto &d: result)
        d /= constant;
    return result;
}

template <size_t T_width>
DataContainer<T_width> & DataContainer<T_width>::operator += (const DataContainer &rhs) {
    for (unsigned int i = 0; i < this->size(); i++) {
        (*this)[i] = (*this)[i] + rhs[i];
    }
    return *this;
}
template <size_t T_width>
DataContainer<T_width> & DataContainer<T_width>::operator-=(const DataContainer &rhs) {
    for (unsigned int i = 0; i < this->size(); i++) {
        (*this)[i] = (*this)[i] - rhs[i];
    }
    return *this;
}

/* DataContainer<T_width> Pow(const double exponent); */
/* DataContainer<T_width> Sqrt(); */

template <size_t T_width>
void DataContainer<T_width>::Print() {
    for (auto d: *this)
        std::cout << d << ' ';
    std::cout << std::endl;
}

