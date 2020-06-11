#pragma once

#include "test_framework.h"
#include "PriorityQueue.h"
#include <vector>

PriorityQueue<int> InitializeQueue() {
    PriorityQueue<int> queue;
    queue.Push(5, 1);
    queue.Push(1, 2);
    queue.Push(3, 3);
    queue.Push(3, 3);
    queue.Push(2, 2);
    queue.Push(4, 1);
    queue.Push(3, 1);
    queue.Push(3, 3);
    queue.Push(3, 2);
    return queue;
}

void TestQueueProperties() {
    PriorityQueue<int> queue = InitializeQueue();
    vector<int> result = {};
    while (queue.GetPrioritiesNum()) {
        result.push_back(queue.Pop());
    }
    vector<int> correct_result = {5, 4, 3, 1, 2, 3, 3, 3, 3};
    AssertEqual(result, correct_result, "Error");
}

void TestWhere() {
    PriorityQueue<int> queue = InitializeQueue();
    vector<int> result = {};
    queue.Where(more_then_two);
    while (queue.GetPrioritiesNum()) {
        result.push_back(queue.Pop());
    }
    vector<int> correct_result = {5, 4, 3, 3, 3, 3, 3};
    AssertEqual(result, correct_result, "Error");
}

void TestMap() {
    PriorityQueue<int> queue = InitializeQueue();
    vector<int> result = {};
    queue.Map(decrement);
    while (queue.GetPrioritiesNum()) {
        result.push_back(queue.Pop());
    }
    vector<int> correct_result = {4, 3, 2, 0, 1, 2, 2, 2, 2};
    AssertEqual(result, correct_result, "Error");
}

void TestConcat() {
    PriorityQueue<int> queue1 = InitializeQueue();
    vector<int> result = {};
    PriorityQueue<int> queue2 = queue1;
    queue2.Map(decrement);
    queue1.Concat(queue2);
    while (queue1.GetPrioritiesNum()) {
        result.push_back(queue1.Pop());
    }
    vector<int> correct_result = {5, 4, 3, 4, 3, 2, 1, 2, 3, 0, 1, 2, 3, 3, 3, 2, 2, 2};
    AssertEqual(result, correct_result, "Error");
}

void TestReduce() {
    PriorityQueue<int> queue = InitializeQueue();
    int result = queue.Reduce(multiply_items, 2);
    int correct_result = 19440;
    AssertEqual(result, correct_result, "Error");
}

void TestAll() {
    TestRunner tr;
    tr.RunTest(TestQueueProperties, "Test Pop-Push");
    tr.RunTest(TestWhere, "Test Where");
    tr.RunTest(TestMap, "Test Map");
    tr.RunTest(TestConcat, "Test Concat");
    tr.RunTest(TestReduce, "Test Reduce");
}