#ifndef POLITOCEAN_MQTT_LOGGER_H
#define POLITOCEAN_MQTT_LOGGER_H

#include <logger.h>
#include <MqttClient.h>

namespace Politocean {

class mqttLogger : public logger {

protected:
    std::string clientID_, ipAddress_;
    int port_;
    
public:
    mqttLogger(std::string clientID, std::string ipAddress, int port = DEF_MOSQUITTO_PORT);

    void log(const levels level, const std::exception& exc) override;
    void log(const levels level, const std::string& msg, const std::exception& exc) override;
    void log(const levels level, const std::string& msg) override;

    void setPublishLevel(const levels level);

    static mqttLogger& getInstance(const std::string& ipAddress, const int& port = DEF_MOSQUITTO_PORT);
    static mqttLogger& getInstance(const std::string& clientID, const std::string& ipAddress, const int& port = DEF_MOSQUITTO_PORT);
    static mqttLogger& getInstance(MqttClient& client);

private:
    static std::map<mqttID_t, mqttLogger*> instances;
    static std::string def_clientID;
    int publisher_activation_level;
};

}

#endif
