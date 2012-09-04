#ifndef VCQUEUE_H
#define VCQUEUE_H

#include <queue>
#include <QMutex>
#include "Message.h"

template <class T>
class VCQueue
{
private:
    std::queue<T> q;
    QMutex qlock;

public:
    VCQueue() {}

    bool empty() const {
        return q.empty();
    }

    int size() const {
        return q.size();
    }

    T& front() {
        return q.front();
    }

    const T& front() const {
        return q.front();
    }

    T& back() {
        return q.back();
    }

    const T& back() const {
        return q.back();
    }

    void push(const T& x) {
        q.push(x);
    }

    void pop() {
        q.pop();
    }

    void flush() {
        std::queue<Message *> empty;
        std::swap(q, empty);
    }

    void lock() {
        qlock.lock();
    }

    void unlock() {
        qlock.unlock();
    }
};

#endif // VCQUEUE_H
