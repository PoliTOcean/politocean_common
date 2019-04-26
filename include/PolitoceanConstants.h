#ifndef POLITOCEAN_CONSTANTS_H
#define POLITOCEAN_CONSTANTS_H

namespace Politocean {

    namespace Constants {
        
        namespace Logger {

            const std::string LOGS_PATH { "logs/" };

            namespace Levels {
                const std::string ERROR { "error" };
                const std::string INFO { "info" };
                const std::string DEBUG { "debug" };
            }
        }

        namespace Common {
        }

        namespace Topics {
            const std::string ERRORS { "Errors" };
            const std::string INFO { "Info" };
            const std::string MICRO_ROV_CAMERA { "MicroRovCamera" };
        }

        namespace MicroRov {
            const std::string HOST_ADDRESS { "127.0.0.1" };
            const std::string PUBLISHERID { "MicroRov_Publisher" };
            const std::string CAMERA_ERROR { "Error while setup of the camera. Please check." };
        }


    }

}

#endif