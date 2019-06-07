#ifndef REFLECTABLE_INTEGER_H
#define REFLECTABLE_INTEGER_H

#include "../Reflectable.hpp"
namespace Reflectable {
    
class Integer : public Reflectable {
    int value;

public:
    Integer(int value) : value(value) {}

    static Integer parse(std::string stringified) {
        // TODO catch exception
        return Integer(std::stoi(stringified));
    }

    static Integer valueOf(int value) {
        return Integer(value);
    }

    std::string stringify() {
        return std::to_string(value);
    }

    int getInt() {
        return value;
    }
};

}
#endif