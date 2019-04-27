#ifndef ACTION_LISTENER_PUBLISHER_H
#define ACTION_LISTENER_PUBLISHER_H

#include "mqtt/iaction_listener.h"

class action_listener : public virtual mqtt::iaction_listener
{
public:
    void on_failure(const mqtt::token& tok) override { }

    void on_success(const mqtt::token& tok) override { }
};

#endif // ACTION_LISTENER_PUBLISHER_H