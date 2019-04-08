//
// Created by pettinz.
//

#ifndef PUBLISHER_PUBLISHER_H
#define PUBLISHER_PUBLISHER_H

#include <string>

#include "mqtt/async_client.h"

class Publisher {
    std::string address, clientID;
    mqtt::async_client *asyncClient;
    mqtt::token_ptr tok;

public:
    const int QOS = 1;
    const std::chrono::seconds TIMEOUT;

    /**
     * Creates new client with @clientID listening on a server with address @address
     */
    Publisher(std::string address, std::string clientID);
    /**
    * Removes references for @asyncClient
    */
    ~Publisher()
    /*
     * Connects the client to the server.
     */
    void connect();
    /*
     * Disconnects the client from the server.
     */
    void disconnect();

    /**
     * Sends a message @payload to the topic @topic.
     */
    void publish(std::string topic, std::string payload);
};


#endif //PUBLISHER_PUBLISHER_H
