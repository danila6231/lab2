#pragma once

#include <cstddef>

// Declaration

template <class T>
class DynamicArray {
public:
    DynamicArray(T* items, const int& count);
    explicit DynamicArray(const int& size);
    DynamicArray(const DynamicArray<T>& dynamicArray);
    T Get(const int& index) const;
    int GetSize() const;
    void Set(const int& index, const T& value);
    void Resize(const int& newSize);
    ~DynamicArray() {
        free(data_);
    }
private:
    T *data_;
    size_t size_;
};

// Definition

template <class T>
DynamicArray<T>::DynamicArray(T *items, const int &count) : data_(items), size_(count) {}

template <class T>
DynamicArray<T>::DynamicArray(const int &size) : data_(new T(size)), size_(size){
    for (int i = 0; i < size_; i++) {
        data_[i] = 0;
    }
}

template <class T>
DynamicArray<T>::DynamicArray(const DynamicArray<T> &dynamicArray) : data_(new T(dynamicArray.GetSize())),
                                                                     size_(dynamicArray.GetSize()) {
    for (int i = 0; i < size_; i++) {
        data_[i] = dynamicArray.Get(i);
    }
}

template <class T>
T DynamicArray<T>::Get(const int &index) const {
    OutOfRangeCheck(index, size_);
    return data_[index];
}

template <class T>
int DynamicArray<T>::GetSize() const {
    return size_;
}

template <class T>
void DynamicArray<T>::Set(const int &index, const T &value) {
    OutOfRangeCheck(index, size_);
    data_[index] = value;
}

template <class T>
void DynamicArray<T>::Resize(const int &newSize) {
    T* new_data = new T(newSize);
    for (int i = 0; i < size_; i++) {
        new_data[i] = data_[i];
    }
    free(data_);
    data_ = new_data;
    size_ = newSize;
}
