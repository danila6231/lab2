#pragma once

#include "utility.h"
#include <cstddef>

// Declaration

template <class T>
class LinkedList {
public:
    LinkedList(T* items, const int& count);
    LinkedList();
    LinkedList(const LinkedList<T>& list);
    T GetFirst() const;
    T GetLast() const;
    T Get(const int& index) const;
    //LinkedList<T>* GetSubList(const int& startIndex, const int& endIndex) const;
    int GetLength() const;
    void Append(const T& item);
    void Prepend(const T& item);
    void InsertAt(const T& item, const int& index);
    void Set(const T& item, const int& index);
    void EraseAt(const int& index);
    Node<T>* GetFirstPointer() const;
    Node<T>* GetLastPointer() const;
    Node<T>* GetPointer(int index) const;
    LinkedList<T>* Concat(LinkedList<T> *list) const;
private:
    Node<T>* first_;
    Node<T>* last_;
    size_t size_;
};

// Definition

template <class T>
LinkedList<T>::LinkedList(T *items, const int &count) : size_(count) {
    if (size_ > 0) {
        first_ = new Node<T>;
        Node<T>* current_element = first_;
        for (int i = 0; i < size_; i++) {
            current_element->data = items[i];
            if (i != size_-1) {
                current_element->next = new Node<T>;
                current_element = current_element->next;
            }
            else {
                current_element->next = nullptr;
            }
        }
        last_ = current_element;
    }
    else {
        first_ = nullptr;
        last_ = nullptr;
    }
}

template <class T>
LinkedList<T>::LinkedList() : first_(nullptr), last_(nullptr), size_(0) {}

template <class T>
LinkedList<T>::LinkedList(const LinkedList<T>& list) : size_(list.GetLength()) {
    if (size_ > 0) {
        first_ = new Node<T>;
        Node<T>* current_element = first_;
        for (int i = 0; i < size_; i++) {
            current_element->data = list.Get(i);
            if (i != size_-1) {
                current_element->next = new Node<T>;
                current_element = current_element->next;
            }
            else {
                current_element->next = nullptr;
            }
        }
        last_ = current_element;
    }
    else {
        first_ = nullptr;
        last_ = nullptr;
    }
}

template <class T>
T LinkedList<T>::GetFirst() const {
    OutOfRangeCheck(0, size_);
    return first_->data;
}

template <class T>
T LinkedList<T>::GetLast() const {
    OutOfRangeCheck(0, size_);
    return last_->data;
}

template <class T>
T LinkedList<T>::Get(const int& index) const {
    OutOfRangeCheck(index, size_);
    Node<T>* current_element = first_;
    for (int i = 0; i < index; i++) {
        current_element = current_element->next;
    }
    return current_element->data;
}

/*
template <class T>
LinkedList<T>* LinkedList<T>::GetSubList(const int& startIndex, const int& endIndex) const {}
*/

template <class T>
int LinkedList<T>::GetLength() const {
    return size_;
}

template <class T>
void LinkedList<T>::Append(const T& item) {
    if (first_ == nullptr) {
        first_ = new Node<T>;
        last_ = first_;
        first_->data = item;
    }
    else {
        last_->next = new Node<T>;
        last_ = last_->next;
        last_->data = item;
        last_->next = nullptr;
    }
    size_++;
}

template <class T>
void LinkedList<T>::Prepend(const T& item) {
    if (first_ == nullptr) {
        first_ = new Node<T>;
        last_ = first_;
        first_->data = item;
    }
    else {
        auto new_first_ = new Node<T>;
        new_first_->next = first_;
        new_first_->data = item;
        first_ = new_first_;
    }
    size_++;
}

template <class T>
void LinkedList<T>::InsertAt(const T& item, const int& index) {
    OutOfRangeCheck(index, size_);
    if (first_ == nullptr) {
        first_ = new Node<T>;
        last_ = first_;
        first_->data = item;
    }
    else if (index == 0) {
        auto new_first_ = new Node<T>;
        new_first_->next = first_;
        new_first_->data = item;
        first_ = new_first_;
    }
    else {
        Node<T>* current_element = first_;
        for (int i = 0; i < index-1; i++) {
            current_element = current_element->next;
        }
        Node<T>* prev_element = current_element;
        Node<T>* next_element = prev_element->next;
        prev_element->next = new Node<T>;
        prev_element->next->data = item;
        prev_element->next->next = next_element;
    }
    size_++;
}

template<class T>
Node<T> *LinkedList<T>::GetFirstPointer() const {
    return first_;
}

template<class T>
Node<T> *LinkedList<T>::GetLastPointer() const {
    return last_;
}

template<class T>
LinkedList<T> *LinkedList<T>::Concat(LinkedList<T> *list) const {
    auto new_list = new(LinkedList);
    size_t size_1_ = list->GetLength();
    for (size_t i = 0; i < size_; i++) {
        new_list->Append(this->Get(i));
    }
    for (size_t i = 0; i < size_1_; i++) {
        new_list->Append(list->Get(i));
    }
    return new_list;
}

template<class T>
void LinkedList<T>::EraseAt (const int &index) {
    OutOfRangeCheck(index, size_);
    if (first_ == last_) {
        first_ = nullptr;
        last_ = nullptr;
    }
    else if (index == 0) {
        first_ = first_->next;
    }
    else if (index == size_-1) {
        Node<T>* current_element = first_;
        for (int i = 0; i < size_-2; i++) {
            current_element = current_element->next;
        }
        Node<T>* new_last = current_element;
        last_ = new_last;
    }
    else {
        Node<T>* current_element = first_;
        for (int i = 0; i < index-1; i++) {
            current_element = current_element->next;
        }
        Node<T>* prev_element = current_element;
        Node<T>* this_element = prev_element->next;
        Node<T>* next_element = this_element->next;
        prev_element->next = next_element;
    }
    size_--;
}

template<class T>
Node<T> *LinkedList<T>::GetPointer(int index) const {
    OutOfRangeCheck(index, size_);
    Node<T>* current_element = first_;
    for (int i = 0; i < index; i++) {
        current_element = current_element->next;
    }
    return current_element;
}

template<class T>
void LinkedList<T>::Set(const T &item, const int &index) {
    OutOfRangeCheck(index, size_);
    Node<T>* current_element = first_;
    for (int i = 0; i < index; i++) {
        current_element = current_element->next;
    }
    current_element->data = item;
}
