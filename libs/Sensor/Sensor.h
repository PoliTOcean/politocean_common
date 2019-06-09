/**
 * @author: pettinz
 */

#ifndef SENSOR_H
#define SENSOR_H

#include <iostream>

#include <Reflectable.hpp>
#include "include/sensor_t.h"
#include <json.hpp>

using namespace Reflectable;

namespace Politocean {

template <class T>
class Sensor : public Reflectable::IReflectable {
    sensor_t type_;
    T value_;

public:
    static Sensor parse(const std::string& stringified)
    {
        sensor_t type;
        T value;

        try
        {
            auto j_map = nlohmann::json::parse(stringified);

            type    = j_map["type"];
            value   = j_map["value"];
        }
        catch(const std::exception& e)
        {
            throw ReflectableParsingException("An error occurred parsing sensor.");
        }

        return Sensor(type, value);
    }

    std::string stringify() override
    {
        nlohmann::json j_map;
        j_map["type"] = type_;
        j_map["value"] = value_;

        return j_map.dump();
    }

    Sensor(sensor_t type, T value) : type_(type), value_(value) {}

    void setValue(T value) { value_ = value; }
    T getValue() { return value_; }
    sensor_t getType();

    /*
     * Overloading the operator << to properly print a sensor object
     */
    friend std::ostream& operator<< (std::ostream& os, const Sensor& s) {
        switch (s.type_) {
            case sensor_t::ROLL:
                os << "ROLL";
                break;
            case sensor_t::PITCH:
                os << "PITCH";
                break;
            case sensor_t::TEMPERATURE_INT:
                os << "INTERNAL TEMPERATURE";
                break;
            case sensor_t::TEMPERATURE_PWR:
                os << "12V POWER TEMPERATURE";
                break;
            case sensor_t::PRESSURE:
                os << "PRESSURE";
                break;
        }
        os << ": " << static_cast<unsigned>(s.value_);

        return os;
    }

};

}

#endif //SENSOR_H
