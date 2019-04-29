/**
 * @author: pettinz
 * 
 * Implementation for MQTT Subscriber client.
 */ 

#include "Subscriber.h"

#include <sstream>
#include <string>
#include "logger.h"
#include "PolitoceanExceptions.hpp"

namespace Politocean {

using namespace std;

void Subscriber::connect()
{
	connOpts_ = new mqtt::connect_options();
	connOpts_->set_keep_alive_interval(20);
	connOpts_->set_clean_session(true);
    
	cb_ = new callback(cli_, *connOpts_, clientID_, topic_, QOS);
	cli_.set_callback(*cb_);

	logger::log(logger::DEBUG, clientID_+string(" is trying to subscribe to ")+topic_);

	try{
    	cli_.connect(*connOpts_, nullptr, *cb_);
	}
	catch(std::exception& e){
        stringstream ss;
        ss << "Error while subscribing: " << e.what();
		logger::log(logger::ERROR, ss.str().c_str());
		throw Politocean::mqttException(ss.str());
	}

	logger::log(logger::DEBUG, clientID_+string(" is now a subscriber of ")+topic_);
	connected = true;
}

void Subscriber::disconnect()
{
	logger::log(logger::DEBUG, clientID_+string(" is being disconnected from ")+topic_);

	try{
    	cli_.disconnect()->wait();
	}
	catch(std::exception& e){
        stringstream ss;
        ss << "Error while disconnecting: " << e.what();
		logger::log(logger::ERROR, ss.str().c_str());
		throw Politocean::mqttException(ss.str());
	}

	logger::log(logger::DEBUG, clientID_+string(" has been disconnected from ")+topic_);
	connected = false;
}

bool Subscriber::isConnected(){
	return connected;
}

void Subscriber::wait(){
	while(this->isConnected());
}

}