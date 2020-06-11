#pragma once

#include "sequence.h"
#include "DynamicArray.h"

template <class T>
class ArraySequence : public Sequence<T, DynamicArray<T>> {
public:
    explicit ArraySequence(size_t size) : array_(size) {}

    T GetFirst() const override {
        return array_.Get(0);
    }
    T GetLast() const override {
        return array_.Get(array_.GetSize() - 1);
    }
    T Get(const int& index) const override {
        return array_.Get(index);
    }
    int GetLength() const override {
        return array_.GetSize();
    }
    void InsertAt(T item, int index) override {
        array_.Set(index, item);
    }
    void Append(T item) override {
        array_.Resize(array_.GetSize()+1);
        array_.Set(array_.GetSize()-1, item);
    }
    void Prepend(T item) override {
        array_.Resize(array_.GetSize()+1);
        for (int i = array_.GetSize() - 2; i > 0; i--) {
            array_.Set(i + 1, array_.Get(i));
        }
        array_.Set(0, item);
    }
    DynamicArray<T>* Concat(DynamicArray<T> *array) override {}
    DynamicArray<T>* GetArray() const {
        return &array_;
    }
private:
    DynamicArray<T> array_;
};