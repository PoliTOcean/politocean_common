/**
 * @author: pettinz
 */

#include <thread>

#include "Publisher.h"

#include "PolitoceanExceptions.hpp"
#include "logger.h"

namespace Politocean {
    
void Publisher::connect()
{
	logger::log(logger::DEBUG, clientID_+std::string(" is trying to connect as a publisher to ")+address_);
    cli_.connect()->wait();
	logger::log(logger::DEBUG, clientID_+std::string(" is now connected and can publish to ")+address_);
    connected = true;
}

void Publisher::publish(std::string topic, std::string payload)
{
    if(!connected){
        logger::log(logger::ERROR, clientID_+std::string(" is not connected but it's trying to publish."));
        throw Politocean::mqttException("Publisher is not connected.");
    }
    
    mqtt::message_ptr pubmsg = mqtt::make_message(topic, clientID_+std::string(":\t")+payload);
    pubmsg->set_qos(QOS);

    cli_.publish(pubmsg, nullptr, listener_)->wait();
}

void Publisher::disconnect()
{
    auto toks = cli_.get_pending_delivery_tokens();

	logger::log(logger::DEBUG, clientID_+std::string(" is being disconnected from ")+address_);
    cli_.disconnect()->wait();

    if (!toks.empty()){
        logger::log(logger::ERROR, "There are pending delivery tokens.");
        throw Politocean::mqttException("There are pending delivery tokens.");
    }
	logger::log(logger::DEBUG, clientID_+std::string(" has been disconnected from ")+address_);
    connected = false;
}

bool Publisher::is_connected(){
    return connected;
}

Publisher::~Publisher(){
    this->disconnect();
}

}