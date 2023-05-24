#ifndef CONCURRENTQUEUE_H
#define CONCURRENTQUEUE_H

#include <future>
#include <iostream>
#include <limits>
#include <mutex>
#include <queue>
#include <stdexcept>
#include <utility>

template <typename T, template <typename, typename> class Cont = std::deque>
class ConcurrentQueue {
public:
  void push(T val) {
    std::lock_guard<std::mutex> lockQueue(mutexQueue);
    myQueue.push(std::move(val));
  }
  T frontAndPop() {
    std::lock_guard<std::mutex> lockQueue(mutexQueue);
    if (myQueue.empty())
      throw std::out_of_range("The queue is empty!");
    auto val = myQueue.front();
    myQueue.pop();
    return val;
  }
  ConcurrentQueue() = default;
  ConcurrentQueue(const ConcurrentQueue &) = delete;
  ConcurrentQueue &operator=(const ConcurrentQueue &) = delete;

private:
  mutable std::mutex mutexQueue;
  std::queue<T, Cont<T, std::allocator<T>>> myQueue;
};

#endif