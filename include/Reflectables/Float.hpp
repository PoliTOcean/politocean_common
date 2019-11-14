#ifndef REFLECTABLE_Float_H
#define REFLECTABLE_Float_H

#include <iostream>
#include <exception>

#include "../Reflectable.hpp"

namespace Politocean
{
namespace Types
{

using namespace Reflectable;

class Float : public IReflectable
{
    float value_;

public:
    Float(float value) : value_(value) {}

    static Float parse(const std::string &stringified)
    {
        float value;
        try
        {
            value = std::stof(stringified);
        }
        catch (const std::exception &e)
        {
            throw ReflectableParsingException(std::string("An error occurred parsing Float value: ") + e.what());
        }
        catch (...)
        {
            throw ReflectableParsingException("An error occurred parsing Float value.");
        }

        return Float(value);
    }

    static Float valueOf(int value)
    {
        return Float(value);
    }

    std::string stringify() override
    {
        return std::to_string(value_);
    }

    int getFloat()
    {
        return value_;
    }

    void operator=(const float &i)
    {
        value_ = i;
    }

    friend std::ostream &operator<<(std::ostream &output, const Float &I)
    {
        output << I.value_;
        return output;
    }

    Float &operator+=(const Float &rhs) { value_ += rhs.value_; }
    Float &operator-=(const Float &rhs) { value_ -= rhs.value_; }

    inline friend bool operator<(const Float &lhs, const Float &rhs) { return (lhs.value_ < rhs.value_); }
    inline friend bool operator>(const Float &lhs, const Float &rhs) { return rhs < lhs; }
    inline friend bool operator<=(const Float &lhs, const Float &rhs) { return !(lhs > rhs); }
    inline friend bool operator>=(const Float &lhs, const Float &rhs) { return !(lhs < rhs); }

    inline friend bool operator==(const Float &lhs, const Float &rhs) { return (lhs.value_ == rhs.value_); }
    inline friend bool operator!=(const Float &lhs, const Float &rhs) { return !(lhs == rhs); }
};

} // namespace Types
} // namespace Politocean

#endif // REFLECTABLE_Float_H