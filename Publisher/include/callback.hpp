/**
 * A callback class for use with the main MQTT client.
 */

#ifndef CALLBACK_PUBLISHER_H
#define CALLBACK_PUBLISHER_H

#include "mqtt/callback.h"

class callback : public virtual mqtt::callback
{
public:
	void connection_lost(const std::string& cause) override {
        /*
		cout << "\nConnection lost" << endl;
		if (!cause.empty())
			cout << "\tcause: " << cause << endl;
        */
	}

	void delivery_complete(mqtt::delivery_token_ptr tok) override {
        /*
		cout << "\tDelivery complete for token: "
			<< (tok ? tok->get_message_id() : -1) << endl;
        */
	}
};

#endif //CALLBACK_PUBLISHER_H