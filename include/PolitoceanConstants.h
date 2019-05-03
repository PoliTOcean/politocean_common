#ifndef POLITOCEAN_CONSTANTS_H
#define POLITOCEAN_CONSTANTS_H

#include <string>

#define N_BUTTONS 8

namespace Politocean
{
    using namespace std;

    namespace Constants
    {
        const string CLIENT_ID_REGEX { "[\\w_\\-.\\/]+" };

        namespace Topics
        {
            const string ERRORS             { "errors/" };
            const string INFO               { "info/" };

            const string MICRO_ROV          { "microRov/" };
            const string MICRO_ROV_CAMERA   { MICRO_ROV + string("camera") };

            const string HMI                { "hmi/" };
            const string JOYSTICK           { HMI + string("joystick/") };
            const string JOYSTICK_AXES      { JOYSTICK + string("axis/") };
            const string JOYSTICK_BUTTONS   { JOYSTICK + string("buttons/") };

            const string AXES               { HMI + string("axes/") };
            const string BUTTONS            { HMI + string("buttons/") };

            const string VISION             { HMI + string("vision/") };

            const string AUTODRIVE          { VISION + string("autodrive") };

        }

        namespace Logger
        {
            const string LOGS_PATH { "logs/" };

            namespace Levels
            {
                const string ERROR  { "error" };
                const string INFO   { "info" };
                const string DEBUG  { "debug" };
            }
        }
        
        namespace MicroRov
        {
            const string HOST_ADDRESS   { "127.0.0.1" }; //TODO da togliere
            const string PUBLISHERID    { "MicroRov_Publisher" }; //TODO da cambiare
            const string IP_ADDRESS     { "10.0.0.3" };
        }

        namespace Hmi
        {
            const string CMD_ID_PUB         { "cmd_pub" };
            const string CMD_ID_SUB         { "cmd_sub" };
            const string AUTODRIVE_ID       { "autodrive" };
            const string UI_ID              { "ui" };

            const string IP_ADDRESS         { "10.0.0.1" };
            const string CAMERA_IP_ADDRESS  { "10.0.0.4" };
        }

        namespace Rov
        {
            const string TOPIC_PREFIX   { "rov/" };
            const string CLIENT_ID      { "rov_core" };

            const string IP_ADDRESS     { "10.0.0.2" };
        }

        namespace Commands
        {
            namespace Buttons
            {
                static const int MOTORS   = 1;
                static const int VDOWN       = 5;
                static const int WRIST       = 7;
                static const int RESET       = 9;
                static const int VUP         = 14;
                static const int MEDIUM_FAST = 24;
                static const int SLOW        = 25;
            }
            
            namespace Axes
            {
                static const int X          = 0;
                static const int Y          = 1;
                static const int SHOULDER   = 2;
                static const int WRIST      = 4;
                static const int RZ         = 5;
            }

            namespace Actions
            {
                const string MOTORS_ON          { "MOTORS_ON" };
                const string MOTORS_OFF         { "MOTORS_OFF" };
                const string VDOWN              { "VDOWN" };
                const string VDOWN_STOP         { "VDOWN_STOP" };
                const string VUP                { "VUP" };
                const string VUP_STOP           { "VUP_STOP" };
                const string WRIST              { "WRIST "};
                const string WRIST_STOP         { "WRIST_STOP "};
                const string RESET              { "RESET" };
                const string MEDIUM_FAST        { "MEDIUM_FAST" };
                const string MEDIUM_FAST_STOP   { "MEDIUM_FAST_STOP" };
                const string SLOW               { "SLOW" };
                const string SLOW_STOP          { "SLOW_STOP" };

                const string NONE               { "NONE" };
            }
        }
       }

    }

#endif