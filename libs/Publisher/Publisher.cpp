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
    : address_(address), clientID_(clientID+"_pub"), cli_(address, clientID), TIMEOUT(10) {}

void Publisher::connect()
{
    // Logging
	if(cli_.is_connected())
    {
		logger::log(logger::INFO, clientID_+std::string(" already connected."));
		return;
	}
	logger::log(logger::INFO, clientID_+std::string(" is trying to connect as a publisher to ")+address_);

    if(!regex_match(clientID_, std::regex(Constants::CLIENT_ID_REGEX)))
    {
        logger::log(logger::ERROR, "Invalid characters for clientID.");
        throw mqttException("Invalid clientID.");
    }
    cli_.set_callback(*this);

	connOpts_.set_keep_alive_interval(5);
	connOpts_.set_clean_session(true);
	connOpts_.set_automatic_reconnect(true);

    while(!cli_.is_connected())
        cli_.connect(connOpts_, nullptr, *this)->wait_for(std::chrono::seconds(5));


    nretry_ = N_RETRY_ATTEMPTS;
	    
    // Logging
	logger::log(logger::INFO, clientID_+std::string(" is now connected and can publish to ")+address_);
}

void Publisher::publish(std::string topic, std::string payload)
{
    if(!cli_.is_connected())
    {
        // Logging
        logger::log(logger::ERROR, clientID_+std::string(" is not connected but it's trying to publish."));
        //throw Politocean::mqttException("Publisher is not connected.");
        return;
    }
    logger::log(logger::DEBUG, clientID_+std::string(" is trying to publish..."));
    mqtt::message_ptr pubmsg = mqtt::make_message(topic, payload);
    pubmsg->set_qos(QOS);

    cli_.publish(pubmsg, nullptr, *this)->wait();
}

void Publisher::disconnect()
{
	if(!(cli_.is_connected()))
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
	return cli_.is_connected() || nretry_<N_RETRY_ATTEMPTS;
}

std::string Publisher::getClientId(){
    return clientID_;
}

Publisher::~Publisher(){
    this->disconnect();
}


void Publisher::reconnect() {
	try {
		cli_.reconnect()->wait_for(std::chrono::seconds(5));
	}
	catch (const mqtt::exception& exc) {
		logger::log(logger::ERROR, exc);
	}
}

/** Inherited functions **/
void Publisher::connection_lost(const std::string& cause) {
    std::stringstream ss;
    ss << "The Publisher " << clientID_ << " lost the connection.";
    logger::log(logger::ERROR, ss.str());
	if (!cause.empty())
		ss << "\tcause: " << cause << std::endl;
	ss << "\tReconnecting..." << std::endl;
	logger::log(logger::DEBUG, ss.str());
	
	nretry_ = 0;
	reconnect();
}

void Publisher::delivery_complete(mqtt::delivery_token_ptr tok) {
    std::stringstream ss;
    ss << clientID_ << ": message " << tok->get_message_id() << " delivered with return code " << tok->get_return_code();
    logger::log(logger::DEBUG, ss.str());
}

void Publisher::on_failure(const mqtt::token& tok) {
    if(!cli_.is_connected()){
        logger::log(logger::INFO, "Failed connection attempt. Retrying...");
        if (++nretry_ > N_RETRY_ATTEMPTS){
            logger::log(logger::ERROR, "Limit of retry attempts reached while trying to reconnect.");
        }
        else reconnect();
    }else{
        std::stringstream ss;
        ss << clientID_ << ": message " << tok.get_message_id() << " wasn't delivered, return code " << tok.get_return_code();
        logger::log(logger::ERROR, ss.str());
    }
}

void Publisher::on_success(const mqtt::token& tok) {
    std::stringstream ss;
    ss << clientID_ << ": message " << tok.get_message_id() << " correctly delivered, return code " << tok.get_return_code();
    logger::log(logger::DEBUG, ss.str());
}

void Publisher::connected(const std::string& cause) {
    std::stringstream ss;
    ss << "The Publisher " << clientID_ << " successfully connected.";
    logger::log(logger::DEBUG, ss.str());
}

}