#ifndef POLITOCEAN_EXCEPTIONS_H
#define POLITOCEAN_EXCEPTIONS_H

#include <stdexcept>

namespace Politocean {


class exception : public std::exception {
public:
    /// returns the explanatory string
    const char* what() const noexcept override
    {
        return m.what();
    }

    exception(std::string what_arg) : std::exception(), m(what_arg.c_str()) {}
    exception(const char* what_arg) : std::exception(), m(what_arg) {}

private:
    /// an exception object as storage for error messages
    std::runtime_error m;
};



class mqttException : public exception {
public:
    mqttException(std::string what_arg) : exception(what_arg) {}
    mqttException(const char* what_arg) : exception(what_arg) {}
};

class loggerException : public exception {
public:
    loggerException(std::string what_arg) : exception(what_arg) {}
    loggerException(const char* what_arg) : exception(what_arg) {}
};

}

#endif