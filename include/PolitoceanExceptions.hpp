
namespace Politocean {


class exception : public std::exception {
public:
    /// returns the explanatory string
    const char* what() const noexcept override
    {
        return m.what();
    }

    exception(const char* what_arg) : std::exception(), m(what_arg) {}

protected:
    static std::string name(const std::string& ename, int id_)
    {
        return "[Politocean.exception." + ename + "." + std::to_string(id_) + "] ";
    }

private:
    /// an exception object as storage for error messages
    std::runtime_error m;
};



class mqttException : public exception {
public:
    mqttException(const char* what_arg) : exception(what_arg) {}

protected:
    static std::string name(const std::string& ename, int id_)
    {
        return "[Politocean.mqttException." + ename + "." + std::to_string(id_) + "] ";
    }
};


}
