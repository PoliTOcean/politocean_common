#include "Subscriber.h"

#include <sstream>
#include <string>
#include <regex>

#include "logger.h"
#include "PolitoceanExceptions.hpp"
#include "PolitoceanConstants.h"

namespace Politocean {

using namespace std;
using namespace Politocean;
using namespace Politocean::Constants;

/**
 * Constructor
 */
Subscriber::Subscriber(const std::string& address, const std::string& clientID)
	: address_(address), clientID_(clientID), cli_(address, clientID), nretry_(0), QOS_(QOS)
{
	if(!regex_match(clientID_, std::regex(Constants::CLIENT_ID_REGEX)))
    {
        logger::log(logger::ERROR, "Invalid characters for clientID.");
        throw mqttException("Invalid clientID.");
    }
}

/**
 * Connection method
 */
void Subscriber::connect()
{
	// Logging
	if (this->is_connected())
	{
		logger::log(logger::DEBUG, clientID_+string(" already connected."));
		return;
	}

	connOpts_.set_keep_alive_interval(20);
	connOpts_.set_clean_session(true);
    
	cli_.set_callback(*this);

	// Logging
	logger::log(logger::DEBUG, clientID_+string(" is trying to connect as a subscriber."));

	try {
    	cli_.connect(connOpts_, nullptr, *this)->wait();

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

/** 
 * Disconnection method
 */
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

/**
 * Returns true if connected
 */
bool Subscriber::is_connected()
{
	return cli_.is_connected();
}

/**
 * Wait until client is connected
 */
void Subscriber::wait()
{
	while(cli_.is_connected() || nretry_<N_RETRY_ATTEMPTS);
}



/**
 * Subscribe to the given topic with the given callback.
 * Remove traling '/'.
 */
void Subscriber::subscribeTo(const std::string& topic, callback_t pf)
{
	if(is_connected())
		throw mqttException("Cannot subscribe while connected.");

	string topicf = topic.substr(0, topic.find_last_not_of('/')+1); //trim trailing '/' if they exist

	topic_to_callback.insert(std::pair<std::string, callback_t>(topicf, pf));
	logger::log(logger::DEBUG, string("Subscribed ")+clientID_+string(" to topic ")+topic);
}

void Subscriber::subscribeTo(const std::string& topic, void (*pf)(const std::string& payload))
{
	callback_t wrapper_function = [pf](const std::string& payload, const std::string& topic) { (*pf)(payload); };

	subscribeTo(topic, wrapper_function);
}


/**
 * Unsubscribe from the given topic.
 */
void Subscriber::unsubscribeFrom(const std::string& topic)
{
	if(is_connected())
		throw mqttException("Cannot unsubscribe while connected.");

	topic_to_callback.erase(topic);
	logger::log(logger::DEBUG, string("Unsubscribed ")+clientID_+string(" from topic ")+topic);
}

void Subscriber::unsubscribeFrom(const std::vector<std::string>& topics)
{
	for (auto &topic : topics)
		unsubscribeFrom(topic);
}

/**
 * get the topics which it's subscribed to
 */
std::vector<string> Subscriber::getSubscribedTopics()
{
	std::vector<std::string> topics;
	for(std::map<std::string, callback_t>::iterator it = topic_to_callback.begin(); it != topic_to_callback.end(); ++it) {
		topics.push_back(it->first);
	}
	return topics;
}

/**
 * get client id
 */
std::string Subscriber::getClientId(){
    return clientID_;
}

/**
 * Destructor
 */
Subscriber::~Subscriber()
{
	this->disconnect();
}


/**** mqtt::callback and actionlistener methods ovverrided ****/

void Subscriber::reconnect() {
	std::this_thread::sleep_for(std::chrono::milliseconds(2500));
	try {
		cli_.connect(connOpts_, nullptr, *this);
	}
	catch (const mqtt::exception& exc) {
		logger::log(logger::ERROR, exc);
	}
}

// Re-connection failure
void Subscriber::on_failure(const mqtt::token& tok) {
	logger::log(logger::INFO, "Failed connection attempt. Retrying...");

	if (++nretry_ > N_RETRY_ATTEMPTS){
		logger::log(logger::ERROR, "Limit of retry attempts reached while trying to reconnect.");
	}
	reconnect();
}

// (Re)connection success
// Either this or connected() can be used for callbacks.
void Subscriber::on_success(const mqtt::token& tok) {}

void Subscriber::connected(const std::string& cause) {
	vector<std::string> topics = getSubscribedTopics();

	std::stringstream ss;
	ss  << "Connection success\n"
		<< "\tSubscribing to " << topics.size() << " topics\n"
		<< "\tfor client " << clientID_ << std::endl
		<< "\tusing QoS: " << QOS_;
	logger::log(logger::DEBUG, ss.str());

	cli_.subscribe(mqtt::string_collection::create( topics ), mqtt::async_client::qos_collection(topics.size(), QOS_));
}

// Callback for when the connection is lost.
// This will initiate the attempt to manually reconnect.
void Subscriber::connection_lost(const std::string& cause) {
	std::stringstream ss;
	ss << "\nConnection lost" << std::endl;
	if (!cause.empty())
		ss << "\tcause: " << cause << std::endl;
	ss << "Reconnecting..." << std::endl;
	logger::log(logger::DEBUG, ss.str());
	
	nretry_ = 0;
	reconnect();
}

// Callback for when a message arrives.
void Subscriber::message_arrived(mqtt::const_message_ptr msg) {
	
	if(topic_to_callback.empty())
		return;
	
	std::string topic = msg->get_topic();
	std::map<std::string, callback_t>::iterator it;

	it = topic_to_callback.find(topic);

	if(it==topic_to_callback.end()){

		if(topic[topic.size()-1]!='/')
			topic += "/";
		topic += "#";

		for(it = topic_to_callback.find(topic);
			it==topic_to_callback.end() && topic.find_last_of('/')!=std::string::npos;
			it = topic_to_callback.find(topic))
		{
			size_t pos = topic.find_last_of('/');
			topic = topic.substr(0, pos);
			pos = topic.find_last_of('/');
			topic = topic.substr(0, pos+1) + '#';
		}
	}

	if(it == topic_to_callback.end()){
		logger::log(logger::ERROR, string("Callback's topic ")+msg->get_topic()+string(" not found in subscribed topics of ")+clientID_);
		return;
	}

	callback_t callback = it->second;

	std::string payload = msg->get_payload();

	callback(payload, msg->get_topic());
}

void Subscriber::delivery_complete(mqtt::delivery_token_ptr token) {}

}