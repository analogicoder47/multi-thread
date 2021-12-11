#include <iostream>
#include "../../header/sync_msg_q.h"

template<class T>
SyncMsgQueue<T>::SyncMsgQueue()
    : mtx(PTHREAD_MUTEX_INITIALIZER), cv(PTHREAD_COND_INITIALIZER)
{}

template<class T>
void SyncMsgQueue<T>::print()
{
    std::cout << "list: ";
    for (typename std::vector<T>::iterator it=vec.begin(); it != vec.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

template<class T>
void SyncMsgQueue<T>::enqueue(T msg)
{
    pthread_mutex_lock(&mtx);

    vec.push_back(msg);
    print();
    pthread_cond_signal(&cv);

    pthread_mutex_unlock(&mtx);
}

template<class T>
T SyncMsgQueue<T>::dequeue()
{
    pthread_mutex_lock(&mtx);

    while (vec.empty() ) {
        pthread_cond_wait(&cv, &mtx);
    }
    T data = vec[0];
    vec.erase(vec.begin() );
    print();

    pthread_mutex_unlock(&mtx);
    return data;
}

// In separate compile model, it need to declare the real type of template
// to prevent from the linkage error
template class SyncMsgQueue<int>;