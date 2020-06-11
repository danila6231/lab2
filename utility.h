#pragma once

#include <cstddef>

void OutOfRangeCheck(const int& index, const size_t& size) {
    if (index < 0 || index > size-1) {
        throw std::out_of_range ("Index out of range");
    }
}

template <typename T>
std::ostream& operator<<(std::ostream& os, std::vector<T> v) {
    for (auto item : v) {
        os << item << " ";
    }
    return os;
}

template <class T>
T decrement(T x) {
    return x-1;
}

template <class T>
bool more_then_two(T x) {
    return x > 2;
}

template <class T>
T multiply_items(T x, T y) {
    return x*y;
}

template <class T>
struct Node {
    T data = {};
    Node* next = nullptr;
    ~Node() {
        free(next);
    }
};

struct Teacher {
    std::string Name;
    std::string Subject;
    int Age;
};

struct Student {
    std::string Name;
    int study_year;
    int Age;
};
