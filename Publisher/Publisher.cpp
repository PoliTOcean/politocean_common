//
// Created by pettinz.
//

#include "Publisher.h"
#include "PolitoceanExceptions.hpp"

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
    tok = asyncClient->connect();
    tok->wait();
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

    tok = asyncClient->disconnect();
    tok->wait();

    if (!toks.empty()){
        throw Politocean::mqttException("There are pending delivery tokens.");
    }
}

}