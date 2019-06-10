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
    Vector(int N, int values) : std::vector<T>(N, values) {}
    Vector(std::vector<T> v) : std::vector<T>(v) {}

    template<typename R = T, typename std::enable_if<std::is_integral<R>::value, R>::type* = nullptr>
    static Vector<R> parse(const std::string& stringified) {
        Vector<R> vec;
        try
        {
            auto c_map = nlohmann::json::parse(stringified);
            vec = c_map.get<Vector<R>>();
        }
        catch (const std::exception& e)
        {
            logger::getInstance().log(logger::WARNING, "An error occurred parsing Vector value.", e);
            throw ReflectableParsingException(std::string("An error occurred parsing Vector value: ")+e.what());
        }
        catch (...)
        {
            logger::getInstance().log(logger::WARNING, "An error occurred parsing Vector value.");
            throw ReflectableParsingException("An error occurred parsing Vector value.");
        }
        return vec;
    }

    template<typename R = T, typename std::enable_if<std::is_base_of<Reflectable::IReflectable, R>::value, R>::type* = nullptr>
    static Vector<R> parse(const std::string& stringified) {
        Vector<R> vec;
        try
        {
            auto c_map = nlohmann::json::parse(stringified);
            std::vector<std::string> vec_s = c_map.get<std::vector<std::string>>();

            for (std::string el : vec_s) {
                vec.emplace_back( R::parse(el) );
            }
        }
        catch (const std::exception& e)
        {
            logger::getInstance().log(logger::WARNING, "An error occurred parsing Vector value.", e);
            throw ReflectableParsingException(std::string("An error occurred parsing Vector value: ")+e.what());
        }
        catch (...)
        {
            logger::getInstance().log(logger::WARNING, "An error occurred parsing Vector value.");
            throw ReflectableParsingException("An error occurred parsing Vector value.");
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