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

class callback : public virtual mqtt::callback, public virtual mqtt::iaction_listener {
    const int N_RETRY_ATTEMPTS = 5;

    int nRetry, QOS_;
    std::string clientID_, topic_;

    mqtt::async_client& asyncClient_;
    mqtt::connect_options& connectOptions_;

    void (*pFunction_)(std::string payload);

    void reconnect() {
        std::this_thread::sleep_for(std::chrono::milliseconds(2500));
        try {
            asyncClient_.connect(connectOptions_, nullptr, *this);
        } catch (const mqtt::exception& e) {
            std::cerr << e.what() << std::endl;
            exit(EXIT_FAILURE);
        }
    }

    void on_failure(const mqtt::token& tok) override {
        std::cout << "Connection attempt failed" << std::endl;

        if (++nRetry > N_RETRY_ATTEMPTS)
            exit(EXIT_FAILURE);
        reconnect();
    }

    void on_success(const mqtt::token& tok) override {}

    void connected(const std::string& cause) override {
        std::cout << "\nConnection success" << std::endl;
        std::cout   << "\nSubscribing to topic '" << topic_ << "'\n"
                    << "\tfor client " << clientID_
                    << " using QoS " << QOS_ << std::endl;
        std::cout << "\nPress Q<Enter> to quit" << std::endl;

        asyncClient_.subscribe(topics_, QOS_);
    }

    void connection_lost(const std::string& cause) override {
        std::cout << "\nConnection lost";
        if (!cause.empty())
            std::cout << ": " << cause;
        std::cout << std::endl;
    }

    void message_arrived(mqtt::const_message_ptr msg) override {
        if (pFunction_ != nullptr)
            pFunction_(msg->get_payload_str());
    }

    void delivery_complete(mqtt::delivery_token_ptr token) override {}

public:
    callback(mqtt::async_client& asyncClient, mqtt::connect_options& connectOptions,
             std::string clientID, std::string topic, int QOS, void (*pFunction)(std::string payload) = nullptr) :
            nRetry(0),
            asyncClient_(asyncClient),
            connectOptions_(connectOptions),
            clientID_(clientID), topic_(topic), QOS_(QOS),
            pFunction_(pFunction) {}

    void setpFunction(void (*pFunction)(std::string payload)) { pFunction_ = pFunction; }
};

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

#endif //SUBSCRIBER_SUBSCRIBER_H
