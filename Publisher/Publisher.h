/**
 * @author: pettinz
 */

#ifndef POLITOCEAN_PUBLISHER_H
#define POLITOCEAN_PUBLISHER_H

#include <chrono>
#include <string>

#include "mqtt/async_client.h"
#include "include/callback.hpp"

namespace Politocean {
    
class Publisher {
    std::string address_, clientID_;
    mqtt::async_client cli_;
    mqtt::token_ptr tok;

    callback cb_;

    bool connected;

public:
    const int QOS = 1;
    const std::chrono::seconds TIMEOUT;

    // Creates new client with @clientID listening on a server with address @address
    Publisher(std::string address, std::string clientID)
        : connected(false), address_(address), clientID_(clientID), cli_(address, clientID), cb_(), TIMEOUT(10) {}
    
    ~Publisher();

    // Connects the client to the server.
    void connect();

    // Disconnects the client from the server.
    void disconnect();

    // Sends a message @payload to the topic @topic.
    void publish(std::string topic, std::string payload);

    // States if it's already connected
    bool is_connected();
};

}

#endif //PUBLISHER_PUBLISHER_H
