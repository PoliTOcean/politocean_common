#ifndef POLITOCEAN_MQTT_LOGGER_H
#define POLITOCEAN_MQTT_LOGGER_H

#include "logger.h"
#include "Publisher.h"

namespace Politocean {

class mqttLogger : public logger {

protected:
    Publisher mqtt_pub;

public:
    mqttLogger(std::string node_id, std::string host);

    ~mqttLogger();

    void logError(const char* msg);
    void logError(const char* msg, const std::exception& exc);
    void logError(const std::exception& exc);

    void logInfo(const char* msg);
    void logInfo(const char* msg, const std::exception& exc);
    void logInfo(const std::exception& exc);

};

}

#endif
