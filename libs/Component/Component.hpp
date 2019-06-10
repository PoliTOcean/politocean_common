#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#include <iostream>
#include <string>
#include <exception>

#include <logger.h>

#include "include/component_t.hpp"

#include "Reflectable.hpp"

#include "json.hpp"

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
        std::string getStateStr() const;

        component_t getName();
        std::string getNameStr() const;

        std::string stringify()
        {
            nlohmann::json j_map;
            j_map["name"]   = name_;
            j_map["status"] = state_;

            return j_map.dump();
        }

        static Component parse(const std::string& stringified)
        {
            component_t name;
            Status state;

            try
            {
                auto j_map = nlohmann::json::parse(stringified);

                name    = j_map["name"];
                state   = j_map["status"];
            }
            catch(const std::exception& e)
            {
                logger::getInstance().log(logger::WARNING, "Error while parsing Component: ", e);
                throw ReflectableParsingException(std::string("An error occurred parsing Component: ") + e.what());   
            }
            catch(...)
            {
                logger::getInstance().log(logger::WARNING, "Error while parsing Component.");
                throw ReflectableParsingException("An error occurred parsing Component.");
            }

            return Component(name, state);
        }

        friend std::ostream& operator<<(std::ostream& os, const Component& obj)
        {
            if (obj.state_ == Component::Status::ERROR)
                throw ComponentException("An error occurred processing component " + obj.getNameStr() + ".");

            std::string state = (obj.state_ == Component::Status::ENABLED) ? "enabled" : "disabled";
            
            os << obj.name_ << " is " << state << std::endl;
            return os;
        }

        friend inline bool operator ==(const Component& lhs, const Component& rhs){ return lhs.name_ == rhs.name_; }
        friend inline bool operator!=(const Component& lhs, const Component& rhs){ return !(lhs == rhs); }


    private:
        component_t name_;
        Status state_;
    };
}

#endif // COMPONENT_HPP