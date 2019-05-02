/**
 * @author: pettinz
 * 
 * MQTT Subscriber client definition
 */

#ifndef POLITOCEAN_SUBSCRIBER_H
#define POLITOCEAN_SUBSCRIBER_H

#include <iostream>
#include <string>
#include <sstream>
#include <thread>
#include <chrono>
#include <functional>
#include <map>
#include <vector>

#include "mqtt/async_client.h"
#include "action_listener.hpp"
#include "PolitoceanExceptions.hpp"
#include "logger.h"

namespace Politocean {

typedef std::function<void(const std::string&)> callback_t;

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

        std::function<void(mqtt::const_message_ptr msg)> pf_;

        mqtt::string_collection_ptr topics_;

        void reconnect() {
            std::this_thread::sleep_for(std::chrono::milliseconds(2500));
            try {
                cli_.connect(connOpts_, nullptr, *this);
            }
            catch (const mqtt::exception& exc) {
                logger::log(logger::ERROR, exc);
            }
        }

        // Re-connection failure
        void on_failure(const mqtt::token& tok) override {
            logger::log(logger::INFO, "Failed connection attempt. Retrying...");

            if (++nretry_ > N_RETRY_ATTEMPTS){
                logger::log(logger::ERROR, "Limit of retry attempts reached while trying to reconnect.");
            }
            reconnect();
        }

        // (Re)connection success
        // Either this or connected() can be used for callbacks.
        void on_success(const mqtt::token& tok) override {}

        void connected(const std::string& cause) override {
            std::stringstream ss;
            ss  << "\nConnection success"
                << "\nSubscribing to topic '" << topic_ << "'\n"
                << "\tfor client " << clientID_
                << " using QoS" << QOS_;
            logger::log(logger::DEBUG, ss.str());

            cli_.subscribe(topics_, mqtt::async_client::qos_collection(topics_->size(), QOS_));
        }

        // Callback for when the connection is lost.
        // This will initiate the attempt to manually reconnect.
        void connection_lost(const std::string& cause) override {
            std::stringstream ss;
            ss << "\nConnection lost" << std::endl;
            if (!cause.empty())
                ss << "\tcause: " << cause << std::endl;
            ss << "Reconnecting..." << std::endl;
            logger::log(logger::DEBUG, ss.str());
            
            nretry_ = 0;
            reconnect();
        }

        // Callback for when a message arrives.
        void message_arrived(mqtt::const_message_ptr msg) override {
            if (pf_ != nullptr)
                pf_(msg);
        }

        void delivery_complete(mqtt::delivery_token_ptr token) override {}

    public:
        const int N_RETRY_ATTEMPTS = 5;

        callback(mqtt::async_client& cli, mqtt::connect_options& connOpts, const std::string& clientID, mqtt::string_collection_ptr topics, int QOS)
                    : nretry_(0), cli_(cli), connOpts_(connOpts), subListener_("Subscription"), clientID_(clientID), topics_(topics), QOS_(QOS), pf_(nullptr) {}
        
        void set_callback(std::function<void(mqtt::const_message_ptr msg)> pf) {
            pf_ = pf;
        }
    };

    std::string address_, clientID_;
    mqtt::async_client cli_;

    mqtt::connect_options *connOpts_;
    callback *cb_;

    std::map<std::string, callback_t> topic_to_callback;
    
    void callback_wrapper(mqtt::const_message_ptr msg);

public:
    static const int QOS = 1;

    Subscriber(const std::string& address, const std::string& clientID);
    
	~Subscriber();

    /*
	 * Creates new client with @clientID listening on the topic @topic on a server with address @address.
     * It throws a mqtt::exception in case of failure.
	 */
    void connect();

    /**
     * Subscribe to topic with given callback
     * @param topic name
     * @param callback function
     */
    void subscribeTo(const std::string& topic, void (*pf)(const std::string& payload));
    
    template<class T>
    void subscribeTo(const std::string& topic, void (T::*pf)(const std::string& payload)){
        subscribeTo(topic, pf);
    }
    
    template<class T>
    void subscribeTo(const std::string& topic, void (T::*pf)(const std::string& payload), T* obj){
        subscribeTo(topic, std::bind(pf, obj, std::placeholders::_1));
    }

    /**
     * Unsubscribe from the topic
     * @param topic name
     */
    void unsubscribeFrom(const std::string& topic);

    void unsubscribeFrom(const std::vector<std::string>& topics);

    /**
     * get subscribed topics
     */
    std::vector<std::string> getSubscribedTopics();

    /**
     * Returns true if it's connected
     */
    bool is_connected();

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
