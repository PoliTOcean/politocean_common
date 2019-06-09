#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#include <iostream>
#include <string>
#include <exception>

#include "include/component_t.hpp"

#include "Reflectable.hpp"

using namespace Reflectable;

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

    class Component : public IReflectable
    {
    public:
        enum class Status
        {
            ENABLED, DISABLED, ERROR
        };

        Component(component_t name, Status state) : name_(name), state_(state) {}
        Component(component_t name) : Component(name, Status::DISABLED) {}

        void setState(Status status);
        Status getState();

        component_t getName();
        std::string getNameStr() const;

        friend std::ostream& operator<<(std::ostream& os, const Component& obj)
        {
            if (obj.state_ == Component::Status::ERROR)
                throw ComponentException("An error occurred processing component " + obj.getNameStr() + ".");

            std::string state = (obj.state_ == Component::Status::ENABLED) ? "enabled" : "disabled";
            
            os << obj.name_ << " is " << state << std::endl;
            return os;
        }

    private:
        component_t name_;
        Status state_;
    };
}

#endif // COMPONENT_HPP