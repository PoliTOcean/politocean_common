#ifndef LISTENER
#define LISTENER

#include <string>
#include <queue>
#include <exception>

namespace Politocean
{

/* Exception definition */
class ListenerException : public std::exception
{
    std::string msg_;

public:
    ListenerException(const std::string& msg) : msg_(msg) {}

    virtual char const* what() const throw()
    {
        return msg_.c_str();
    }
};

/* Class definition */
template<class T>
class Listener
{
    T value_;
    bool isUpdated_;

public:
    Listener() : isUpdated_(false) {}

    virtual void listen(const T& obj);
    virtual T get();

    virtual bool isUpdated();
};

/* Implementation */
template<class T>
void Listener<T>::listen(const T& obj)
{
    value_ = obj;
    isUpdated_ = true;
}

template<class T>
T Listener<T>::get()
{
    if (!isUpdated_)
        throw ListenerException("Nothing to retrieve yet.");
    
    isUpdated_ = false;
    return value_;
}

template<class T>
bool Listener<T>::isUpdated()
{
    return isUpdated_;
}

}

#endif // LISTENER