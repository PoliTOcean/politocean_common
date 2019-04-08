//
// Created by pettinz.
//

#include "Publisher.h"

using namespace std;

Publisher::Publisher(string address, string clientID)
    : address(address), clientID(clientID), TIMEOUT(10)
{
    cout << "Initializing for server '" << address << "'...";
    asyncClient = new mqtt::async_client(address, clientID);
    cout << "OK" << endl;
}

Publisher::~Publisher()
{
    delete asyncClient;
}

void Publisher::connect()
{
    cout << "\nConnecting...";
    tok = asyncClient->connect();
    tok->wait();
    cout << "OK" << endl;
}

void Publisher::publish(string topic, string payload)
{
    cout << "\nSending message...";
    mqtt::message_ptr pubmsg = mqtt::make_message(topic, payload);
    pubmsg->set_qos(QOS);
    asyncClient->publish(pubmsg)->wait_for(TIMEOUT);
    cout << "OK" << endl;
}

void Publisher::disconnect()
{
    auto toks = asyncClient->get_pending_delivery_tokens();
    if (!toks.empty())
        cout << "Error: There are pending delivery tokens." << endl;

    cout << "\nDisconnecting...";
    tok = asyncClient->disconnect();
    tok->wait();
    cout << "OK" << endl;
}
