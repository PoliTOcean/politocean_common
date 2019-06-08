#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#include <iostream>
#include <string>
#include <exception>

#include "include/component_t.hpp"

namespace Politocean
{
    class ComponentException : public std::exception
    {
        std::string msg_;

    public:
        ComponentException(const std::string& msg) : msg_(msg) {}

        virtual char const* what() const throw()
        {
            return msg_.c_str();
        }
    };

    class Component
    {
    public:
        enum class Status
        {
            ENABLED, DISABLED, ERROR
        };

        Component(component_t name, Status status) : name_(name), status_(status) {}
        Component(component_t name) : Component(name, Status::DISABLED) {}

        void setStatus(Status status);
        Status getStatus();

        component_t getName();

        friend std::ostream& operator<<(std::ostream& os, const Component& obj)
        {
            if (obj.status_ == ERROR)
                throw ComponentException("An error occurred processing component " + obj.name_ + ".");

            std::string status = (obj.status_ == ENABLED) ? "enabled" : "disabled";
            
            os << obj.name_ << " is " << status << std::endl;
            return os;
        }

    private:
        component_t name_;
        Status status_;
    };
}

#endif // COMPONENT_HPP