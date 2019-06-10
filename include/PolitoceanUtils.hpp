#ifndef POLITOCEAN_UTILS_H
#define POLITOCEAN_UTILS_H

#include <climits>
#include "json.hpp"
#include "../libs/MqttClient/MqttClient.h"
#include "PolitoceanConstants.h"

#define ABS(N) ((N<0)?(-N):(N))

namespace Politocean {
using namespace Politocean::Constants;

static long map(long x, long in_min, long in_max, long out_min = 0, long out_max = UCHAR_MAX) {
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

}

/*
 * {
 *          'Components' : 'POWER',
 *          'Status'     : 0-1-2 (have a look to Status enum in PolitoceanConstants.h)
 * }
 */

#endif