/**
 * @author: pettinz
 */

#include <thread>
#include <regex>

#include "Publisher.h"

#include "PolitoceanExceptions.hpp"
#include "logger.h"
#include "PolitoceanConstants.h"

namespace Politocean {

using namespace Politocean;
using namespace Politocean::Constants;

Publisher::Publisher(std::string address, std::string clientID)
    : address_(address), clientID_(clientID), cb_(clientID), cli_(address, clientID), TIMEOUT(10)
{
	if(!regex_match(clientID_, std::regex(Constants::CLIENT_ID_REGEX)))
    {
        logger::log(logger::ERROR, "Invalid characters for clientID.");
        throw mqttException("Invalid clientID.");
    }
    cli_.set_callback(cb_);
}

void Publisher::connect()
{
    // Logging
	if(this->is_connected())
    {
		logger::log(logger::DEBUG, clientID_+std::string(" already connected."));
		return;
	}
	logger::log(logger::DEBUG, clientID_+std::string(" is trying to connect as a publisher to ")+address_);

    cli_.connect()->wait();

    // Logging
	logger::log(logger::DEBUG, clientID_+std::string(" is now connected and can publish to ")+address_);
}

void Publisher::publish(std::string topic, std::string payload)
{
    if(!this->is_connected())
    {
        // Logging
        logger::log(logger::ERROR, clientID_+std::string(" is not connected but it's trying to publish."));
        throw Politocean::mqttException("Publisher is not connected.");
    }
    logger::log(logger::DEBUG, clientID_+std::string(" is string to publish..."));
    mqtt::message_ptr pubmsg = mqtt::make_message(topic, clientID_+std::string(":\t")+payload);
    pubmsg->set_qos(QOS);

    cli_.publish(pubmsg, nullptr, cb_)->wait();
}

void Publisher::disconnect()
{
	if(!(this->is_connected()))
    {
        // Logging 
		logger::log(logger::DEBUG, clientID_+std::string(" already disconnected."));
		return;
	}

    auto toks = cli_.get_pending_delivery_tokens();

    // Logging
	logger::log(logger::DEBUG, clientID_+std::string(" publisher is being disconnected from ")+address_);

    cli_.disconnect()->wait();

    // Logging
    if (!toks.empty())
    {
        logger::log(logger::ERROR, std::string("There are pending delivery tokens for publisher ")+clientID_);
        throw Politocean::mqttException("There are pending delivery tokens.");
    } 
    else if(cli_.is_connected())
    {
        logger::log(logger::ERROR, clientID_+std::string(" publisher couldn't disconnect."));
        throw Politocean::mqttException("Publisher couldn't disconnect.");
    }
	logger::log(logger::DEBUG, clientID_+std::string(" publisher has been disconnected from ")+address_);
}

bool Publisher::is_connected(){
    return cli_.is_connected();
}

Publisher::~Publisher(){
    this->disconnect();
}

}