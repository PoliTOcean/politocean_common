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
            namespace Millisenconds
            {
                static const int DFLT_STEPPER   = 10;
            }
            namespace Seconds
            {
                static const int SENSORS    = 1;
            }
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

            const string ARM                { "arm/" };
            const string SHOULDER           { ARM + "shoulder/" };
            const string WRIST              { ARM + "wrist/" };
            const string SHOULDER_VELOCITY  { SHOULDER + "velocity/" };
            const string WRIST_VELOCITY     { WRIST + "velocity/" };
            const string HAND               { ARM + "hand/" };
            const string HAND_VELOCITY      { HAND + "velocity/" };
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
            const string CMD_ID             { "cmd" };
            const string AUTODRIVE_ID       { "autodrive" };
            const string GUI_ID             { "gui" };
            const string JOYSTICK_ID        { "joystick" };
            const string SENSORS_ID         { "sensors" };

            const string IP_ADDRESS         { "10.0.0.1" };
            const string CAMERA_IP_ADDRESS  { "10.0.0.5" };
        }

        namespace Rov
        {
            const string TOPIC_PREFIX   { "rov/" };
            const string SPI_ID         { "spi" };

            const string IP_ADDRESS     { "10.0.0.2" };
            
            const string ARM_ID         { "Arm" };
        }

        namespace Commands
        {
            namespace Buttons
            {
                const int MOTORS            = 1;
                const int VDOWN             = 5;
                const int RESET             = 9;
                const int VUP               = 14;
                const int MEDIUM_FAST       = 24;
                const int SLOW              = 25;
                const int AUTONOMOUS        = 66;
                const int START_AND_STOP    = 2;
                const int SHOULDER_ENABLE   = 11;
                const int SHOULDER_DISABLE  = 10;
                const int WRIST_ENABLE      = 13;
                const int WRIST_DISABLE     = 12;
                const int WRIST             = 7;
                const int SHOULDER_UP       = 19;
                const int SHOULDER_DOWN     = 21;
                const int HAND              = 29;
            }
            
            namespace Axes
            {
                static const int X          = 0;
                static const int Y          = 1;
                static const int SHOULDER   = 6;
                static const int WRIST      = 4;
                static const int RZ         = 5;
                static const int HAND       = 3;
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
                const unsigned char SHOULDER_UP        = 0x15;
                const unsigned char SHOULDER_DOWN      = 0x16;
                const unsigned char SHOULDER_STOP      = 0x17;
                const unsigned char WRIST_START        = 0x18;
                const unsigned char WRIST_STOP         = 0x19;
                const unsigned char HAND_START         = 0x1A;
                const unsigned char HAND_STOP          = 0x1B;

                const unsigned char NONE               = 0x00;
            }

            namespace newActions {
                const string ON     { "ON" };
                const string OFF    { "OFF" };
                const string START  { "START" };
                const string STOP   { "STOP" };
                const string RESET  { "RESET" };

                namespace AtMega {
                    const string VDOWN_ON           { "VDOWN_ON" };
                    const string VDOWN_OFF          { "VDOWN_OFF" };
                    const string VUP_ON             { "VUP_ON" };
                    const string VUP_OFF            { "VUP_OFF" };
                    const string FAST               { "FAST" };
                    const string SLOW               { "SLOW" };
                    const string MEDIUM             { "MEDIUM" };
                    const string START_AND_STOP     { "START_AND_STOP" };                
                }

                namespace Arm {
                    const string SHOULDER_UP        { "UP" };
                    const string SHOULDER_DOWN      { "DOWN" };
                }

                const string NONE   { "NONE" };
            }
        }
    }

}

#endif