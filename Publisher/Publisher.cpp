//
// Created by pettinz.
//

#include "Publisher.h"

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
    logger::log(logger::DEBUG, "Trying to connect to... ..."); // TODO aggiungere informazioni
    tok = asyncClient->connect();
    tok->wait();
    logger::log(logger::DEBUG, "Connected to... .");
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

    logger::log(logger::DEBUG, "Disconnecting from... ...");
    tok = asyncClient->disconnect();
    tok->wait();

    if (!toks.empty()){
        logger::log(logger::ERROR, "There are pending delivery tokens.");
        throw Politocean::mqttException("There are pending delivery tokens.");
    }
}

}