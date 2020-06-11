#pragma once

#include "LinkedListSequence.h"

template <class T>
class Queue {
public:
    Queue():priority_(0) {}
    explicit Queue(int priority) : priority_(priority) {}
    void Push(T item) {
        list_.Append(item);
    }
    T Pop() {
        if (list_.GetLength() == 0) {
            return {};
        }
        else {
            T item = list_.Get(0);
            list_.EraseAt(0);
            return item;
        }
    }
    void GetPointer(int index) const {
        return list_.GetPointer(index);
    }
    T Get(int index) const {
        return list_.Get(index);
    }
    void Set(T item, int index) {
        list_.Set(item, index);
    }
    int GetLength() {
        return list_.GetLength();
    }
    void EraseAt(int index) {
        list_.EraseAt(index);
    }
    int GetPriority() {
        return priority_;
    }
private:
    ListSequence<T> list_;
    int priority_{};
};

template <class T>
class PriorityQueue {
public:
    PriorityQueue() = default;
    void Push(T item, int priority) {
        Node<Queue<T>>* p_queue = GetQueue(priority);
        if (p_queue == nullptr) {
            Queue<T> new_queue(priority);
            list_of_queues.Append(new_queue);
            p_queue = list_of_queues.GetPointer(list_of_queues.GetLength()-1);
        }
        p_queue->data.Push(item);
    }
    T Pop() {
        int min_priority = 32000;
        int min_priority_index = 0;
        Node<Queue<T>>* queue = nullptr;
        for (int i = 0; i < list_of_queues.GetLength(); i++) {
            if (list_of_queues.Get(i).GetPriority() < min_priority) {
                queue = list_of_queues.GetPointer(i);
                min_priority = list_of_queues.Get(i).GetPriority();
                min_priority_index = i;
            }
        }
        if (queue != nullptr && queue->data.GetLength() == 1 ) {
            auto to_return = queue->data.Pop();
            list_of_queues.EraseAt(min_priority_index);
            return to_return;
        }
        if (queue != nullptr) {
            return queue->data.Pop();
        }
    }
    int Peek() {
        int min_priority = 32000;
        int min_priority_index = 0;
        Node<Queue<T>>* queue = nullptr;
        for (int i = 0; i < list_of_queues.GetLength(); i++) {
            if (list_of_queues.Get(i).GetPriority() < min_priority) {
                queue = list_of_queues.GetPointer(i);
                min_priority = list_of_queues.Get(i).GetPriority();
            }
        }
        if (queue != nullptr && queue->data.GetLength() == 1 ) {
            return min_priority;
        }
        if (queue != nullptr) {
            return min_priority;
        }
    }
    int GetPrioritiesNum() const {
        return list_of_queues.GetLength();
    }
    void Map(T (*f)(T)) {
        for (int i = 0; i < list_of_queues.GetLength(); i++) {
            for (int j = 0; j < list_of_queues.Get(i).GetLength(); j++) {
                list_of_queues.GetPointer(i)->data.Set(f((list_of_queues.GetPointer(i)->data).Get(j)), j);
            }
        }
    }
    PriorityQueue<T>* Where(bool (*f)(T)) {
        for (int i = 0; i < list_of_queues.GetLength(); i++) {
            for (int j = 0; j < list_of_queues.Get(i).GetLength(); j++) {
                T data_ = list_of_queues.GetPointer(i)->data.Get(j);
                if (!f(data_)) {
                    list_of_queues.GetPointer(i)->data.EraseAt(j);
                    j--;
                }
            }
            if (list_of_queues.Get(i).GetLength() == 0) {
                list_of_queues.EraseAt(i);
                i--;
            }
        }
    }
    T Reduce(T (*f)(T, T), T c) {
        if (list_of_queues.GetLength() == 0) {
            return f(1, c);
        }
        else {
            T result = f(this->Pop(), c);
            while (list_of_queues.GetLength() > 0) {
                result = f(this->Pop(), result);
            }
            return result;
        }
    }
    void Concat(PriorityQueue<T>& to_concat) {
        while (to_concat.GetPrioritiesNum()) {
            int priority = to_concat.Peek();
            this->Push(to_concat.Pop(), priority);
        }
    }
    T Reduce() {}

private:
    ListSequence<Queue<T>> list_of_queues;
    Node<Queue<T>>* GetQueue(int priority) {
        for (int i = 0; i < list_of_queues.GetLength(); i++) {
            if (list_of_queues.Get(i).GetPriority() == priority) {
                return list_of_queues.GetPointer(i);
            }
        }
        return nullptr;
    }
};

template <class T>
std::ostream& operator<<(std::ostream& os, PriorityQueue<T>& queue)
{
    while (queue.GetPrioritiesNum()) {
        os << queue.Pop() << " ";
    }
    return os;
}
