#ifndef MQTT_CLIENT_H
#define MQTT_CLIENT_H

#include <mosquittopp.h>
#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <functional>
#include <logger.h>
#include <thread>
#include <chrono>
#include <Reflectable.hpp>

#define MQTT_CLIENT_LIB_TAG "MqttClient"
#define DEF_MOSQUITTO_PORT 1883

namespace Politocean
{

typedef std::function<void(const std::string &, const std::string &)> callback_t;
typedef struct mqttID_t
{
    std::string clientID;
    std::string ipAddress;
    int port = DEF_MOSQUITTO_PORT;

    mqttID_t(std::string cId, std::string ipAddr, int p = DEF_MOSQUITTO_PORT)
        : clientID(cId), ipAddress(ipAddr), port(p)
    {
    }

    bool operator==(const mqttID_t &o) const
    {
        return clientID == o.clientID && ipAddress == o.ipAddress && port == o.port;
    }

    bool operator<(const mqttID_t &o) const
    {
        return clientID < o.clientID ||
               (clientID == o.clientID && ipAddress < o.ipAddress) ||
               (clientID == o.clientID && ipAddress == o.ipAddress && port < o.port);
    }
} mqttID_t;

class MqttClient : public mosqpp::mosquittopp
{
    const std::string LIB_TAG = MQTT_CLIENT_LIB_TAG;

private:
    std::string clientID_, address_;
    int port_;
    std::thread *reconnectingThread;
    std::map<std::string, callback_t> topic_to_callback;
    static std::map<mqttID_t, MqttClient *> instances;

    MqttClient(const MqttClient &);
    MqttClient operator=(const MqttClient &);

protected:
    bool connected, reconnecting;

    const int keepalive = 10; // seconds
    const int delay = 500;    // milliseconds
    const int qos = 0;

    virtual void on_message(const struct mosquitto_message *msg);
    virtual void on_subscribe(int, int, const int *);
    virtual void on_disconnect(int rc);
    virtual void on_connect(int rc);
    virtual void on_publish(int mid);

    virtual std::string formatTopic(const std::string &topic);

public:
    /** static methods **/
    static MqttClient &getInstance(const std::string &clientID, const std::string &ipAddress, const int &port = DEF_MOSQUITTO_PORT);

    /** implementation **/
    MqttClient(const std::string &clientID, const std::string &address, const int &port = DEF_MOSQUITTO_PORT);

    ~MqttClient();

    /*
	 * Creates new client with @clientID listening on the topic @topic on a server with address @address.
     * It throws a mqtt::exception in case of failure.
	 */
    void connect();

    /**
     * Subscribe to topic with given callback
     * 
     * @param topic       : topic name
     * @param callback    : callbackfunction
     * 
     * @throw mqttException if it's connected
     */
    void subscribeTo(const std::string &topic, callback_t pf);
    void subscribeTo(const std::string &topic, std::function<void(const std::string &payload)> pf);

    template <class T>
    void subscribeTo(const std::string &topic, void (*pf)(const std::string &payload, const std::string &topic))
    {
        subscribeTo(topic, (callback_t)pf);
    }

    template <class T>
    void subscribeTo(const std::string &topic, void (*pf)(const std::string &payload))
    {
        subscribeTo(topic, (std::function<void(const std::string &payload)>)pf);
    }

    template <class T>
    void subscribeTo(const std::string &topic, void (T::*pf)(const std::string &payload), T *obj)
    {
        subscribeTo(topic, (std::function<void(const std::string &payload)>)std::bind(pf, obj, std::placeholders::_1));
    }

    template <class T>
    void subscribeTo(const std::string &topic, void (T::*pf)(const std::string &payload, const std::string &topic), T *obj)
    {
        subscribeTo(topic, (callback_t)std::bind(pf, obj, std::placeholders::_1, std::placeholders::_2));
    }

    /**
     * Subscribe to with Reflectable Objects
     */
    template <class R, typename std::enable_if<std::is_base_of<Reflectable::IReflectable, R>::value>::type * = nullptr>
    void subscribeTo(const std::string &topic, std::function<void(R object, const std::string &topic)> pf)
    {
        callback_t wrapper_function = [pf](const std::string &payload, const std::string &topic) {
            try
            {
                pf(R::parse(payload), topic);
            }
            catch (const Reflectable::ReflectableParsingException &e)
            {
                logger::getInstance(MQTT_CLIENT_LIB_TAG).log(logger::WARNING, e);
            }
            catch (...)
            {
                logger::getInstance(MQTT_CLIENT_LIB_TAG).log(logger::ERROR, "Unknown error while parsing MQTT Object");
            }
        };

        subscribeTo(topic, wrapper_function);
    }

    template <class R, typename std::enable_if<std::is_base_of<Reflectable::IReflectable, R>::value>::type * = nullptr>
    void subscribeTo(const std::string &topic, std::function<void(R object)> pf)
    {
        callback_t wrapper_function = [pf](const std::string &payload, const std::string &topic) {
            try
            {
                pf(R::parse(payload));
            }
            catch (const Reflectable::ReflectableParsingException &e)
            {
                logger::getInstance(MQTT_CLIENT_LIB_TAG).log(logger::WARNING, e);
            }
            catch (...)
            {
                logger::getInstance(MQTT_CLIENT_LIB_TAG).log(logger::ERROR, "Unknown error while parsing MQTT Object");
            }
        };

        subscribeTo(topic, wrapper_function);
    }

    template <class R, typename std::enable_if<std::is_base_of<Reflectable::IReflectable, R>::value>::type * = nullptr>
    void subscribeTo(const std::string &topic, void (*pf)(R object))
    {
        subscribeTo(topic, (std::function<void(R object)>)pf);
    }

    template <class R, typename std::enable_if<std::is_base_of<Reflectable::IReflectable, R>::value>::type * = nullptr>
    void subscribeTo(const std::string &topic, void (*pf)(R object, const std::string &topic))
    {
        subscribeTo(topic, (std::function<void(R object, const std::string &topic)>)pf);
    }

    template <class T,
              class R, typename std::enable_if<std::is_base_of<Reflectable::IReflectable, R>::value>::type * = nullptr>
    void subscribeTo(const std::string &topic, void (T::*pf)(R object), T *obj)
    {
        subscribeTo(topic, (std::function<void(R object)>)std::bind(pf, obj, std::placeholders::_1));
    }

    template <class T,
              class R, typename std::enable_if<std::is_base_of<Reflectable::IReflectable, R>::value>::type * = nullptr>
    void subscribeTo(const std::string &topic, void (T::*pf)(R object, const std::string &topic), T *obj)
    {
        subscribeTo(topic, (std::function<void(R object, const std::string &topic)>)std::bind(pf, obj, std::placeholders::_1, std::placeholders::_2));
    }

    /**
     * Subscribe to a family of topics
     */
    void subscribeToFamily(const std::string &topic, callback_t pf)
    {
        subscribeTo(formatTopic(topic) + "#", pf);
    }

    void subscribeToFamily(const std::string &topic, std::function<void(const std::string &payload)> pf)
    {
        subscribeTo(formatTopic(topic) + "#", pf);
    }

    template <class T>
    void subscribeToFamily(const std::string &topic, void (T::*pf)(const std::string &payload), T *obj)
    {
        subscribeToFamily(topic, std::bind(pf, obj, std::placeholders::_1));
    }

    template <class T>
    void subscribeToFamily(const std::string &topic, void (*pf)(const std::string &payload))
    {
        subscribeToFamily(topic, (std::function<void(const std::string &payload)>)pf);
    }

    template <class T>
    void subscribeToFamily(const std::string &topic, void (T::*pf)(const std::string &payload, const std::string &topic), T *obj)
    {
        subscribeToFamily(topic, std::bind(pf, obj, std::placeholders::_1, std::placeholders::_2));
    }

    /**
     * Subscribe to a family of topics with Reflectable Objects
     */
    template <class R, typename std::enable_if<std::is_base_of<Reflectable::IReflectable, R>::value>::type * = nullptr>
    void subscribeToFamily(const std::string &topic, std::function<void(R object, const std::string &topic)> pf)
    {
        subscribeTo(formatTopic(topic) + "#", pf);
    }

    template <class R, typename std::enable_if<std::is_base_of<Reflectable::IReflectable, R>::value>::type * = nullptr>
    void subscribeToFamily(const std::string &topic, std::function<void(R object)> pf)
    {
        subscribeTo(formatTopic(topic) + "#", pf);
    }

    template <class T,
              class R, typename std::enable_if<std::is_base_of<Reflectable::IReflectable, R>::value>::type * = nullptr>
    void subscribeToFamily(const std::string &topic, void (T::*pf)(R object), T *obj)
    {
        subscribeToFamily(topic, std::bind(pf, obj, std::placeholders::_1));
    }

    template <class T,
              class R, typename std::enable_if<std::is_base_of<Reflectable::IReflectable, R>::value>::type * = nullptr>
    void subscribeToFamily(const std::string &topic, void (T::*pf)(R object, const std::string &topic), T *obj)
    {
        subscribeToFamily(topic, std::bind(pf, obj, std::placeholders::_1, std::placeholders::_2));
    }

    /**
     * Unsubscribe from the topic
     * 
     * @param topic : topic name
     * 
     * @throw mqttException if it's connected
     */
    void unsubscribeFrom(const std::string &topic);
    void unsubscribeFrom(const std::vector<std::string> &topics);

    // Returns a vector with the subscribed topics.
    std::vector<std::string> getSubscribedTopics();

    // Sends a message @payload to the topic @topic.
    void publish(const std::string &topic, const std::string &payload);

    template <class R, typename std::enable_if<std::is_base_of<Reflectable::IReflectable, R>::value>::type * = nullptr>
    void publish(const std::string &topic, R &object)
    {
        publish(topic, object.stringify());
    }

    // Returns true if it's connected.
    bool is_connected();

    // Disconnects the client from the server.
    void disconnect();

    // Listens until it's connected.
    void wait();

    // getters
    std::string getClientId();
    std::string getIpAddress();
    int getPort();
};

} // namespace Politocean

#endif