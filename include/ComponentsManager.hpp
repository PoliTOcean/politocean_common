#include "../libs/Component/Component.hpp"

#include <vector>
#include <exception>

#include "../libs/MqttClient/MqttClient.h"

#include "PolitoceanConstants.h"

#include "../libs/Logger/logger.h"
#include <sstream>

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
        static std::string id_;
        static std::vector<Component> components_;

        static Component& find(component_t component)
        {
            std::vector<Component>::iterator it;

            for (it = components_.begin(); it != components_.end(); it++)
                if (it->getName() == component)
                    return *it;

            if (it == components_.end())
                throw ComponentsManagerException("Out of bounds exception.");
        }

    public:
        static void listen(Component component)
        {
            stringstream ss;
            ss << component;
            logger::getInstance().log(logger::CONFIG, ss.str());
            find(component.getName()).setState(component.getState());
        }

        static void Init(const std::string& id)
        {
            id_ = id;

            for (auto componentType : component_t())
                components_.emplace_back(Component(componentType));

            MqttClient::getInstance(id, Constants::Hmi::IP_ADDRESS).subscribeTo(Topics::COMPONENTS, &listen);
        }

        static void SetComponentState(component_t component, Component::Status state)
        {
            MqttClient::getInstance(id_, Hmi::IP_ADDRESS).publish(Topics::COMPONENTS, find(component));
        }

        static Component::Status GetComponentState(component_t component)
        {
            return find(component).getState();
        }
    };

    std::string ComponentsManager::id_;
    std::vector<Component> ComponentsManager::components_;
}