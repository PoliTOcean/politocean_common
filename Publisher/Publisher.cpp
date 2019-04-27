/**
 * @author: pettinz
 */

#include <thread>
#include <chrono>

#include "Publisher.h"

#include "PolitoceanExceptions.hpp"
#include "logger.h"

namespace Politocean {

void Publisher::connect()
{
	logger::log(logger::DEBUG, clientID+string(" is trying to connect as a publisher to ")+address);
    cli_.set_callback(*cb_);

    cli_.connect()->wait();
	logger::log(logger::DEBUG, clientID+string(" is now connected and can publish to ")+address);
}

void Publisher::publish(std::string topic, std::string payload)
{
    action_listener listener;
    mqtt::message_ptr pubmsg = mqtt::make_message(topic, payload);
    pubmsg->set_qos(QOS);

    cli_.publish(pubmsg, nullptr, listener)->wait();
}

void Publisher::disconnect()
{
    auto toks = cli_.get_pending_delivery_tokens();

	logger::log(logger::DEBUG, clientID+string(" is being disconnected from ")+address);
    cli_.disconnect()->wait();

    if (!toks.empty()){
        logger::log(logger::ERROR, "There are pending delivery tokens.");
        throw Politocean::mqttException("There are pending delivery tokens.");
    }
	logger::log(logger::DEBUG, clientID+string(" has been disconnected from ")+address);
}

}