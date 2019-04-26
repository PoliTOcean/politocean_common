/**
 * Callbacks for the success or failures of requested actions.
 * This could be used to initiate further action, but here we just log the
 * results to the console.
 */

#ifndef ACTION_LISTENER_SUBSCRIBER_H
#define ACTION_LISTENER_SUBSCRIBER_H

#include <iostream>

#include "mqtt/async_client.h"

class action_listener : public virtual mqtt::iaction_listener
{
	std::string name_;

	void on_failure(const mqtt::token& tok) override {
        /*
		std::cout << name_ << " failure";
		if (tok.get_message_id() != 0)
			std::cout << " for token: [" << tok.get_message_id() << "]" << std::endl;
		std::cout << std::endl;
        */
	}

	void on_success(const mqtt::token& tok) override {
        /*
		std::cout << name_ << " success";
		if (tok.get_message_id() != 0)
			std::cout << " for token: [" << tok.get_message_id() << "]" << std::endl;
		auto top = tok.get_topics();
		if (top && !top->empty())
			std::cout << "\ttoken topic: '" << (*top)[0] << "', ..." << std::endl;
		std::cout << std::endl;
        */
	}

public:
	action_listener(const std::string& name) : name_(name) {}
};

#endif //ACTION_LISTENER_SUBSCRIBER_H