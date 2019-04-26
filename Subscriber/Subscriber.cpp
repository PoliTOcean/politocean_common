/**
 * @author: pettinz
 * 
 * Implementation for MQTT Subscriber client.
 */ 

#include <sstream>
#include <string>

#include "Subscriber.h"

namespace Politocean {

const std::string Subscriber::DFLT_ADDRESS      { "tcp://localhost:1883" };
const std::string Subscriber::DFLT_CLIENT_ID    { "JoystickSubscriber" };
const std::string Subscriber::DFLT_TOPIC        { "JoystickTopic" };

void Subscriber::connect()
{
    connOpts_ = new mqtt::connect_options();
	connOpts_->set_keep_alive_interval(20);
	connOpts_->set_clean_session(true);
    
	cb_ = new callback(cli_, *connOpts_, clientID_, topic_, QOS);
	cli_.set_callback(*cb_);

    cli_.connect(*connOpts_, nullptr, *cb_);
}

void Subscriber::disconnect()
{
    cli_.disconnect()->wait();
}

}