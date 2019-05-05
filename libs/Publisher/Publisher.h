/**
 * @author: pettinz
 */

#ifndef POLITOCEAN_PUBLISHER_H
#define POLITOCEAN_PUBLISHER_H

#include <chrono>
#include <string>
#include <sstream>

#include "mqtt/async_client.h"
#include "PolitoceanExceptions.hpp"
#include "logger.h"

namespace Politocean {
    
class Publisher {

    class callback : public virtual mqtt::callback, public virtual mqtt::iaction_listener {
        std::string clientID_;

    public:
        void connection_lost(const std::string& cause) override {
            std::stringstream ss;
            ss << "The Publisher " << clientID_ << " lost the connection.";
            logger::log(logger::ERROR, ss.str());
        }

        void delivery_complete(mqtt::delivery_token_ptr tok) override {
            std::stringstream ss;
            ss << clientID_ << ": message " << tok->get_message_id() << " delivered with return code " << tok->get_return_code();
            logger::log(logger::DEBUG, ss.str());
        }

        void  on_failure(const mqtt::token& tok) override {
            std::stringstream ss;
            ss << clientID_ << ": message " << tok.get_message_id() << " wasn't delivered, return code " << tok.get_return_code();
            logger::log(logger::ERROR, ss.str());
        }

        void on_success(const mqtt::token& tok) override {
            std::stringstream ss;
            ss << clientID_ << ": message " << tok.get_message_id() << " correctly delivered, return code " << tok.get_return_code();
            logger::log(logger::DEBUG, ss.str());
        }

        callback(const std::string& clientID) : clientID_(clientID) {}
    };

    std::string address_, clientID_;

    callback cb_;
    
    mqtt::async_client cli_;
    mqtt::token_ptr tok;
    mqtt::connect_options *connOpts_;

public:
    const int QOS = 1;
    const std::chrono::seconds TIMEOUT;

    // Creates new client with @clientID listening on a server with address @address
    Publisher(std::string address, std::string clientID);
    
    ~Publisher();

    // Connects the client to the server.
    void connect();

    // Disconnects the client from the server.
    void disconnect();

    // Sends a message @payload to the topic @topic.
    void publish(std::string topic, std::string payload);

    // States if it's already connected
    bool is_connected();

    // get client id
    std::string getClientId();
};

}

#endif //PUBLISHER_PUBLISHER_H
