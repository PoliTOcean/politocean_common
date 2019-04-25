
namespace Politocean {


class exception : public std::exception {
public:
    /// returns the explanatory string
    const char* what() const noexcept override
    {
        return m.what();
    }

    exception(const char* what_arg) : std::exception(), m(what_arg) {}

private:
    /// an exception object as storage for error messages
    std::runtime_error m;
};



class mqttException : public exception {
public:
    mqttException(const char* what_arg) : exception(what_arg) {}
};


}
