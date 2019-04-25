//
// Created by pettinz.
//

#ifndef SUBSCRIBER_SUBSCRIBER_H
#define SUBSCRIBER_SUBSCRIBER_H

#include <iostream>
#include <string>
#include <thread>
#include <chrono>

#include "mqtt/async_client.h"
#include "include/callback.hpp"

namespace Politocean {

class Subscriber {
    std::string address, clientID, topic;

    mqtt::async_client *asyncClient;
    mqtt::connect_options *connectOptions;
    callback *cb;
public:
    const int QOS = 1;

    Subscriber() = default;
    /**
     * Creates new client with @clientID listening on the topic @topic on a server with address @address
     */
    Subscriber(std::string address, std::string clientID, std::string topic, void (*pFunction)(std::string payload) = nullptr);
    /**
     * Removes references for pointers @asyncClient, @connectOptions, @cb
     */
    ~Subscriber();

    /*
     * Connects the client to the server.
     */
    void connect();
    void setCallback(void (*pFunction)(std::string payload));
    /*
     * Listens the topic until the user press q<Enter> on the keyboard
     */
    void listen();
    /*
     * Disconnects the client from the server.
     */
    void disconnect();

};

}

#endif //SUBSCRIBER_SUBSCRIBER_H
