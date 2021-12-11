#include <iostream>
#include "../../header/producer.h"

Producer::Producer(SyncMsgQueue<int> *pque)
    : queue(pque)
{}

pthread_t Producer::getTID()
{
    return tid;
}

void Producer::create_worker()
{
    int status = pthread_create(&tid, NULL, start_routine, (void*)queue);
    if (status != 0) {
        std::cout << "Failed to create producer" << std::endl;
    }
}

void* Producer::start_routine(void *arg)
{
    std::cout << " Producer fired up" << std::endl;

    SyncMsgQueue<int> *msgQ = static_cast<SyncMsgQueue<int>*>(arg);

    for (int idx = 0; idx < 20; idx++) {
        std::cout << "Producer-" << pthread_self() << " insert " << idx << std::endl;
        msgQ->enqueue(idx);
    }
    std::cout << "Producer-" << pthread_self() << " terminated..." << std::endl;
}