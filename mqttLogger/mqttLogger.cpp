#include "mqttLogger.h"

#include <sstream>
#include "PolitoceanConstants.h"

namespace Politocean {

using namespace Politocean::Constants;

void mqttLogger::logError(const char* msg){
    std::stringstream ss;
    ss << msg;
    try{
        mqtt_pub.publish(Topics::ERRORS, msg);
    }
    catch(std::exception e){
        ss << " --- [not published due to: " << e.what() << "]";
    }
    logger::log(logger::ERROR, msg);
}

void mqttLogger::logError(const char* msg, const std::exception exc){
    std::stringstream ss;
    ss << msg << " " << exc.what();
    auto str = ss.str();
    logError(str.c_str());

}


void mqttLogger::logError(const std::exception exc){
    logError("Error occured due to exception: ", exc);
}

void mqttLogger::logInfo(const char* msg){
    std::stringstream ss;
    ss << msg;
    try{
        mqtt_pub.publish(Topics::INFO, msg);
    }
    catch(std::exception e){
        ss << " --- [not published due to: " << e.what() << "]";
    }
    auto str = ss.str();
    logger::log(logger::INFO, str.c_str());
}

void mqttLogger::logInfo(const char* msg, const std::exception exc){
    std::stringstream ss;
    ss << msg << " " << exc.what();
    auto str = ss.str();
    logInfo(str.c_str());
}


void mqttLogger::logInfo(const std::exception exc){
    logInfo("Error occured due to exception: ", exc);
}

}