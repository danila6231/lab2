#pragma once

void interface() {
    PriorityQueue<int> queue;
    while (true) {
                std::cout << "Priority Queue (int)\n"
                             "1. Push\n"
                             "2. Use default queue:\n"
                             "Priority 1: 5, 4, 3\n"
                             "Priority 2: 1, 2, 3\n"
                             "Priority 3: 3, 3, 3\n"
                             "3. Pop\n"
                             "4. Pop Everything\n"
                             "5. Map(decrement)\n"
                             "6. Reduce(multiply all elements)\n"
                             "7. Concat with mapped queue\n"
                             "8. Where(Only elements > 2)\n"
                             "9. Run tests\n"
                             "10. Exit\n"
                             "Enter: ";
                int answer;
                cin >> answer;
                switch (answer) {
                    case 1:
                        cout << "Enter number: ";
                        int num;
                        cin >> num;
                        int priority;
                        cout << "Enter priority: ";
                        cin >> priority;
                        queue.Push(num, priority);
                        break;
                    case 2:
                        queue = InitializeQueue();
                        break;
                    case 3:
                        cout << queue.Pop();
                        break;
                    case 4:
                        cout << queue;
                        break;
                    case 5:
                        queue.Map(decrement);
                        break;
                    case 6:
                        cout << queue.Reduce(multiply_items, 1);;
                        break;
                    case 7:
                        {
                            PriorityQueue<int> queue2 = queue;
                            queue2.Map(decrement);
                            queue.Concat(queue2);
                        }
                        break;
                    case 8:
                        queue.Where(more_then_two);
                        break;
                    case 9:
                        TestAll();
                        break;
                    default:
                        exit(0);
                }
                cout << endl;
        }
}
