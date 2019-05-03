/**
 * Callbacks for the success or failures of requested actions.
 * This could be used to initiate further action, but here we just log the
 * results to the console.
 */

#ifndef ACTION_LISTENER_SUBSCRIBER_H
#define ACTION_LISTENER_SUBSCRIBER_H

#include <string>

#include "mqtt/iaction_listener.h"

namespace Politocean {

class action_listener : public virtual mqtt::iaction_listener
{
	std::string name_;

	void on_failure(const mqtt::token& tok) override {
	}

	void on_success(const mqtt::token& tok) override {
	}

public:
	action_listener(const std::string& name) : name_(name) {}
};

}

#endif //ACTION_LISTENER_SUBSCRIBER_H