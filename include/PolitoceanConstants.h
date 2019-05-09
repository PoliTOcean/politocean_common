#ifndef POLITOCEAN_CONSTANTS_H
#define POLITOCEAN_CONSTANTS_H

#include <string>

namespace Politocean
{
    using namespace std;

    namespace Constants
    {
        const string CLIENT_ID_REGEX { "[\\w_]+" };

        namespace Timing
        {
            namespace Seconds
            {
                static const int SENSORS    = 1;
            }
        }

        namespace Pinout
        {
            static const int RESET              = 7;
            static const int MOTORS             = 12;

            static const int SHOULDER_EN        = 15;
            static const int SHOULDER_DIR       = 13;
            static const int SHOULDER_STEPPER   = 11;
            
            static const int WRIST_EN             = 40;
            static const int WRIST_DIR            = 38;
            static const int WRIST_STEPPER        = 36;
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
            const string SENSORS            { "sensors/" };

            const string VISION             { "vision/"};

            const string AUTODRIVE          { VISION + string("autodrive") };

            const string ARM            { "arm/" };
            const string ARM_SHOULDER   { ARM + "shoulder/" };
            const string ARM_WRIST      { ARM + "wrist/" };
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
            const string SENSORS_ID_PUB     { "sensors_pub" };
            const string SENSORS_ID_SUB     { "sensors_sub" };

            const string IP_ADDRESS         { "10.0.0.1" };
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
                const int FAST              = 24;
                const int MEDIUM            = 152;
                const int SLOW              = 153;
                const int AUTONOMOUS        = 66;
                const int START_AND_STOP    = 2;
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
                const unsigned char MOTORS_SWAP        = 0x01;
                const unsigned char MOTORS_ON          = 0x02;
                const unsigned char MOTORS_OFF         = 0x03;
                const unsigned char VDOWN_ON           = 0x04;
                const unsigned char VDOWN_OFF          = 0x05;
                const unsigned char VUP_ON             = 0x06;
                const unsigned char VUP_OFF            = 0x07;
                const unsigned char WRIST_SWAP         = 0x08;
                const unsigned char WRIST_ON           = 0x09;
                const unsigned char WRIST_OFF          = 0x0A;
                const unsigned char RESET              = 0x0B;
                const unsigned char FAST               = 0x0D;
                const unsigned char SLOW               = 0x0E;
                const unsigned char MEDIUM             = 0x0C;
                const unsigned char AUTONOMOUS_ON      = 0x10;
                const unsigned char AUTONOMOUS_OFF     = 0x11;
                const unsigned char START_AND_STOP     = 0x12;
                const unsigned char SHOULDER_ON        = 0x13;
                const unsigned char SHOULDER_OFF       = 0x14;

                const unsigned char NONE               = 0x00;
            }
        }
    }

}

#endif