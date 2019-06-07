#ifndef REFLECTABLE_H
#define REFLECTABLE_H

#include <string>
#include <iostream>

namespace Reflectable {

class NotImplementedException : public std::exception {
    /// an exception object as storage for error messages
    std::runtime_error m;

public:
    /// returns the explanatory string
    const char* what() const noexcept override
    {
        return m.what();
    }

    NotImplementedException(const std::string& msg) : NotImplementedException(msg.c_str()) {}
    NotImplementedException(const char *msg) : std::exception(), m(msg) {}
};

class Reflectable {
public:
    template <typename T, typename std::enable_if<std::is_base_of<Reflectable, T>::value>::type* = nullptr>
    static T parse(std::string stringified) {
        throw NotImplementedException("Method PARSE has not been implemented.");
        T obj;
        return obj;
    }

    virtual std::string stringify() {
        throw NotImplementedException("Method STRINGIFY has not been implemented.");
        return "";
    }
};

}

#endif