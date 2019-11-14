#ifndef REFLECTABLE_INTEGER_H
#define REFLECTABLE_INTEGER_H

#include <iostream>
#include <exception>

#include "../Reflectable.hpp"

namespace Politocean
{
namespace Types
{

using namespace Reflectable;

class Integer : public IReflectable
{
    int value_;

public:
    Integer(int value) : value_(value) {}

    static Integer parse(const std::string &stringified)
    {
        int value;
        try
        {
            value = std::stoi(stringified);
        }
        catch (const std::exception &e)
        {
            throw ReflectableParsingException(std::string("An error occurred parsing Integer value: ") + e.what());
        }
        catch (...)
        {
            throw ReflectableParsingException("An error occurred parsing Integer value.");
        }

        return Integer(value);
    }

    static Integer valueOf(int value)
    {
        return Integer(value);
    }

    std::string stringify() override
    {
        return std::to_string(value_);
    }

    int getInt()
    {
        return value_;
    }

    void operator=(const int &i)
    {
        value_ = i;
    }

    friend std::ostream &operator<<(std::ostream &output, const Integer &I)
    {
        output << I.value_;
        return output;
    }

    Integer &operator++() { ++value_; }
    Integer operator++(int)
    {
        Integer I(value_);
        ++value_;

        return I;
    }

    Integer &operator--() { --value_; }
    Integer operator--(int)
    {
        Integer I(value_);
        --value_;

        return I;
    }

    Integer &operator+=(const Integer &rhs) { value_ += rhs.value_; }
    Integer &operator-=(const Integer &rhs) { value_ -= rhs.value_; }

    inline friend bool operator<(const Integer &lhs, const Integer &rhs) { return (lhs.value_ < rhs.value_); }
    inline friend bool operator>(const Integer &lhs, const Integer &rhs) { return rhs < lhs; }
    inline friend bool operator<=(const Integer &lhs, const Integer &rhs) { return !(lhs > rhs); }
    inline friend bool operator>=(const Integer &lhs, const Integer &rhs) { return !(lhs < rhs); }

    inline friend bool operator==(const Integer &lhs, const Integer &rhs) { return (lhs.value_ == rhs.value_); }
    inline friend bool operator!=(const Integer &lhs, const Integer &rhs) { return !(lhs == rhs); }
};

} // namespace Types
} // namespace Politocean

#endif // REFLECTABLE_INTEGER_H