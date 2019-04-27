//
// Created by pettinz.
//

#include "Publisher.h"

#include <string>
#include "PolitoceanExceptions.hpp"
#include "logger.h"

namespace Politocean {
using namespace std;

Publisher::Publisher(string address, string clientID)
    : address(address), clientID(clientID), TIMEOUT(10)
{
    asyncClient = new mqtt::async_client(address, clientID);
}

Publisher::~Publisher()
{
    delete asyncClient;
}

void Publisher::connect()
{
	logger::log(logger::DEBUG, clientID+string(" is trying to connect as a publisher to ")+address);
    tok = asyncClient->connect();
    tok->wait();
	logger::log(logger::DEBUG, clientID+string(" is now connected and can publish to ")+address);
}

void Publisher::publish(string topic, string payload)
{
    mqtt::message_ptr pubmsg = mqtt::make_message(topic, payload);
    pubmsg->set_qos(QOS);
    asyncClient->publish(pubmsg)->wait_for(TIMEOUT);
}

void Publisher::disconnect()
{
    auto toks = asyncClient->get_pending_delivery_tokens();

	logger::log(logger::DEBUG, clientID+string(" is being disconnected from ")+address);
    tok = asyncClient->disconnect();
    tok->wait();

    if (!toks.empty()){
        logger::log(logger::ERROR, "There are pending delivery tokens.");
        throw Politocean::mqttException("There are pending delivery tokens.");
    }
	logger::log(logger::DEBUG, clientID+string(" has been disconnected from ")+address);
}

}