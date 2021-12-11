#ifndef CONSUMER_H_
#define CONSUMER_H_

#include "sync_msg_q.h"

class Consumer {
public:
    Consumer(SyncMsgQueue<int>*);

    static void* start_routine(void*);
    void create_worker();
    pthread_t getTID();

private:
    pthread_t tid;
    SyncMsgQueue<int> *queue;
};

#endif