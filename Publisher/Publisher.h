/**
 * @author: pettinz
 */

#ifndef POLITOCEAN_PUBLISHER_H
#define POLITOCEAN_PUBLISHER_H

#include <string>

#include "mqtt/async_client.h"
#include "include/callback.hpp"

namespace Politocean {
    
class Publisher {
    std::string address_, clientID_;
    mqtt::async_client cli_;
    mqtt::token_ptr tok;

    callback *cb_;

public:
    const int QOS = 1;
    const std::chrono::seconds TIMEOUT;

    // Creates new client with @clientID listening on a server with address @address
    Publisher(std::string address, std::string clientID)
        : address_(address), clientID_(clientID), cli_(address, clientID), TIMEOUT(10) {}

    // Connects the client to the server.
    void connect();

    // Disconnects the client from the server.
    void disconnect();

    // Sends a message @payload to the topic @topic.
    void publish(std::string topic, std::string payload);
};

}

#endif //PUBLISHER_PUBLISHER_H
