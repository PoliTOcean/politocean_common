#ifndef POLITOCEAN_MQTT_LOGGER_H
#define POLITOCEAN_MQTT_LOGGER_H

#include "logger.h"
#include "Publisher.h"

namespace Politocean {

class mqttLogger : public logger {

protected:
    Publisher* mqtt_pub;

public:
    mqttLogger(Publisher *pub);

    void logError(const std::string& msg);
    void logError(const std::string& msg, const std::exception& exc);
    void logError(const std::exception& exc);

    void logInfo(const std::string& msg);
    void logInfo(const std::string& msg, const std::exception& exc);
    void logInfo(const std::exception& exc);

    void logPublish(const logger::levels level, const std::string& topic, const std::string& msg);
    void logException(const logger::levels level, const std::string& topic, const std::string& msg, const std::exception& exc);
};

}

#endif
