#ifndef LISTENER
#define LISTENER

#include <string>
#include <queue>
#include <exception>

namespace Politocean
{
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

    template<class T>
    class Listener
    {
        std::queue<T> queue_;
        bool isUpdated_;

    public:
        Listener() : isUpdated_(false) {}

        virtual void listen(const T& obj);
        T get();

        bool isUpdated();
    };

    template<class T>
    void Listener<T>::listen(const T& obj)
    {
        queue_.push(obj);
    }

    template<class T>
    T Listener<T>::get()
    {
        if (queue_.empty())
            throw ListenerException("Listening queue is empty. Nothing to retreive.");
        
        T obj = queue_.front();
        queue_.pop();

        return obj;
    }

    template<class T>
    bool Listener<T>::isUpdated()
    {
        return isUpdated_;
    }
}

#endif // LISTENER