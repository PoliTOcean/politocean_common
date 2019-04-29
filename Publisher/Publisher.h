/**
 * @author: pettinz
 */

#ifndef POLITOCEAN_PUBLISHER_H
#define POLITOCEAN_PUBLISHER_H

#include <chrono>
#include <string>

#include "mqtt/async_client.h"
#include "action_listener.hpp"
#include "PolitoceanExceptions.hpp"

namespace Politocean {
    
class Publisher {

    class callback : public virtual mqtt::callback {
    public:
        void connection_lost(const std::string& cause) override {

        }

        void delivery_complete(mqtt::delivery_token_ptr tok) override {

        }
    };

    std::string address_, clientID_;
    mqtt::async_client cli_;
    mqtt::token_ptr tok;

    mqtt::connect_options *connOpts_;
    callback cb_;
    action_listener listener_;

    bool connected;

public:
    const int QOS = 1;
    const std::chrono::seconds TIMEOUT;

    // Creates new client with @clientID listening on a server with address @address
    Publisher(std::string address, std::string clientID)
        : address_(address), clientID_(clientID), cli_(address, clientID), cb_(), listener_("Publication"), TIMEOUT(10), connected(false) {}
    
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
