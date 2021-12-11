#ifndef SYNC_MSG_QUEUE_H_
#define SYNC_MSG_QUEUE_H_

#include <pthread.h>
#include <vector>

template<class T>
class SyncMsgQueue {
public:
    SyncMsgQueue();

    void print();
    void enqueue(T);
    T dequeue();

private:
    std::vector<T> vec;
    pthread_mutex_t mtx;
    pthread_cond_t  cv;
};

#endif