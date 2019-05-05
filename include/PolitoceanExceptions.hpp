#ifndef POLITOCEAN_EXCEPTIONS_H
#define POLITOCEAN_EXCEPTIONS_H

#include <stdexcept>

namespace Politocean {


class exception : public std::exception {
    /// an exception object as storage for error messages
    std::runtime_error m;

public:
    /// returns the explanatory string
    const char* what() const noexcept override
    {
        return m.what();
    }

    exception(const std::string& msg) : std::exception(), m(msg.c_str()) {}
    exception(const char *msg) : std::exception(), m(msg) {}
};



class mqttException : public exception {
public:
    mqttException(const std::string& msg) : exception(msg) {}
    mqttException(const char *msg) : exception(msg) {}
};

class loggerException : public exception {
public:
    loggerException(const std::string& msg) : exception(msg) {}
    loggerException(const char *msg) : exception(msg) {}
};

class controllerException : public exception {
public:
    controllerException(const std::string& msg) : exception(msg) {}
    controllerException(const char *msg) : exception(msg) {}
};

class JoystickException : public exception {
public:
    JoystickException(const std::string& msg) : exception(msg) {}
    JoystickException(const char *msg) : exception(msg) {}
};

}

#endif