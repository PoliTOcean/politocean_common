/**
 * @author: pettinz
 */

#include <thread>
#include <chrono>

#include "Publisher.h"

#include "action_listener.hpp"
#include "PolitoceanExceptions.hpp"

namespace Politocean {

void Publisher::connect()
{
    cli_.set_callback(*cb_);

    cli_.connect()->wait();
}

void Publisher::publish(std::string topic, std::string payload)
{
    action_listener listener;
    mqtt::message_ptr pubmsg = mqtt::make_message(topic, payload);
    pubmsg->set_qos(QOS);

    cli_.publish(pubmsg, nullptr, listener)->wait();
}

void Publisher::disconnect()
{
    auto toks = cli_.get_pending_delivery_tokens();

    cli_.disconnect()->wait();

    if (!toks.empty()){
        throw Politocean::mqttException("There are pending delivery tokens.");
    }
}

}