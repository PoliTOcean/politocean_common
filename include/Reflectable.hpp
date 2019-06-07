#ifndef REFLECTABLE_H
#define REFLECTABLE_H

#include <iostream>
#include <string>
#include <exception>

namespace MQTT
{
    class NotImplementedException : public std::exception
    {
        std::string msg_;

    public:
        NotImplementedException(const std::string& msg) : msg_(msg) {}

        virtual char const* what() const throw()
        {
            return msg_.c_str();
        }
    };
    
    class Reflectable
    {
    public:
        template <typename T, typename std::enable_if<std::is_base_of<Reflectable, T>::value>::type* = nullptr>
        static T parse(std::string stringified)
        {
            throw NotImplementedException("Method PARSE has not been implemented.");
            T obj;
            return obj;
        }
        
        virtual std::string stringify()
        {
            throw NotImplementedException("Method STRINGIFY has not been implemented.");
            return "";
        }
    };
}

#endif