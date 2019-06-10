#include "Component.hpp"

#include <sstream>

using namespace Politocean;

void Component::setState(Status state)
{
    state_ = state;
}

Component::Status Component::getState()
{
    return state_;
}

component_t Component::getName()
{
    return name_;
}

std::string Component::getNameStr() const
{
    std::stringstream ss;
    ss << name_;

    return ss.str(); 
}