# Thread-Safe Queue

Implementation of thread-safe queue.

## Use Cases

```cpp
#include <iostream>
#include <thread>

#include "thread_safe_queue.hpp"

void push_values(int n, ThreadSafeQueue<int> &que) {
    for (size_t i = 0; i < n; i++) {
        que.push_back(i);
    }
}

void pop_values(int n) {
    for (size_t i = 0; i < n; i++) {
        que.pop();
    }
}

int main() {
    ThreadSafeQueue<int> que;

    std::thread t1(push_values, 100, que);
    std::thread t2(push_values, 100, que);

    std::cout << "ThreadSafeQueue.size is " << que.size() << std::endl;


    t1.run(pop_values, 100);
    t2.run(pop_values, 100);

    std::cout << "ThreadSafeQueue.size is " << que.size() << std::endl;

    t1.join();
    t2.join();

    return 0;
}
```
