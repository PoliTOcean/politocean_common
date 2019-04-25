//
// Created by pettinz.
//

#include <sstream>
#include <string>
#include "Subscriber.h"
#include "PolitoceanExceptions.hpp"

namespace Politocean {
using namespace std;

Subscriber::Subscriber(string address, string clientID, string topic, void (*pFunction)(std::string payload))
    : address(address), clientID(clientID), topic(topic)
{
    connectOptions = new mqtt::connect_options();
    connectOptions->set_keep_alive_interval(20);
    connectOptions->set_clean_session(true);

    asyncClient = new mqtt::async_client(address, clientID);

    cb = new callback(*asyncClient, *connectOptions, clientID, topic, QOS, pFunction);
    asyncClient->set_callback(*cb);
}

Subscriber::~Subscriber()
{
    delete asyncClient, connectOptions, cb;
}

void Subscriber::connect()
{
    try {
        asyncClient->connect(*connectOptions, nullptr, *cb);
    } catch (const mqtt::exception& e) {
        std::stringstream ss;
        ss << "Error while connecting: " << e.what();
        throw Politocean::mqttException(ss.str().c_str());
    }
}

void Subscriber::setCallback(void (*pFunction)(std::string payload))
{
    cb->setpFunction(pFunction);
}

void Subscriber::disconnect()
{
    try {
        asyncClient->disconnect();
    } catch (mqtt::exception& e) {
        std::stringstream ss;
        ss << "Error while disconnecting: " << e.what();
        throw Politocean::mqttException(ss.str().c_str());
    }
}

void Subscriber::listen(){
    while(asyncClient->is_connected()); // TODO trovare un modo più custom
}

}