#ifndef POLITOCEAN_CONSTANTS_H
#define POLITOCEAN_CONSTANTS_H

#include <string>

#define N_BUTTONS 8

namespace Politocean {
using namespace std;
    namespace Constants {
        
        namespace Topics {

            const string ERRORS { "errors/" };
            const string INFO { "info/" };

            const string HMI { "hmi/" };
            const string MICRO_ROV { "microRov/" };

            const string JOYSTICK { HMI + string("joystick/") };
            const string VISION { HMI + string("vision/") };

            const string JOYSTICK_AXIS { JOYSTICK + string("axis/") };
            const string JOYSTICK_BUTTONS { JOYSTICK + string("buttons/") };

            const string AUTODRIVE { VISION + string("autodrive") };

            const string MICRO_ROV_CAMERA { MICRO_ROV + string("camera") };
        }



        namespace Logger {

            const string LOGS_PATH { "logs/" };

            namespace Levels {
                const string ERROR { "error" };
                const string INFO { "info" };
                const string DEBUG { "debug" };
            }
        }
        
        namespace MicroRov {
            const string HOST_ADDRESS { "127.0.0.1" }; //TODO da togliere
            const string PUBLISHERID { "MicroRov_Publisher" }; //TODO da cambiare
            const string IP_ADDRESS { "10.0.0.3" };
        }

        namespace Hmi {
            const string CLIENT_ID { "hmi_core" };
            const string AUTODRIVE_ID { "autodrive" };
            const string UI_ID { "ui" };

            const string IP_ADDRESS { "10.0.0.1" };
            const string CAMERA_IP_ADDRESS { "10.0.0.4" };
        }

        namespace Rov {
            const string TOPIC_PREFIX { "rov/" };
            const string CLIENT_ID { "rov_core" };

            const string IP_ADDRESS { "10.0.0.2" };
        }

    }

}

#endif