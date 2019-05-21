#include "MqttClient.h"
#include <logger.h>

using namespace Politocean;
using namespace std;

MqttClient::MqttClient(const std::string& clientID, const std::string& address, const int& port)
    :  mosqpp::mosquittopp(clientID.c_str()), clientID_(clientID), address_(address)
{
    port_ = port;
    mosqpp::lib_init();
}

MqttClient::~MqttClient()
{
    disconnect();
    loop_stop();
    mosqpp::lib_cleanup();
}

bool MqttClient::is_connected()
{
    return connected;
}

void MqttClient::connect()
{
    connect_async(this->address_.c_str(), this->port_, this->keepalive);
    loop_start();
}

/**
 * Wait until client is connected
 */
void MqttClient::wait()
{
	while(is_connected());
}

/**
 * Subscribe to the given topic with the given callback.
 * Remove traling '/'.
 */
void MqttClient::subscribeTo(const std::string& topic, callback_t pf)
{
	string topicf = topic;
	if(topicf[topicf.size()-1]=='/')
		topicf = topicf.substr(0, topicf.find_last_not_of('/')+1)+"/"; //trim trailing '/' if they exist

	topic_to_callback.insert(std::pair<std::string, callback_t>(topicf, pf));

    mosquittopp::subscribe(NULL, topic.c_str());

	logger::log(logger::DEBUG, string("Subscribed ")+clientID_+string(" to topic ")+topic);
}

void MqttClient::subscribeTo(const std::string& topic, void (*pf)(const std::string& payload))
{
	callback_t wrapper_function = [pf](const std::string& payload, const std::string& topic) { (*pf)(payload); };

	subscribeTo(topic, wrapper_function);
}

void MqttClient::publish(const string& topic, const string& message)
{
    mosqpp::mosquittopp::publish(NULL, topic.c_str(), message.length(), message.c_str(), this->qos, false);
}

/**
 * Unsubscribe from the given topic.
 */
void MqttClient::unsubscribeFrom(const std::string& topic)
{
	topic_to_callback.erase(topic);

    mosquittopp::unsubscribe(NULL, topic.c_str());

	logger::log(logger::DEBUG, string("Unsubscribed ")+clientID_+string(" from topic ")+topic);
}

void MqttClient::unsubscribeFrom(const std::vector<std::string>& topics)
{
	for (auto &topic : topics)
		unsubscribeFrom(topic);
}

/**
 * get the topics which it's subscribed to
 */
std::vector<string> MqttClient::getSubscribedTopics()
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
std::string MqttClient::getClientId(){
    return clientID_;
}


void MqttClient::on_message(const struct mosquitto_message *msg) {
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
		logger::log(logger::ERROR, string("Callback's topic ")+msg->topic+string(" not found in subscribed topics of ")+clientID_);
		return;
	}

	callback_t callback = it->second;

	callback((char*)msg->payload, msg->topic);
}

void MqttClient::disconnect()
{
    mosquittopp::disconnect();
}

void MqttClient::on_subscribe(int, int, const int *) {
    cout << TAG <<"Subscription succeeded." << endl;
}

void MqttClient::on_disconnect(int rc)
{
    cout << TAG << "disconnection(" << rc << ")" << endl;
	connected = false;
}

void MqttClient::on_connect(int rc)
{
    if ( rc == 0 ) {
        cout << TAG << "connected with server" << endl;
		connected = true;
    } else {
        cout << TAG << "impossible to connect with server(" << rc << ")" << endl;
    }
}

void MqttClient::on_publish(int mid)
{
    cout << TAG << "Message (" << mid << ") succeed to be published " << endl;
}
