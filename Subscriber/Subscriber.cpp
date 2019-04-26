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

	try{
    	cli_.connect(*connOpts_, nullptr, *cb_);
	}
	catch(mqtt::exception e){
        std::stringstream ss;
        ss << "MQTT error while connecting: " << e.what();
		//TODO logger error
		throw Politocean::mqttException(ss.str().c_str());
	}
	catch(std::exception e){
        std::stringstream ss;
        ss << "Generic error while connecting: " << e.what();
		//TODO logger error
		throw Politocean::exception(ss.str().c_str());
	}
}

void Subscriber::disconnect()
{
	try{
    	cli_.disconnect()->wait();
	}
	catch(mqtt::exception e){
        std::stringstream ss;
        ss << "MQTT error while disconnecting: " << e.what();
		//TODO logger error
		throw Politocean::mqttException(ss.str().c_str());
	}
	catch(std::exception e){
        std::stringstream ss;
        ss << "Generic error while disconnecting: " << e.what();
		//TODO logger error
		throw Politocean::exception(ss.str().c_str());
	}
}

}