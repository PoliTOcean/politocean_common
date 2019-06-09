#ifndef REFLECTABLE_VECTOR_H
#define REFLECTABLE_VECTOR_H

#include "../Reflectable.hpp"
#include "../json.hpp"
#include <vector>
#include <string>
#include <boost/algorithm/string.hpp>
#include <sstream>
#include <iostream>

namespace Politocean {

namespace Types {

using namespace Reflectable;

template< class T, typename std::enable_if<std::is_base_of<Reflectable::IReflectable, T>::value || std::is_integral<T>::value, T>::type* = nullptr>
class Vector : public std::vector<T>, public IReflectable {
public:
    Vector() : std::vector<T>() {}
    Vector(std::vector<T> v) : std::vector<T>(v) {}

    template<typename R = T, typename std::enable_if<std::is_integral<R>::value, R>::type* = nullptr>
    static Vector<R> parse(const std::string& stringified) {
        std::vector<R> c_map = nlohmann::json::parse(stringified);
        return Vector<R>(c_map);
    }

    template<typename R = T, typename std::enable_if<std::is_base_of<Reflectable::IReflectable, R>::value, R>::type* = nullptr>
    static Vector<R> parse(const std::string& stringified) {
        std::vector<std::string> c_map = nlohmann::json::parse(stringified);
        Vector<R> vec;
        for (std::string el : c_map) {
            vec.emplace_back( R::parse(el) );
        }
        return vec;
    }

    static Vector<T> valueOf(std::vector<T> vec) {
        return Vector<T>(vec);
    }

    std::string stringify() override {
        return stringify(this);
    }

    template<typename R = T, typename std::enable_if<std::is_integral<R>::value, R>::type* = nullptr>
    std::string stringify(Vector<R> *vec) {
        nlohmann::json j_map;
        j_map = *vec;
        return j_map.dump();
    }  

    template<typename R = T, typename std::enable_if<std::is_base_of<Reflectable::IReflectable, R>::value, R>::type* = nullptr>
    std::string stringify(Vector<R> *vec) {
        nlohmann::json j_map;
        std::vector<string> tmp_vec;
        
        for (R el : *vec) 
            tmp_vec.emplace_back(el.stringify());
        
        j_map = tmp_vec;
        return j_map.dump();
    }
};
}
}

#endif