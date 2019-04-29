/**
 * @author: pettinz
 * 
 * MQTT Subscriber client definition
 */

#ifndef POLITOCEAN_SUBSCRIBER_H
#define POLITOCEAN_SUBSCRIBER_H

#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <functional>

#include "mqtt/async_client.h"
#include "action_listener.hpp"
#include "PolitoceanExceptions.hpp"

namespace Politocean {

class Subscriber {

    class callback : public virtual mqtt::callback, public virtual mqtt::iaction_listener {
        // Counter for the number of connection retries
        int nretry_;

        // The MQTT client
        mqtt::async_client& cli_;
        // Options to use if we need to reconnect
        mqtt::connect_options& connOpts_;
        // An action listener to display the result of actions.
        action_listener subListener_;

        std::string clientID_, topic_;
        int QOS_;

        std::function<void(const std::string& payload)> pf_;

        void reconnect() {
            std::this_thread::sleep_for(std::chrono::milliseconds(2500));
            try {
                cli_.connect(connOpts_, nullptr, *this);
            }
            catch (const mqtt::exception& exc) {
                //TODO logger error
                throw Politocean::mqttException(exc.what());
            }
        }

        // Re-connection failure
        void on_failure(const mqtt::token& tok) override {
            //TODO logger info: "Failed connection attempt. Retrying..."
            if (++nretry_ > N_RETRY_ATTEMPTS){
                //TODO logger error
                throw Politocean::mqttException("Limit of retry attempts reached while trying to reconnect.");
            }
            reconnect();
        }

        // (Re)connection success
        // Either this or connected() can be used for callbacks.
        void on_success(const mqtt::token& tok) override {}

        void connected(const std::string& cause) override {
            /* Logger info:
            std::cout << "\nConnection success" << std::endl;
            std::cout << "\nSubscribing to topic '" << topic_ << "'\n"
                << "\tfor client " << clientID_
                << " using QoS" << QOS_ << "\n"
            */
            cli_.subscribe(topic_, QOS_, nullptr, subListener_);
        }

        // Callback for when the connection is lost.
        // This will initiate the attempt to manually reconnect.
        void connection_lost(const std::string& cause) override {
            /* Logger info:
            std::cout << "\nConnection lost" << std::endl;
            if (!cause.empty())
                std::cout << "\tcause: " << cause << std::endl;

            std::cout << "Reconnecting..." << std::endl;
            */
            nretry_ = 0;
            reconnect();
        }

        // Callback for when a message arrives.
        void message_arrived(mqtt::const_message_ptr msg) override {
            if (pf_ != nullptr)
                pf_(msg->to_string());
        }

        void delivery_complete(mqtt::delivery_token_ptr token) override {}

    public:
        const int N_RETRY_ATTEMPTS = 5;

        callback(mqtt::async_client& cli, mqtt::connect_options& connOpts, const std::string& clientID, const std::string& topic, int QOS)
                    : nretry_(0), cli_(cli), connOpts_(connOpts), subListener_("Subscription"), clientID_(clientID), topic_(topic), QOS_(QOS), pf_(nullptr) {}
        
        void set_callback(std::function<void(const std::string& payload)> pf) {
            pf_ = pf;
        }
    };

    std::string address_, clientID_, topic_;
    mqtt::async_client cli_;

    mqtt::connect_options *connOpts_;
    callback *cb_;

    bool connected;

public:
    static const int QOS = 1;

    template<class T>
    Subscriber(const std::string& address, const std::string& clientID, const std::string& topic, void (T::*pf)(const std::string& payload))
        : address_(address), clientID_(clientID), topic_(topic), cli_(address, clientID), connected(false) {
        
        this->connect();
        this->setCallback(pf);
    }
    
    template<class T, class M>
    Subscriber(const std::string& address, const std::string& clientID, const std::string& topic,
                void (T::*pf)(const std::string& payload), M* obj)
        : address_(address), clientID_(clientID), topic_(topic), cli_(address, clientID), connected(false) {
        
        this->connect();
        this->setCallback(pf, obj);
    }
    

    Subscriber(const std::string& address, const std::string& clientID, const std::string& topic, void (*pf)(const std::string& payload))
        : address_(address), clientID_(clientID), topic_(topic), cli_(address, clientID), connected(false) {
        
        this->connect();
        this->setCallback(pf);
    }
    
	~Subscriber() { delete connOpts_; delete cb_; }

    /*
	 * Creates new client with @clientID listening on the topic @topic on a server with address @address.
     * It throws a mqtt::exception in case of failure.
	 */
    void connect();

    /**
	 * Update 
	 */
    template<class T>
    void setCallback(void (T::*pf)(const std::string& payload)){
        cb_->set_callback(pf);
    }

    template<class T, class M>
    void setCallback(void (T::*pf)(const std::string& payload), M* obj){
        cb_->set_callback(std::bind(pf, obj, std::placeholders::_1));
    }

    void setCallback(void (*pf)(const std::string& payload)){
        cb_->set_callback(pf);
    }

    /**
     * Returns true if it's connected
     */
    bool isConnected();

    /*
	 * Disconnects the client from the server
	 */
    void disconnect();

    /**
     * Listens until it's connected
     */
    void wait();
};


}

#endif //SUBSCRIBER_SUBSCRIBER_H
