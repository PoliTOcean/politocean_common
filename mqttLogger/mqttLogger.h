#ifndef POLITOCEAN_MQTT_LOGGER_H
#define POLITOCEAN_MQTT_LOGGER_H

#include "logger.h"
#include "Publisher.h"

namespace Politocean {

class mqttLogger : public logger {

protected:
    Publisher mqtt_pub;

public:
    mqttLogger(const std::string& node_id, const std::string& host);

    ~mqttLogger();

    void logError(const std::string& msg);
    void logError(const std::string& msg, const std::exception& exc);
    void logError(const std::exception& exc);

    void logInfo(const std::string& msg);
    void logInfo(const std::string& msg, const std::exception& exc);
    void logInfo(const std::exception& exc);

};

}

#endif
