#pragma once

#include "sequence.h"
#include "LinkedList.h"

template <class T>
class ListSequence : public Sequence<T, LinkedList<T>> {
public:
    ListSequence() = default;

    T GetFirst() const override {
        return list_.GetFirst();
    }
    T GetLast() const override {
        return list_.GetLast();
    }
    T Get(const int& index) const override {
        return list_.Get(index);
    }
    int GetLength() const override {
        return list_.GetLength();
    }
    void InsertAt(T item, int index) override {
        list_.InsertAt(item, index);
    }
    void Append(T item) override {
        list_.Append(item);
    }
    void Prepend(T item) override {
        list_.Prepend(item);
    }
    void EraseAt(int index) {
        list_.EraseAt(index);
    }
    void Set(T item, int index) {
        list_.Set(item, index);
    }
    LinkedList<T>* GetList() {
        return &list_;
    }
    Node<T>* GetPointer(int i) {
        return list_.GetPointer(i);
    }
    LinkedList<T>* Concat(LinkedList<T>* list) override {
        return list_.Concat(list);
    }
private:
    LinkedList<T> list_;
};

template <class T>
std::ostream& operator<<(std::ostream& os, const ListSequence<T>& list)
{
    for (int i = 0; i < list.GetLength(); i++) {
        os << list.Get(i) << " ";
    }
    return os;
}