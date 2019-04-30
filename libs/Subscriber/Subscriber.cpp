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

	if(this->is_connected()){
		logger::log(logger::DEBUG, clientID_+string(" already connected."));
		return;
	}

	connOpts_ = new mqtt::connect_options();
	connOpts_->set_keep_alive_interval(20);
	connOpts_->set_clean_session(true);
    
	cb_ = new callback(cli_, *connOpts_, clientID_, topic_, QOS);
	cli_.set_callback(*cb_);

	cb_->set_callback(std::bind(&Subscriber::callback_wrapper, this, std::placeholders::_1));

	logger::log(logger::DEBUG, clientID_+string(" is trying to subscribe to ")+topic_);

	try{
    	cli_.connect(*connOpts_, nullptr, *cb_)->wait();

		if(!(cli_.is_connected()))
			throw mqttException("client couldn't connect.");
	}
	catch(std::exception& e){
        stringstream ss;
        ss << "Error while subscribing: " << e.what();
		logger::log(logger::ERROR, ss.str().c_str());
		throw Politocean::mqttException(ss.str());
	}

	logger::log(logger::DEBUG, clientID_+string(" is now a subscriber of ")+topic_);
}

void Subscriber::disconnect()
{
	if(!(this->is_connected())){
		logger::log(logger::DEBUG, clientID_+string(" already disconnected."));
		return;
	}
	logger::log(logger::DEBUG, clientID_+string(" is being disconnected from ")+topic_);

	try{
    	cli_.disconnect()->wait();

		if(cli_.is_connected())
			throw mqttException("client didn't disconnect.");
	}
	catch(std::exception& e){
        stringstream ss;
        ss << "Error while disconnecting: " << e.what();
		logger::log(logger::ERROR, ss.str().c_str());
		throw Politocean::mqttException(ss.str());
	}

	logger::log(logger::DEBUG, clientID_+string(" has been disconnected from ")+topic_);
}

bool Subscriber::is_connected(){
	return cli_.is_connected();
}

void Subscriber::wait(){
	while(cli_.is_connected());
}

Subscriber::~Subscriber() {
	this->disconnect();
	delete connOpts_;
	delete cb_;
}

void Subscriber::callback_wrapper(const std::string& payload){	
	size_t pos = payload.find_first_of(':');

	if(pos < payload.length())
		callback_(payload.substr(pos+2));
	else
		callback_(payload);
	
}

}