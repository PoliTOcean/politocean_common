#include "Component.hpp"

using namespace Politocean;

void Component::setStatus(Status status)
{
    status_ = status;
}

Component::Status Component::getStatus()
{
    return status_;
}

component_t Component::getName()
{
    return name_;
}