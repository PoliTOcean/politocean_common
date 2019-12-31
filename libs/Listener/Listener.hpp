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
    ListenerException(const std::string &msg) : msg_(msg) {}

    virtual char const *what() const throw()
    {
        return msg_.c_str();
    }
};

/* Class definition */
template <class T>
class Listener
{
protected:
    std::optional<T> value_;

public:
    Listener() {}

    virtual void listen(const T &obj);
    virtual T get();

    virtual bool isUpdated();
};

/* Implementation */
template <class T>
void Listener<T>::listen(const T &obj)
{
    value_ = obj;
}

template <class T>
T Listener<T>::get()
{
    if (!value_.has_value())
        throw ListenerException("Nothing to retrieve yet.");

    T value = value_.value();
    value_.reset();
    return value;
}

template <class T>
bool Listener<T>::isUpdated()
{
    return value_.has_value();
}

} // namespace Politocean

#endif // LISTENER