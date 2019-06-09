#ifndef COMPONENT_T_HPP
#define COMPONENT_T_HPP

#include <iostream>

namespace Politocean
{
    enum class component_t
    {
        POWER,
        SHOULDER,
        WRIST,
        HEAD,
        JOYSTICK,

        First=POWER,
        Last=JOYSTICK
    };

    inline component_t operator++ (component_t &s) { return s = (component_t)(((int)(s) +1)); }
    inline component_t operator* (component_t &s) { return s; }
    inline component_t begin(component_t r) { return component_t::First; }
    inline component_t end(component_t r) { component_t l = component_t::Last; return ++l; }

    inline std::ostream& operator<<(std::ostream& os, component_t& obj)
    {
        switch (obj)
        {
            case component_t::POWER:
                os << "POWER";
                break;

            case component_t::SHOULDER:
                os << "SHOULDER";
                break;

            case component_t::WRIST:
                os << "WRIST";
                break;

            case component_t::HEAD:
                os << "HEAD";
                break;

            case component_t::JOYSTICK:
                os << "JOYSTICK";
                break;

            default: break;
        }

        return os;
    }

    inline std::ostream& operator<<(std::ostream& os, const component_t& obj)
    {
        switch (obj)
        {
            case component_t::POWER:
                os << "POWER";
                break;

            case component_t::SHOULDER:
                os << "SHOULDER";
                break;

            case component_t::WRIST:
                os << "WRIST";
                break;

            case component_t::HEAD:
                os << "HEAD";
                break;

            case component_t::JOYSTICK:
                os << "JOYSTICK";
                break;

            default: break;
        }

        return os;
    }
}

#endif // COMPONENT_T_HPP