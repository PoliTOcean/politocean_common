#include "mqttLogger.h"

#include <sstream>
#include <string>
#include <unistd.h>
#include "PolitoceanConstants.h"
#include "PolitoceanExceptions.hpp"

#define UNDEFINED "undefined"

using namespace Politocean;

using namespace Politocean::Constants;

logger::levels mqttLogger::publisher_activation_level = logger::INFO;

mqttLogger::mqttLogger(const std::string& tag) : logger(tag)
{}

std::map<std::string, mqttLogger*> mqttLogger::instances;

mqttLogger& mqttLogger::getInstance(const std::string& tag) {
    if (tag==""){
        static mqttLogger defaultInstance(logger::rootTag);
        return defaultInstance;
    }

    if (instances.find(tag) != instances.end())
	{
		if(instances.at(tag)==nullptr)
			instances.erase(tag);
		else
			return *instances.at(tag);
	}

	instances.insert(std::pair<std::string, mqttLogger*>(tag, new mqttLogger(tag)));
	return *instances.at(tag);
}

void mqttLogger::log(const levels level, const std::exception& exc) {
    mqttLogger::log(level, "An error occured due to an exception.", exc);
}

void mqttLogger::log(const levels level, const std::string& msg, const std::exception& exc) {
    std::stringstream ss;
    ss << msg << "\tException: " << exc.what();
    auto str = ss.str();
    mqttLogger::log(level, msg);
}

void mqttLogger::log(const levels level, const std::string& msg) {
    
    std::string topic = Topics::LOGS + logger::levels_name.at(level) + "/";
    try{
        if (level > publisher_activation_level)
            throw Politocean::loggerException("Publisher activation level lower than "+logger::levels_name.at(level));

        MqttClient& mqtt_pub = MqttClient::getInstance(logger::rootTag, Hmi::IP_ADDRESS);

        if(!mqtt_pub.is_connected())
            throw Politocean::mqttException("mqtt_pub is not connected");
        
        mqtt_pub.publish(topic, (rootTag == "" ? mqtt_pub.getClientId() : rootTag ) + ": " + msg);

        logger::log(level, msg + " [published]");
    }
    catch(std::exception& e) {
        logger::log(level, msg + " [not published] due to: " + e.what());
    }
    catch (...) {
        logger::log(logger::ERROR, "Uknown error while logging over MQTT.");
    }
    
}

void mqttLogger::setPublishLevel(const levels level)
{
    publisher_activation_level = level;
}

void mqttLogger::setDisplayLevel(const levels level)
{
    logger::enableLevel(level);
}

void mqttLogger::setRootTag(const std::string& rootTag)
{
    logger::setRootTag(rootTag);
}