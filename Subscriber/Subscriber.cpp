/**
 * @author: pettinz
 * 
 * Implementation for MQTT Subscriber client.
 */ 

#include "Subscriber.h"

#include <sstream>
#include "logger.h"

namespace Politocean {

void Subscriber::connect()
{
    connOpts_ = new mqtt::connect_options();
	connOpts_->set_keep_alive_interval(20);
	connOpts_->set_clean_session(true);
    
	cb_ = new callback(cli_, *connOpts_, clientID_, topic_, QOS);
	cli_.set_callback(*cb_);

	logger::log(logger::DEBUG, "Trying to connect to... ...");
	try{
    	cli_.connect(*connOpts_, nullptr, *cb_);
	}
	catch(mqtt::exception e){
        std::stringstream ss;
        ss << "MQTT error while connecting: " << e.what();
		logger::log(logger::ERROR, ss.str().c_str());
		throw Politocean::mqttException(ss.str());
	}
	catch(std::exception& e){
        std::stringstream ss;
        ss << "Generic error while connecting: " << e.what();
		logger::log(logger::ERROR, ss.str().c_str());
		throw Politocean::exception(ss.str());
	}
	logger::log(logger::DEBUG, "Connected to... .");
}

void Subscriber::disconnect()
{
	logger::log(logger::DEBUG, "Trying to disconnect from... ...");
	try{
    	cli_.disconnect()->wait();
	}
	catch(mqtt::exception e){
        std::stringstream ss;
        ss << "MQTT error while disconnecting: " << e.what();
		logger::log(logger::ERROR, ss.str().c_str());
		throw Politocean::mqttException(ss.str());
	}
	catch(std::exception& e){
        std::stringstream ss;
        ss << "Generic error while disconnecting: " << e.what();
		logger::log(logger::ERROR, ss.str().c_str());
		throw Politocean::exception(ss.str());
	}
	logger::log(logger::DEBUG, "Disconnected from... .");
}

}