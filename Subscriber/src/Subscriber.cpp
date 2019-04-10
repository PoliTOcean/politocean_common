//
// Created by pettinz.
//

#include "Subscriber.h"

using namespace std;

Subscriber::Subscriber(string address, string clientID, string topic, void (*pFunction)(std::string payload))
    : address(address), clientID(clientID), topic(topic)
{
    connectOptions = new mqtt::connect_options();
    connectOptions->set_keep_alive_interval(20);
    connectOptions->set_clean_session(true);

    asyncClient = new mqtt::async_client(address, clientID);

    cb = new callback(*asyncClient, *connectOptions, clientID, topic, QOS, pFunction);
    asyncClient->set_callback(*cb);
}

Subscriber::~Subscriber()
{
    delete asyncClient, connectOptions, cb;
}

void Subscriber::connect()
{
    try {
        cout << "Connecting to the MQTT server..." << flush;
        asyncClient->connect(*connectOptions, nullptr, *cb);
    } catch (const mqtt::exception& e) {
        cerr << e.what() << endl;
        exit(EXIT_FAILURE);
    }
}

void Subscriber::setCallback(void (*pFunction)(std::string payload))
{
    cb->setpFunction(pFunction);
}

void Subscriber::listen()
{
    while (tolower(cin.get()) != 'q');
}

void Subscriber::disconnect()
{
    try {
        cout << "\nDisconnecting from the MQTT server..." << flush;
        asyncClient->disconnect();
        cout << "OK" << endl;
    } catch (mqtt::exception& e) {
        cerr << e.what() << endl;
        exit(EXIT_FAILURE);
    }
}