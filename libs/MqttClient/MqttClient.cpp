#include "MqttClient.h"
#include <logger.h>
#include <sstream>

using namespace Politocean;
using namespace std;


/**
 * Singletons
 */
std::map<mqttID_t, MqttClient*> MqttClient::instances;

MqttClient &MqttClient::getInstance(std::string clientID, std::string ipAddress, int port)
{
	mqttID_t myKey(clientID, ipAddress, port);

	if (instances.find(myKey) != instances.end())
	{
		if(instances.at(myKey)==nullptr)
			instances.erase(myKey);
		else{
			instances.at(myKey)->connect();
			return *instances.at(myKey);
		}
	}

	instances.insert(std::pair<mqttID_t, MqttClient*>(myKey, new MqttClient(clientID, ipAddress, port)));
	return *instances.at(myKey);
}

MqttClient::MqttClient(const std::string& clientID, const std::string& address, const int& port)
    :   mosqpp::mosquittopp(clientID.c_str()), clientID_(clientID), address_(address), port_(port),
		reconnectingThread(nullptr), LOGGER(logger::getInstance(clientID))
{
    mosqpp::lib_init();
	connect();
}

MqttClient::~MqttClient()
{
    disconnect();
    loop_stop();
    mosqpp::lib_cleanup();
}

bool MqttClient::is_connected()
{
    return connected || reconnecting;
}

void MqttClient::connect()
{
	if(is_connected()) return;

	reconnecting = true;
	reconnectingThread = new std::thread([&]() {
		while (!connected && reconnecting)
		{
    		mosquittopp::connect(this->address_.c_str(), this->port_, this->keepalive);
    		loop_start();
			std::this_thread::sleep_for(std::chrono::milliseconds(delay));
		}
	});
}


void MqttClient::wait()
{
	while(is_connected())
	{
		std::this_thread::sleep_for(std::chrono::seconds(delay));
	}
}


void MqttClient::subscribeTo(const std::string& topic, callback_t pf)
{
	string topicf = topic;
	if(topicf.at(topicf.size()-1) != '#')
		topicf = formatTopic(topic);

	topic_to_callback.insert(std::pair<std::string, callback_t>(topicf, pf));

    mosquittopp::subscribe(NULL, topicf.c_str());

	LOGGER.log(logger::CONFIG, string("Subscribing ")+clientID_+string(" to topic ")+topicf);
}


void MqttClient::subscribeTo(const std::string& topic, void (*pf)(const std::string& payload))
{
	callback_t wrapper_function = [pf](const std::string& payload, const std::string& topic) { (*pf)(payload); };

	subscribeTo(topic, wrapper_function);
}


void MqttClient::publish(const string& topic, const string& message)
{
    mosqpp::mosquittopp::publish(NULL, formatTopic(topic).c_str(), message.length(), message.c_str(), this->qos, false);
}


string MqttClient::formatTopic(const string& topic)
{
	return topic.substr(0, topic.find_last_not_of(" /")+1)+"/";
}


void MqttClient::unsubscribeFrom(const std::string& topic)
{
	topic_to_callback.erase(topic);

    mosquittopp::unsubscribe(NULL, topic.c_str());

	LOGGER.log(logger::INFO, string("Unsubscribed ")+clientID_+string(" from topic ")+topic);
}


void MqttClient::unsubscribeFrom(const std::vector<std::string>& topics)
{
	for (auto &topic : topics)
		unsubscribeFrom(topic);
}



std::vector<string> MqttClient::getSubscribedTopics()
{
	std::vector<std::string> topics;
	for(std::map<std::string, callback_t>::iterator it = topic_to_callback.begin(); it != topic_to_callback.end(); ++it) {
		topics.push_back(it->first);
	}
	return topics;
}


std::string MqttClient::getClientId()
{
    return clientID_;
}


std::string MqttClient::getIpAddress()
{
	return address_;
}

int MqttClient::getPort()
{
	return port_;
}


void MqttClient::on_message(const struct mosquitto_message *msg)
{
    if(topic_to_callback.empty())
		return;
	
	std::string topic = msg->topic;
	std::map<std::string, callback_t>::iterator it;

	it = topic_to_callback.find(topic);


	if(it==topic_to_callback.end())
	{
		if(topic[topic.size()-1]!='/')
			topic += "/";
		topic += "#";

		for(it = topic_to_callback.find(topic);
			it == topic_to_callback.end() && topic.find_last_of('/') != std::string::npos;
			it = topic_to_callback.find(topic))
		{
			size_t pos = topic.find_last_of('/');
			topic = topic.substr(0, pos);
			pos = topic.find_last_of('/');
			topic = topic.substr(0, pos+1) + '#';
		}
	}

	if(it == topic_to_callback.end())
	{
		LOGGER.log(logger::ERROR, string("Callback's topic ")+msg->topic+string(" not found in subscribed topics of ")+clientID_);
		return;
	}

	callback_t callback = it->second;

	callback((char*)msg->payload, msg->topic);
}


void MqttClient::disconnect()
{
    mosquittopp::disconnect();
	connected = false;
}


void MqttClient::on_subscribe(int, int, const int *)
{
	stringstream ss;
    ss << TAG << "Subscription succeeded.";
	LOGGER.log(logger::INFO, ss.str());
}


void MqttClient::on_disconnect(int rc)
{
	stringstream ss;
    ss << TAG << "disconnection (" << rc << "). Reconnecting...";
	LOGGER.log(logger::ERROR, ss.str());
}

void MqttClient::reconnect()
{
	if (connected || reconnecting) return;
	reconnecting = true;
	reconnectingThread = new std::thread([&]() {
		std::this_thread::sleep_for(std::chrono::milliseconds(delay));
		while (!connected && reconnecting)
		{
			mosquittopp::reconnect();
			std::this_thread::sleep_for(std::chrono::milliseconds(delay));
		}
	});
}


void MqttClient::on_connect(int rc)
{
	stringstream ss;
    if ( rc == 0 ) {
        ss << TAG << "connected with server";
		LOGGER.log(logger::CONFIG, ss.str());
		connected = true;
		reconnecting = false;
		for(std::map<std::string, callback_t>::iterator it = topic_to_callback.begin(); it != topic_to_callback.end(); ++it) {
    		mosquittopp::subscribe(NULL, it->first.c_str());
		}
    } else {
		ss << TAG << "impossible to connect with server(" << rc << ")";
		LOGGER.log(logger::ERROR, ss.str());
    }
}


void MqttClient::on_publish(int mid)
{
	stringstream ss;
	ss << TAG << "Message (" << mid << ") succeed to be published ";
	LOGGER.log(logger::DEBUG, ss.str());
}