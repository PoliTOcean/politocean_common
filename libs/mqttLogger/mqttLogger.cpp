#include "mqttLogger.h"

#include <sstream>
#include <string>
#include <unistd.h>
#include "PolitoceanConstants.h"
#include "PolitoceanExceptions.hpp"

#define UNDEFINED "undefined"

using namespace Politocean;

using namespace Politocean::Constants;

std::string mqttLogger::def_clientID = UNDEFINED;

mqttLogger::mqttLogger(std::string clientID, std::string ipAddress, int port)
 :  logger(logger::getInstance(clientID)), clientID_(clientID), ipAddress_(ipAddress), port_(port),
    publisher_activation_level(logger::WARNING)
{}

std::map<mqttID_t, mqttLogger*> mqttLogger::instances;

mqttLogger& mqttLogger::getInstance(const std::string& ipAddress, const int& port) {
    return getInstance(def_clientID, ipAddress, port);
}

mqttLogger& mqttLogger::getInstance(MqttClient& client) {
    return getInstance(client.getClientId(), client.getIpAddress(), client.getPort());
}

mqttLogger& mqttLogger::getInstance(const std::string& clientID, const std::string& ipAddress, const int& port) {
	mqttID_t myKey(clientID, ipAddress, port);
    if (def_clientID==UNDEFINED)
        def_clientID = clientID;
	else if (instances.find(myKey) != instances.end())
	{
		if(instances.at(myKey)==nullptr)
			instances.erase(myKey);
		else
			return *instances.at(myKey);
	}

	instances.insert(std::pair<mqttID_t, mqttLogger*>(myKey, new mqttLogger(clientID, ipAddress, port)));
	return *instances.at(myKey);
}

void mqttLogger::log(const levels level, const std::exception& exc) {
    log(level, "An error occured due to an exception.", exc);
}

void mqttLogger::log(const levels level, const std::string& msg, const std::exception& exc) {
    std::stringstream ss;
    ss << msg << "\tException: " << exc.what();
    auto str = ss.str();
    log(level, msg);
}

void mqttLogger::log(const levels level, const std::string& msg) {

    std::stringstream ss;
    ss << msg;

    std::string topic = Topics::LOGS+logger::levels_name.at(level);    
    try{
        if (level < publisher_activation_level)
            throw Politocean::loggerException("Publisher activation level lower than "+logger::levels_name.at(level));

        MqttClient mqtt_pub = MqttClient::getInstance(clientID_, ipAddress_, port_);

        if(!mqtt_pub.is_connected())
            throw Politocean::mqttException("mqtt_pub is not connected");
        mqtt_pub.publish(topic, "["+mqtt_pub.getClientId()+"]"+msg);
        ss << "\t--- [published]";
    }
    catch(std::exception& e){
        ss << "\t--- [not published due to: " << e.what() << "]";
    }
    auto str = ss.str();
    logger::log(level, str.c_str());
}

void mqttLogger::setPublishLevel(const levels level)
{
    publisher_activation_level = level;
}