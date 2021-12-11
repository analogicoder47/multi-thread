#include <iostream>
#include "../../header/sync_msg_q.h"
#include "../../header/producer.h"
#include "../../header/consumer.h"

int main(int argc, char* argv[])
{
    SyncMsgQueue<int> msgQ;

    Producer producer(&msgQ);
    Consumer consumer(&msgQ);

    producer.create_worker();
    consumer.create_worker();

    pthread_join(producer.getTID(), NULL);
    pthread_join(consumer.getTID(), NULL);

    return 0;
}