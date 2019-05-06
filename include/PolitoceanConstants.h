#ifndef POLITOCEAN_CONSTANTS_H
#define POLITOCEAN_CONSTANTS_H

#include <string>

namespace Politocean
{
    using namespace std;

    namespace Constants
    {
        const string CLIENT_ID_REGEX { "[\\w_]+" };

        namespace Pinout
        {
            static const int RESET  = 7;
            static const int MOTORS = 12;
        }

        namespace Topics
        {
            const string ERRORS             { "messages/errors/" };
            const string INFO               { "messages/info/" };
            const string COMPONENTS         { "messages/components/" };

            const string MICRO_ROV_CAMERA   { "microRovCamera/" };

            const string JOYSTICK           { "joystick/" };
            const string JOYSTICK_AXES      { JOYSTICK + string("axis/") };
            const string JOYSTICK_BUTTONS   { JOYSTICK + string("buttons/") };

            const string AXES               { "axes/" };
            const string BUTTONS            { "buttons/" };

            const string VISION             { "vision/"};

            const string AUTODRIVE          { VISION + string("autodrive") };

            const string ROV_ARM            { "rovArmControl" };
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
            const string GUI_ID_PUB         { "gui_pub" };
            const string GUI_ID_SUB         { "gui_sub" };
            const string CMD_PRS_ID_PUB     { "cmd_parser_pub" };
            const string CMD_PRS_ID_SUB     { "cmd_parser_sub" };
            const string JOYSTICK_ID_PUB    { "joystick_pub" };

            const string IP_ADDRESS         { "127.0.0.1" }; //{ "10.0.0.1" };
            const string CAMERA_IP_ADDRESS  { "10.0.0.4" };
        }

        namespace Rov
        {
            const string TOPIC_PREFIX   { "rov/" };
            const string SPI_ID_PUB     { "spi_pub" };
            const string SPI_ID_SUB     { "spi_sub" };

            const string IP_ADDRESS     { "10.0.0.2" };
            
            const string ARM_ID         { "Arm" };
        }

        namespace Commands
        {
            namespace Buttons
            {
                const int MOTORS            = 1;
                const int VDOWN             = 5;
                const int WRIST             = 7;
                const int RESET             = 9;
                const int VUP               = 14;
                const int MEDIUM_FAST       = 24;
                const int SLOW              = 25;
                const int AUTONOMOUS        = 66;
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
                const string MOTORS_SWAP        { "MOTORS" };
                const string MOTORS_ON          { "MOTORS_ON" };
                const string MOTORS_OFF         { "MOTORS_OFF" };
                const string VDOWN              { "VDOWN" };
                const string VDOWN_STOP         { "VDOWN_STOP" };
                const string VUP                { "VUP" };
                const string VUP_STOP           { "VUP_STOP" };
                const string WRIST_SWAP         { "WRIST" };
                const string WRIST_ON           { "WRIST_ON "};
                const string WRIST_OFF          { "WRIST_OFF "};
                const string RESET              { "RESET" };
                const string MEDIUM_FAST        { "MEDIUM_FAST" };
                const string MEDIUM_FAST_STOP   { "MEDIUM_FAST_STOP" };
                const string SLOW               { "SLOW" };
                const string SLOW_STOP          { "SLOW_STOP" };
                const string AUTONOMOUS_ON      { "AUTONOMOUS_ON" };
                const string AUTONOMOUS_OFF     { "AUTONOMOUS_OFF" };

                const string NONE               { "" };
            }
        }
       }

    }

#endif