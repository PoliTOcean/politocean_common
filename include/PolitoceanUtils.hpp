#include <climits>
#include <nlohmann/json.hpp>

#define ABS(N) ((N<0)?(-N):(N))

namespace Politocean {

static long map(long x, long in_min, long in_max, long out_min = 0, long out_max = UCHAR_MAX) {
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

static void publish(Publisher publisher,  const string topic, const string status)
{
    nlohmann::json json[topic] = status;
    publisher.publish(topic, json->dump());
}

}