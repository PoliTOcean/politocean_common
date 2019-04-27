#include "mqttLogger.h"

#include <sstream>
#include <unistd.h>
#include "PolitoceanConstants.h"

namespace Politocean {

using namespace Politocean::Constants;
using namespace Politocean::Constants::Common;


mqttLogger::mqttLogger(std::string host, std::string node_id) : mqtt_pub(host, node_id) {
    mqtt_pub.connect();
}

mqttLogger::~mqttLogger(){
    mqtt_pub.disconnect();
}

void mqttLogger::logError(const char* msg){
    std::stringstream ss;
    ss << msg;
    try{
        mqtt_pub.publish(Topics::ERRORS, msg);
        ss << " --- [published]";
    }
    catch(std::exception& e){
        ss << " --- [not published due to: " << e.what() << "]";
    }
    auto str = ss.str();
    logger::log(logger::ERROR, str.c_str());
}

void mqttLogger::logError(const char* msg, const std::exception& exc){
    std::stringstream ss;
    ss << msg << " " << exc.what();
    auto str = ss.str();
    logError(str.c_str());
}


void mqttLogger::logError(const std::exception& exc){
    logError("Error occured due to exception: ", exc);
}

void mqttLogger::logInfo(const char* msg){
    std::stringstream ss;
    ss << msg;
    try{
        mqtt_pub.publish(Topics::INFO, msg);
        ss << " --- [published]";
    }
    catch(std::exception& e){
        ss << " --- [not published due to: " << e.what() << "]";
    }
    auto str = ss.str();
    logger::log(logger::INFO, str.c_str());
}

void mqttLogger::logInfo(const char* msg, const std::exception& exc){
    std::stringstream ss;
    ss << msg << " " << exc.what();
    auto str = ss.str();
    logInfo(str.c_str());
}


void mqttLogger::logInfo(const std::exception& exc){
    logInfo("Error occured due to exception: ", exc);
}

}