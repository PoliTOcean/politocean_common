#ifndef POLITOCEAN_CONSTANTS_H
#define POLITOCEAN_CONSTANTS_H

#include <string>

#define N_BUTTONS 8

namespace Politocean {
using namespace std;
    namespace Constants {
        
        namespace Logger {

            const string LOGS_PATH { "logs/" };

            namespace Levels {
                const string ERROR { "error" };
                const string INFO { "info" };
                const string DEBUG { "debug" };
            }
        }

        namespace Common {
            const string TOPIC_PREFIX { "common/" };

            namespace Topics {
                const string ERRORS { Common::TOPIC_PREFIX + string("errors") };
                const string INFO { Common::TOPIC_PREFIX + string("info") };
            }
        }
        
        namespace MicroRov {
            const string TOPIC_PREFIX { "microRov/" };

            namespace Topics {
                const string MICRO_ROV_CAMERA { TOPIC_PREFIX + string("camera") };
            }
            const string HOST_ADDRESS { "127.0.0.1" }; //TODO da togliere
            const string PUBLISHERID { "MicroRov_Publisher" }; //TODO da cambiare
            const string IP_ADDRESS { "10.0.0.3" };
        }

        namespace Hmi {
            const string TOPIC_PREFIX { "hmi/" };
            const string CLIENT_ID { "hmi_core" };

            namespace Topics {
                const string JOYSTICK_AXIS { Hmi::TOPIC_PREFIX + string("JoystickTopicAxis") };
                const string JOYSTICK_AXES { Hmi::TOPIC_PREFIX + string("JoystickTopicAxes") };
                const string JOYSTICK_BUTTON {Hmi::TOPIC_PREFIX + string("JoystickTopicButton")};
                const string JOYSTICK_BUTTONS {Hmi::TOPIC_PREFIX + string("JoystickTopicButtons")};
            }

            const string IP_ADDRESS { "10.0.0.1" };
            const string CAMERA_IP_ADDRESS { "10.0.0.4" };
        }

        namespace Rov {
            const string TOPIC_PREFIX { "rov/" };
            const string CLIENT_ID { "rov_core" };

            namespace Topics {
            }

            const string IP_ADDRESS { "10.0.0.2" };
        }

        namespace Buttons {
            enum buttons {
                MOTOR,
                RESET,
                AUTONOMOUS,
                WRIST,
                V_UP,
                V_DOWN,
                SLOW,
                MEDIUM_FAST
            };
        }

    }

}

#endif