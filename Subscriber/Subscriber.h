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

#include "mqtt/async_client.h"
#include "include/callback.hpp"

namespace Politocean {

class Subscriber {
    std::string address_, clientID_, topic_;
    mqtt::async_client cli_;

    mqtt::connect_options *connOpts_;
    callback *cb_;

public:
    static const int QOS = 1;

    Subscriber(const std::string& address, const std::string& clientID, const std::string& topic)
        : address_(address), clientID_(clientID), topic_(topic), cli_(address, clientID) {}
	~Subscriber() { delete connOpts_; delete cb_; }

    /*
	 * Creates new client with @clientID listening on the topic @topic on a server with address @address.
     * It throws a mqtt::exception in case of failure.
	 */
    void connect();
    /**
	 * Listens the topic until the user press q<Enter> on the keyboard.
	 *  @pf is the pointer to the method function to be execute every time a message arrives
     *  @obj is the instance object to bind with @pf
	 */
    template<class M, class T>
    std::thread *listen(void (T::*pf)(const std::string& payload), M *obj) {
        cb_->set_callback(std::bind(pf, obj, std::placeholders::_1));

        return new std::thread([]() {
            while (std::tolower(std::cin.get()) != 'q');
        });
    }
    /*
	 * Disconnects the client from the server
	 */
    void disconnect();
};


}

#endif //SUBSCRIBER_SUBSCRIBER_H
