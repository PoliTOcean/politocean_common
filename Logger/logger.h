#ifndef POLITOCEAN_LOGGER_H
#define POLITOCEAN_LOGGER_H

#include <map>

namespace Politocean {

class logger {

public:
    
    enum levels {
        ERROR,
        DEBUG,
        INFO
    };
    
    static const int MAX_FILE_SIZE;

    static void log(const levels level, const std::exception& exc);
    static void log(const levels level, const std::string& msg, const std::exception& exc);
    static void log(const levels level, const std::string& msg);
    static void enableLevel(const levels level, const bool mode);

private:
    static const std::map<levels, std::string> levels_name;
    static std::map<levels, bool> is_enabled;

};

}

#endif