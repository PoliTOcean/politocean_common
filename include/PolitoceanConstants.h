#ifndef POLITOCEAN_CONSTANTS_H
#define POLITOCEAN_CONSTANTS_H

#include <string>

namespace Politocean
{
using namespace std;

namespace Constants
{
const string CLIENT_ID_REGEX{"[\\w_]+"};

namespace Timing
{
namespace Milliseconds
{
static const int MIN_WRIST = 100;
static const int MAX_WRIST = 1;
static const int AXES_DELAY = 50;
static const int SENSORS_UPDATE_DELAY = 2000;
static const int JOYSTICK = 50;
static const int COMMANDS = 10;
} // namespace Milliseconds
namespace Seconds
{
static const int SENSORS = 1;
}
namespace Microseconds
{
static const int DFLT_STEPPER = 10000;
static const int WRIST_MIN = 500;
static const int WRIST_MAX = 1000;
static const int DFLT_HEAD = 10000;
} // namespace Microseconds
} // namespace Timing

namespace Logger
{
const string LOGS_PATH{"pto_logs/"};

namespace Levels
{
const string ERROR{"error"};
const string WARNING{"warning"};
const string CONFIG{"config"};
const string INFO{"info"};
const string DEBUG{"debug"};
} // namespace Levels
} // namespace Logger

namespace Topics
{
const string LOGS{"logs/"};

namespace Logs
{
const string ERRORS{LOGS + Logger::Levels::ERROR + "/"};
const string WARNING{LOGS + Logger::Levels::WARNING + "/"};
const string CONFIG{LOGS + Logger::Levels::CONFIG + "/"};
const string INFO{LOGS + Logger::Levels::INFO + "/"};
const string DEBUG{LOGS + Logger::Levels::DEBUG + "/"};
} // namespace Logs

const string COMPONENTS{"components/"};

const string MICRO_ROV_CAMERA{"microRovCamera/"};

const string JOYSTICK{"joystick/"};
const string JOYSTICK_AXES{JOYSTICK + string("axis/")};
const string JOYSTICK_BUTTONS{JOYSTICK + string("buttons/")};

const string ATMEGA{"ATmega/"};
const string AXES{ATMEGA + "axes/"};
const string COMMANDS{ATMEGA + "commands/"};
const string SENSORS{"sensors/"};
const string POWER{"power/"};

const string VISION{"vision/"};

const string AUTODRIVE{VISION + string("autodrive")};

const string SKELETON{"skeleton/"};
const string SHOULDER{SKELETON + "shoulder/"};
const string WRIST{SKELETON + "wrist/"};
const string SHOULDER_VELOCITY{SHOULDER + "velocity/"};
const string WRIST_VELOCITY{WRIST + "velocity/"};
const string HAND{SKELETON + "hand/"};
const string HAND_VELOCITY{HAND + "velocity/"};
const string HEAD{SKELETON + "head/"};

const string MICROROV{"microRov/"};
const string MICROROV_VELOCITY{MICROROV + "velocity/"};
const string MICROROV_COMMANDS{MICROROV + "commands/"};
} // namespace Topics

namespace MicroRov
{
const string HOST_ADDRESS{"127.0.0.1"};         //TODO da togliere
const string PUBLISHERID{"MicroRov_Publisher"}; //TODO da cambiare
const string IP_ADDRESS{"10.0.0.3"};
const string MICRO_ROV_ID{"Rov_id"};
} // namespace MicroRov

namespace Hmi
{
const string MOUSE_ID{"mouse"};
const string CMD_ID{"cmd"};
const string AUTODRIVE_ID{"autodrive"};
const string GUI_ID{"gui"};
const string JOYSTICK_ID{"joystick"};
const string SENSORS_ID{"sensors"};
const string COMPONENTS_ID{"components"};

const string IP_ADDRESS{"10.0.0.1"};
const string CAMERA_IP_ADDRESS{"10.0.0.5"};
} // namespace Hmi

namespace Rov
{
const string TOPIC_PREFIX{"rov/"};
const string ATMEGA_ID{"ATMegaController"};

const string IP_ADDRESS{"10.0.0.2"};

const string SKELETON_ID{"skeleton"};
} // namespace Rov

namespace Commands
{
namespace Buttons
{
const int VUP = 0;
const int MOTORS = 1;
const int VDOWN = 5;
const int RESET = 3;
const int VUP_FAST = 14;
const int MEDIUM_FAST = 24;
const int SLOW = 25;
const int AUTONOMOUS = 66;
const int START_AND_STOP = 2;
const int SHOULDER_ENABLE = 11;
const int SHOULDER_DISABLE = 10;
const int WRIST_ENABLE = 13;
const int WRIST_DISABLE = 12;
const int HEAD_ENABLE = 9;
const int HEAD_DISABLE = 8;
const int WRIST = 7;
const int SHOULDER_UP = 19;
const int SHOULDER_DOWN = 21;
const int HAND = 29;
const int HEAD_UP = 15;
const int HEAD_DOWN = 17;
const int PITCH_CONTROL = 6;
const int CLICK_MOUSE = 30;
} // namespace Buttons

namespace Axes
{
static const int X = 0;
static const int Y = 1;
static const int SHOULDER = 6;
static const int WRIST = 4;
static const int RZ = 5;
static const int HAND = 3;
static const int PITCH = 2;
static const int X_MOUSE = 9;
static const int Y_MOUSE = 10;
} // namespace Axes

namespace Actions
{
const string ON{"ON"};
const string OFF{"OFF"};
const string START{"START"};
const string STOP{"STOP"};
const string RESET{"RESET"};

namespace ATMega
{
const string VDOWN_ON{"VDOWN_ON"};
const string VDOWN_OFF{"VDOWN_OFF"};
const string VUP_ON{"VUP_ON"};
const string VUP_OFF{"VUP_OFF"};
const string VUP_FAST_ON{"VUP_FAST_ON"};
const string VUP_FAST_OFF{"VUP_FAST_OFF"};
const string FAST{"FAST"};
const string SLOW{"SLOW"};
const string MEDIUM{"MEDIUM"};
const string START_AND_STOP{"START_AND_STOP"};
const string PITCH_CONTROL{"PITCH_CONTROL"};
} // namespace ATMega

namespace Stepper
{
const string UP{"UP"};
const string DOWN{"DOWN"};
} // namespace Stepper

const string NONE{"NONE"};
} // namespace Actions

namespace Control
{
const string MOTORS{"motors"};
}
} // namespace Commands

namespace Components
{
const string POWER{"power"};
const string SHOULDER{"shoulder"};
const string WRIST{"wrist"};
const string HEAD{"head"};
const string JOYSTICK{"joytick"};

enum Status
{
    ENABLED,
    DISABLED,
    ERROR
};
} // namespace Components
} // namespace Constants

} // namespace Politocean

#endif