#include "../libs/Component/Component.hpp"

#include <vector>
#include <exception>

#include "../libs/MqttClient/MqttClient.h"

#include "PolitoceanConstants.h"

using namespace Politocean::Constants;

namespace Politocean
{
    class ComponentsManagerException : std::exception
    {
        std::string msg_;

    public:
        ComponentsManagerException(const std::string& msg) : msg_(msg) {}

        virtual char const* what() const throw()
        {
            return msg_.c_str();
        }
    };

    class ComponentsManager
    {
        static std::vector<Component> components_;

        static Component& find(component_t component)
        {
            bool found = false;
                for (auto it = components_.begin(); it != components_.end() && !found; it++)
                    if (it->getName == component)
                    {
                        found = true;
                        return *it;
                    }

                if (!found)
                    throw ComponentsManagerException("Out of bounds exception.");
        }

    public:
        static void listen(Component& component)
        {
            find(component.getName()).setState(component.getState());
        }

        static void Init()
        {
            MqttClient::getInstance(Constants::Hmi::COMPONENTS_ID, Constants::Hmi::IP_ADDRESS).subscribeTo(Topics::COMPONENTS, &listen);
        }

        static void SetComponentState(component_t component, Component::Status state)
        {
            MqttClient::getInstance(Hmi::COMPONENTS_ID, Hmi::IP_ADDRESS).publish(Topics::COMPONENTS, c);
        }

        static Component::Status GetComponentState(component_t component)
        {
            return find(component).getState();
        }
    };
}