#ifndef QUEUED_LISTENER_
#define QUEUED_LISTENER_

#include <string>
#include <queue>
#include <exception>
#include <Listener.hpp>

namespace Politocean
{

/* Definition */
template< class T >
class QueuedListener : public Listener<T>
{
protected:
    std::queue<T> queue_;

public:
    QueuedListener() : Listener<T>() {}

    virtual void listen(const T& obj) override;
    virtual T get() override;

    virtual bool isUpdated() override;
};

/* Implementation */

template<class T>
void QueuedListener<T>::listen(const T& obj)
{
    queue_.push(obj);
}

template<class T>
T QueuedListener<T>::get()
{
    if (queue_.empty())
        throw ListenerException("Listening queue is empty. Nothing to retrieve.");
    
    T obj = queue_.front();
    queue_.pop();

    return obj;
}

template<class T>
bool QueuedListener<T>::isUpdated()
{
    return !queue_.empty();
}

}

#endif // LISTENER