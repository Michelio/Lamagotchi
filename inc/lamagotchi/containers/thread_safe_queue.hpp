#ifndef THREAD_SAFE_QUEUE_HPP
#define THREAD_SAFE_QUEUE_HPP

#include <condition_variable>
#include <mutex>
#include <queue>

namespace Containers
{

template <class T>
class ThreadSafeQueue
{
public:
    void push(T item)
    {
        std::unique_lock<std::mutex> lock(m_mutex);

        m_queue.push(item);
        m_condition.notify_one();
    }

    T pop()
    {
        std::unique_lock<std::mutex> lock(m_mutex);

        m_condition.wait(lock, [this]() { return !m_queue.empty(); });

        T item = m_queue.front();

        m_queue.pop();
        return item;
    }

    bool empty()
    {
        std::unique_lock<std::mutex> lock(m_mutex);

        return m_queue.empty();
    }

private:
    std::queue<T> m_queue;
    std::mutex m_mutex;
    std::condition_variable m_condition;
};

} // namespace Containers

#endif // THREAD_SAFE_QUEUE_HPP
