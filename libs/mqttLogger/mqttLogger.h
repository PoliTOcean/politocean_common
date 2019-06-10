#ifndef POLITOCEAN_MQTT_LOGGER_H
#define POLITOCEAN_MQTT_LOGGER_H

#include <logger.h>
#include <MqttClient.h>

namespace Politocean {

class mqttLogger : public logger {

protected:
    std::string clientID_;
    
public:
    mqttLogger(const std::string& tag);

    void log(const levels level, const std::exception& exc) override;
    void log(const levels level, const std::string& msg, const std::exception& exc) override;
    void log(const levels level, const std::string& msg) override;

    static void setPublishLevel(const levels level);
    static void setDisplayLevel(const levels level);
    static mqttLogger& getInstance(const std::string& tag = "");
    static void setRootTag(const std::string& rootTag);

private:
    static std::map<std::string, mqttLogger*> instances;
    static logger::levels publisher_activation_level;

    mqttLogger(const mqttLogger&);
    mqttLogger operator=(const mqttLogger&);
};

}

#endif
