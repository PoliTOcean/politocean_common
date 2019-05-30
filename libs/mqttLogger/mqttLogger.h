#ifndef POLITOCEAN_MQTT_LOGGER_H
#define POLITOCEAN_MQTT_LOGGER_H

#include <logger.h>
#include <MqttClient.h>

namespace Politocean {

class mqttLogger : public logger {

protected:
    MqttClient& mqtt_pub;

public:
    mqttLogger(std::string clientID, std::string ipAddress, int port = DEF_MOSQUITTO_PORT);

    void log(const levels level, const std::exception& exc) override;
    void log(const levels level, const std::string& msg, const std::exception& exc) override;
    void log(const levels level, const std::string& msg) override;

    mqttLogger& getInstance(const std::string& ipAddress, const int& port = DEF_MOSQUITTO_PORT);
    mqttLogger& getInstance(const std::string& clientID, const std::string& ipAddress, const int& port = DEF_MOSQUITTO_PORT);
    mqttLogger& getInstance(MqttClient& client);

private:
    static std::map<mqttID_t, mqttLogger&> instances;
    static std::string def_clientID;
};

}

#endif
