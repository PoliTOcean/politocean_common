#include "mqttLogger.h"

#include <sstream>
#include <string>
#include <unistd.h>
#include "PolitoceanConstants.h"

namespace Politocean {

using namespace Politocean::Constants;
using namespace Politocean::Constants::Common;

const std::string mqttLogger::DFLT_HOST = Hmi::IP_ADDRESS;

mqttLogger::mqttLogger(const std::string& node_id) : mqttLogger(DFLT_HOST, node_id) {}

mqttLogger::mqttLogger(const std::string& host, const std::string& node_id) : mqtt_pub(host, node_id) {
    try{
        mqtt_pub.connect();
    }
    catch(std::exception& e){
        logger::log(logger::ERROR, "mqttLogger class: Couldn't connect mqtt logger publisher. mqttLogger will be used as a normal logger.", e);
    }
}

mqttLogger::~mqttLogger(){
    try{
        mqtt_pub.disconnect();
    }
    catch(...){}
}

void mqttLogger::logError(const std::string& msg){
    std::stringstream ss;
    ss << msg;
    try{
        mqtt_pub.publish(Topics::ERRORS, msg);
        ss << "\t--- [published]";
    }
    catch(std::exception& e){
        ss << "\t--- [not published due to: " << e.what() << "]";
    }
    auto str = ss.str();
    logger::log(logger::ERROR, str.c_str());
}

void mqttLogger::logError(const std::string& msg, const std::exception& exc){
    std::stringstream ss;
    ss << msg << "\tException: " << exc.what();
    auto str = ss.str();
    logError(str.c_str());
}


void mqttLogger::logError(const std::exception& exc){
    logError("An error occured due to an exception.", exc);
}

void mqttLogger::logInfo(const std::string& msg){
    std::stringstream ss;
    ss << msg;
    try{
        mqtt_pub.publish(Topics::INFO, msg);
        ss << "\t--- [published]";
    }
    catch(std::exception& e){
        ss << "\t--- [not published due to: " << e.what() << "]";
    }
    auto str = ss.str();
    logger::log(logger::INFO, str.c_str());
}

void mqttLogger::logInfo(const std::string& msg, const std::exception& exc){
    std::stringstream ss;
    ss << msg << "\tException: " << exc.what();
    auto str = ss.str();
    logInfo(str.c_str());
}


void mqttLogger::logInfo(const std::exception& exc){
    logInfo("An error occured due to an exception.", exc);
}

}