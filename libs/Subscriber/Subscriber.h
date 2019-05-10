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
#include "mqtt/iaction_listener.h"
#include "PolitoceanExceptions.hpp"
#include "logger.h"

namespace Politocean {

typedef std::function<void(const std::string&, const std::string&)> callback_t;

class Subscriber : public virtual mqtt::callback, public virtual mqtt::iaction_listener {

    // Options to use if we need to reconnect
    mqtt::connect_options connOpts_;

    // An action listener to display the result of actions.
    std::string address_;
    std::string clientID_;
    mqtt::async_client cli_;
    
    // Counter for the number of connection retries
    int nretry_;

    int QOS_;

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

public:
    static const int QOS = 1;
    static const int N_RETRY_ATTEMPTS = 5;

    Subscriber(const std::string& address, const std::string& clientID) : address_(address), clientID_(clientID+"_sub"), cli_(address, clientID), nretry_(0), QOS_(QOS) {}
    
	~Subscriber();

    /*
	 * Creates new client with @clientID listening on the topic @topic on a server with address @address.
     * It throws a mqtt::exception in case of failure.
	 */
    void connect();

    /**
     * Subscribe to topic with given callback
     * 
     * @topic       : topic name
     * @callback    : callbackfunction
     * 
     * @throw mqttException if it's connected
     */
    void subscribeTo(const std::string& topic, callback_t pf);
    void subscribeTo(const std::string& topic, void (*pf)(const std::string& payload));

    template<class T>
    void subscribeTo(const std::string& topic, void (T::*pf)(const std::string& payload))
    {
        subscribeTo(topic, pf);
    }

    template<class T>
    void subscribeTo(const std::string& topic, void (T::*pf)(const std::string& payload), T* obj)
    {
        subscribeTo(topic, std::bind(pf, obj, std::placeholders::_1));
    }

    template<class T>
    void subscribeTo(const std::string& topic, void (T::*pf)(const std::string& payload, const std::string& topic))
    {
        subscribeTo(topic, pf);
    }

    template<class T>
    void subscribeTo(const std::string& topic, void (T::*pf)(const std::string& payload, const std::string& topic), T* obj)
    {
        subscribeTo(topic, (callback_t)std::bind(pf, obj, std::placeholders::_1, std::placeholders::_2));
    }

    /**
     * Unsubscribe from the topic
     * 
     * @topic : topic name
     * 
     * @throw mqttException if it's connected
     */
    void unsubscribeFrom(const std::string& topic);
    void unsubscribeFrom(const std::vector<std::string>& topics);

    // Returns a vector with the subscribed topics.
    std::vector<std::string> getSubscribedTopics();

    // Returns true if it's connected.
    bool is_connected();

    // Disconnects the client from the server.
    void disconnect();

    // Listens until it's connected.
    void wait();

    // get client id 
    std::string getClientId();
};


}

#endif //SUBSCRIBER_SUBSCRIBER_H
