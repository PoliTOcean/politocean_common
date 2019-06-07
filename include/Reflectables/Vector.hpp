#ifndef REFLECTABLE_VECTOR_H
#define REFLECTABLE_VECTOR_H

#include "../Reflectable.hpp"
#include <vector>
#include <string>
#include <boost/algorithm/string.hpp>
#include <sstream>
#include <iostream>

namespace Reflectable {

template <typename T, typename std::enable_if<std::is_base_of<Reflectable, T>::value>::type* = nullptr>
class Vector : public std::vector<T>, public Reflectable {

public:
    Vector(std::vector<T> v) : std::vector<T>(v) {}

    static Vector<T> parse(std::string stringified) {
        std::vector<T> vec;

        std::stringstream ss(stringified);
        std::string token;
        while (std::getline(ss, token, ' ')) {
            vec.push_back(T::parse(token));
        }
        return Vector<T>(vec);
    }

    static Vector<T> valueOf(std::vector<T> vec) {
        return Vector<T>(vec);
    }

    std::string stringify() {
        std::string str = "";
        for (T el : *this)
            str += el.stringify() + " ";
        return str;
    }
};

}

#endif