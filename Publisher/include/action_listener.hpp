#ifndef ACTION_LISTENER_PUBLISHER_H
#define ACTION_LISTENER_PUBLISHER_H

#include "mqtt/iaction_listener.h"

class action_listener : public virtual mqtt::iaction_listener
{
	void on_failure(const mqtt::token& tok) override {
        /*
		cout << "\tListener failure for token: "
			<< tok.get_message_id() << endl;
        */
	}

	void on_success(const mqtt::token& tok) override {
        /*
		cout << "\tListener success for token: "
			<< tok.get_message_id() << endl;
        */
	}
};

#endif //ACTION_LISTENER_PUBLISHER_H