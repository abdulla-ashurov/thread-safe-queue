#ifndef __THREAD_SAFE_QUEUE_HPP__
#define __THREAD_SAFE_QUEUE_HPP__

#include <queue>
#include <mutex>

template <class T>
class ThreadSafeQueue {
private:
    std::queue<T> m_que;
    std::mutex m_mtx;
    std::condition_variable m_cond;

public:
    ThreadSafeQueue(const ThreadSafeQueue &l) = delete;
    ThreadSafeQueue(ThreadSafeQueue &&r) = delete;

public:
    ThreadSafeQueue& operator=(const ThreadSafeQueue &l) = delete;
    ThreadSafeQueue& operator=(ThreadSafeQueue &&r) = delete;

public:
    void push(const T &value) {
        std::unique_lock<std::mutex> lock(m_mtx);
        m_que.push(value);

        m_cond.notify_all();
    }

    T pop() {
        std::unique_lock<std::mutex> lock(m_mtx);
        m_cond.wait(lock, [this](){ return !m_que.empty(); });

        T value = std::move(m_que.front());
        m_que.pop();

        return value;
    }
    
public:
    T& front() {
        std::unique_lock<std::mutex> lock(m_mtx);
        m_cond.wait(lock, [this](){ return !m_que.empty(); });

       return m_que.front();
    }

    const T& front() const {
        std::unique_lock<std::mutex> lock(m_mtx);
        m_cond.wait(lock, [this](){ return !m_que.empty(); });

        return m_que.front();
    }

public:
    size_t size() const {
        std::lock_guard<std::mutex> lock(m_mtx);
        return m_que.size();
    }

    bool empty() const {
        std::lock_guard<std::mutex> lock(m_mtx);
        return m_que.empty();
    }
};

#endif // __THREAD_SAFE_QUEUE_HPP__
