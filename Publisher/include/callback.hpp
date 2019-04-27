/**
 * A callback class for use with the main MQTT client.
 */

#ifndef CALLBACK_PUBLISHER_H
#define CALLBACK_PUBLISHER_H

#include "mqtt/callback.h"

namespace Politocean {

class callback : public virtual mqtt::callback {
public:
    void connection_lost(const std::string& cause) override {

    }

    void delivery_complete(mqtt::delivery_token_ptr tok) override {

    }
};

}

#endif //CALLBACK_PUBLISHER_H