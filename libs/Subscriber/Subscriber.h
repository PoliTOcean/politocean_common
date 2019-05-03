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
#include <regex>

#include "mqtt/async_client.h"
#include "mqtt/callback.h"
#include "action_listener.hpp"
#include "PolitoceanExceptions.hpp"
#include "logger.h"

namespace Politocean {

typedef std::function<void(const std::string&)> callback_t;

class Subscriber : public virtual mqtt::callback, public virtual mqtt::iaction_listener {

    // Counter for the number of connection retries
    int nretry_;

    // Options to use if we need to reconnect
    mqtt::connect_options connOpts_;

    // An action listener to display the result of actions.
    action_listener listener_;
    std::string clientID_;
    int QOS_;
    mqtt::string_collection_ptr topics_;
    std::string address_;
    mqtt::async_client cli_;

    std::map<std::string, callback_t> topic_to_callback;
    
    void reconnect();

    // Re-connection failure
    void on_failure(const mqtt::token& tok) override;

    // (Re)connection success
    // Either this or connected() can be used for callbacks.
    void on_success(const mqtt::token& tok) override;

    void connected(const std::string& cause) override;

    // Callback for when the connection is lost.
    // This will initiate the attempt to manually reconnect.
    void connection_lost(const std::string& cause) override;

    // Callback for when a message arrives.
    void message_arrived(mqtt::const_message_ptr msg) override;

    void delivery_complete(mqtt::delivery_token_ptr token) override;

public:
    static const int QOS = 1;
    static const int N_RETRY_ATTEMPTS = 5;

    Subscriber(const std::string& address, const std::string& clientID);
    
	~Subscriber();

    /*
	 * Creates new client with @clientID listening on the topic @topic on a server with address @address.
     * It throws a mqtt::exception in case of failure.
	 */
    void connect();

    /**
     * Subscribe to topic with given callback
     * 
     * @param topic name
     * @param callback function
     * 
     * @throw mqttException if it's connected
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
     * 
     * @param topic name
     * 
     * @throw mqttException if it's connected
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
