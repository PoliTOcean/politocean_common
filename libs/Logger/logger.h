#ifndef POLITOCEAN_LOGGER_H
#define POLITOCEAN_LOGGER_H

#include <map>

namespace Politocean {

class logger {

public:
    
    enum levels {
        ERROR   = 0,
        WARNING = 50,
        CONFIG  = 400,
        INFO    = 500,
        DEBUG   = 700
    };
    
    static const int MAX_FILE_SIZE;

    logger(const std::string& tag);
    virtual void log(const levels level, const std::exception& exc);
    virtual void log(const levels level, const std::string& msg, const std::exception& exc);
    virtual void log(const levels level, const std::string& msg);

    static void enableLevel(const levels level);
    static logger& getInstance(const std::string& tag = "");
    static void setRootTag(const std::string& tag);

    logger operator=(const logger&);

protected:
    logger(const logger& lgr) : logger(lgr.tag) {}
    static const std::map<levels, std::string> levels_name;
    static std::string rootTag;
    static int activation_level;
    std::string tag;

private:
    static std::map<std::string, logger*> instances;

};

}

#endif