#include "mqttLogger.h"

#include <sstream>
#include <string>
#include <unistd.h>
#include "PolitoceanConstants.h"
#include "PolitoceanExceptions.hpp"

namespace Politocean {

using namespace Politocean::Constants;
using namespace Politocean::Constants::Common;


mqttLogger::mqttLogger(Publisher *pub) {
    mqtt_pub = pub;
}

void mqttLogger::logError(const std::string& msg){
    logPublish(logger::ERROR, Topics::ERRORS, msg);
}

void mqttLogger::logError(const std::string& msg, const std::exception& exc){
    logException(logger::ERROR, Topics::ERRORS, msg, exc);
}


void mqttLogger::logError(const std::exception& exc){
    logError("An error occured due to an exception.", exc);
}

void mqttLogger::logInfo(const std::string& msg){
    logPublish(logger::INFO, Topics::INFO, msg);
}

void mqttLogger::logInfo(const std::string& msg, const std::exception& exc){
    logException(logger::INFO, Topics::INFO, msg, exc);
}


void mqttLogger::logInfo(const std::exception& exc){
    logInfo("An error occured due to an exception.", exc);
}

void mqttLogger::logPublish(const logger::levels level, const std::string& topic, const std::string& msg){
    std::stringstream ss;
    ss << msg;
    try{
        if(!mqtt_pub->is_connected())
            throw Politocean::mqttException("mqtt_pub is not connected");
        mqtt_pub->publish(topic, msg);
        ss << "\t--- [published]";
    }
    catch(std::exception& e){
        ss << "\t--- [not published due to: " << e.what() << "]";
    }
    auto str = ss.str();
    logger::log(level, str.c_str());
}

void mqttLogger::logException(const logger::levels level, const std::string& topic, const std::string& msg, const std::exception& exc){
    std::stringstream ss;
    ss << msg << "\tException: " << exc.what();
    auto str = ss.str();
    logPublish(level, topic, msg);
}

}