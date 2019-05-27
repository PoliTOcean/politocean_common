#ifndef MQTT_CLIENT_H
#define MQTT_CLIENT_H

#include <mosquittopp.h>
#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <functional>

#define TAG "MqttClient: "

#define DEF_MOSQUITTO_PORT 1883

namespace Politocean {

typedef std::function<void(const std::string&, const std::string&)> callback_t;

class MqttClient : public mosqpp::mosquittopp
{
protected:
    std::string clientID_, address_;
    int port_;
    bool connected;
    
    std::map<std::string, callback_t> topic_to_callback;

    static const int keepalive = 60;
    static const int qos = 1;
    static std::string clientID;
    static std::map<std::string, MqttClient> instances;

    void on_message(const struct mosquitto_message *msg);


    void on_subscribe(int, int, const int *);
    void on_disconnect(int rc);
    void on_connect(int rc);
    void on_publish(int mid);

    std::string formatTopic(const std::string& topic);

public:
    /** static methods **/

    static MqttClient& getInstance(std::string clientID, std::string ipAddress, int port = DEF_MOSQUITTO_PORT);

    static MqttClient& getInstance(std::string ipAddress, int port = DEF_MOSQUITTO_PORT){
        return getInstance(MqttClient::clientID, ipAddress);
    }

    static void setClientId(std::string clientID);

    /** implementation **/
    MqttClient(const std::string& clientID, const std::string& address, const int& port = DEF_MOSQUITTO_PORT);

    ~MqttClient();

    /*
	 * Creates new client with @clientID listening on the topic @topic on a server with address @address.
     * It throws a mqtt::exception in case of failure.
	 */
    void connect();

    /**
     * Subscribe to topic with given callback
     * 
     * @topic       : topic name
     * @callback    : callbackfunction
     * 
     * @throw mqttException if it's connected
     */
    void subscribeTo(const std::string& topic, callback_t pf);
    void subscribeTo(const std::string& topic, void (*pf)(const std::string& payload));

    template<class T>
    void subscribeTo(const std::string& topic, void (T::*pf)(const std::string& payload))
    {
        subscribeTo(topic, pf);
    }

    template<class T>
    void subscribeTo(const std::string& topic, void (T::*pf)(const std::string& payload), T* obj)
    {
        subscribeTo(topic, std::bind(pf, obj, std::placeholders::_1));
    }

    template<class T>
    void subscribeTo(const std::string& topic, void (T::*pf)(const std::string& payload, const std::string& topic))
    {
        subscribeTo(topic, pf);
    }

    template<class T>
    void subscribeTo(const std::string& topic, void (T::*pf)(const std::string& payload, const std::string& topic), T* obj)
    {
        subscribeTo(topic, (callback_t)std::bind(pf, obj, std::placeholders::_1, std::placeholders::_2));
    }

    /**
     * Unsubscribe from the topic
     * 
     * @topic : topic name
     * 
     * @throw mqttException if it's connected
     */
    void unsubscribeFrom(const std::string& topic);
    void unsubscribeFrom(const std::vector<std::string>& topics);

    // Returns a vector with the subscribed topics.
    std::vector<std::string> getSubscribedTopics();

    // Sends a message @payload to the topic @topic.
    void publish(const std::string& topic, const std::string& payload);

    // Returns true if it's connected.
    bool is_connected();

    // Disconnects the client from the server.
    void disconnect();

    // Listens until it's connected.
    void wait();

    // get client id 
    std::string getClientId();
};

}


#endif