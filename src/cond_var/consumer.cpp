#include <iostream>
#include "../../header/consumer.h"

Consumer::Consumer(SyncMsgQueue<int> *pque)
    : queue(pque)
{}

pthread_t Consumer::getTID()
{
    return tid;
}

void Consumer::create_worker()
{
    int status = pthread_create(&tid, NULL, start_routine, (void*)queue);
    if (status != 0) {
        std::cout << "Failed to create consumer" << std::endl;
    }
}

void* Consumer::start_routine(void *arg)
{
    std::cout << "Consumer fired up" << std::endl;

    SyncMsgQueue<int> *msgQ = static_cast<SyncMsgQueue<int>*>(arg);
    while (true) {
        int data = msgQ->dequeue();
        std::cout << "Consumer-" << pthread_self() << " deleted " << data << " from Q" << std::endl;
    }
    std::cout << "Consumer-" << pthread_self() << " terminated..." << std::endl;
}