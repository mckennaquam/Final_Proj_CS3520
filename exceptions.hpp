#ifndef EXCEPTIONS_HPP
#define EXCEPTIONS_HPP

#include <exception>
#include <string>

namespace final_proj
{

    class InvalidUserInputException : public std::exception
    {
    public:
        InvalidUserInputException(const std::string &msg) : m_msg(msg) {}

        const char *what() const noexcept override
        {
            return m_msg.c_str();
        }

    private:
        std::string m_msg;
    };
}

#endif