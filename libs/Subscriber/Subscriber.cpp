/**
 * @author: pettinz
 * 
 * Implementation for MQTT Subscriber client.
 */ 

#include "Subscriber.h"

#include <sstream>
#include <string>
#include <regex>

#include "logger.h"
#include "PolitoceanExceptions.hpp"

namespace Politocean {

using namespace std;

void Subscriber::connect()
{
	// Logging
	if (this->is_connected())
	{
		logger::log(logger::DEBUG, clientID_+string(" already connected."));
		return;
	}

	connOpts_ = new mqtt::connect_options();
	connOpts_->set_keep_alive_interval(20);
	connOpts_->set_clean_session(true);
    
	/*std::vector<std::string> topics = getSubscribedTopics();
	mqtt::string_collection_ptr::create( getSubscribedTopics()) mqttTopics;
	for(std::string topic : topics){
		mqttTopics.push_back()
	}*/
	cb_ = new callback(cli_, *connOpts_, clientID_, mqtt::string_collection::create( getSubscribedTopics() ), QOS);
	cli_.set_callback(*cb_);

	cb_->set_callback(std::bind(&Subscriber::callback_wrapper, this, std::placeholders::_1));

	// Logging
	logger::log(logger::DEBUG, clientID_+string(" is trying to connect as a subscriber."));

	try {
    	cli_.connect(*connOpts_, nullptr, *cb_)->wait();

		if(!(cli_.is_connected()))
			throw mqttException("client couldn't connect.");

	} catch(std::exception& e) {
		// Logging
        stringstream ss;
        ss << "Error while subscribing: " << e.what();
		logger::log(logger::ERROR, ss.str());
		throw Politocean::mqttException(ss.str());
	}

	logger::log(logger::DEBUG, clientID_+string(" is now connected as a subscriber."));
}

std::vector<string> Subscriber::getSubscribedTopics(){
	std::vector<std::string> topics;
	for(std::map<std::string, callback_t>::iterator it = topic_to_callback.begin(); it != topic_to_callback.end(); ++it) {
		topics.push_back(it->first);
	}
	return topics;
}

void Subscriber::disconnect()
{
	// Logging
	if (!(this->is_connected()))
	{
		logger::log(logger::DEBUG, clientID_+string(" already disconnected."));
		return;
	}
	logger::log(logger::DEBUG, clientID_+string(" is being disconnected"));

	try {
    	cli_.disconnect()->wait();

		if(cli_.is_connected())
			throw mqttException("client didn't disconnect.");
	} catch(std::exception& e) {
		// Logging
        stringstream ss;
        ss << "Error while disconnecting: " << e.what();
		logger::log(logger::ERROR, ss.str().c_str());
		throw Politocean::mqttException(ss.str());
	}

	logger::log(logger::DEBUG, clientID_+string(" has been disconnected."));
}

bool Subscriber::is_connected(){
	return cli_.is_connected();
}

void Subscriber::wait(){
	while(cli_.is_connected());
}


Subscriber::Subscriber(const std::string& address, const std::string& clientID)
	: address_(address), clientID_(clientID), cli_(address, clientID) {
		if(clientID.find_first_of(':')!=clientID.size()){
			throw mqttException("Invalid clientID.");
		}
}
    

void Subscriber::subscribeTo(const std::string& topic, void (*pf)(const std::string& payload)){
	if(is_connected()){
		throw mqttException("Cannot subscribe while connected.");
	}
	topic_to_callback.insert(std::pair<std::string, callback_t>(topic, pf));
	logger::log(logger::DEBUG, string("Subscribed ")+clientID_+string(" to topic ")+topic);
}

void Subscriber::unsubscribeFrom(const std::string& topic){
	if(is_connected()){
		throw mqttException("Cannot unsubscribe while connected.");
	}
	topic_to_callback.erase(topic);
	logger::log(logger::DEBUG, string("Unsubscribed ")+clientID_+string(" from topic ")+topic);
}

void Subscriber::unsubscribeFrom(const std::vector<std::string>& topics){
	for(auto &topic : topics) {
		unsubscribeFrom(topic);
	}
}

Subscriber::~Subscriber() {
	this->disconnect();
	delete connOpts_;
	delete cb_;
}

void Subscriber::callback_wrapper(mqtt::const_message_ptr msg) {
	if(topic_to_callback.empty()) return;
	
	callback_t callback = topic_to_callback.at(msg->get_topic());

	std::string payload = msg->get_payload();

	size_t pos = payload.find(":");
	// Check if the string from position 0 to pos+1 (`:` included) matches the regex
	if (pos == string::npos && regex_match(payload.substr(0, pos+1), regex("\\w+:")))
		// Send the substring from pos+2 (after `:` excluded) to the end of the string to the callback
		callback(payload.substr(pos+2));
	else
		callback(payload);
}

}