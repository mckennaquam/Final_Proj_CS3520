#ifndef EXCEPTIONS_HPP
#define EXCEPTIONS_HPP

#include <exception>
#include <string>

namespace final_proj
{
    // An InvalidUserException to throw whenever there is an exception
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

    // An UnsupportedBehavoir to throw whenever there is unsupported behavior 
    class UnsupportedBehavoir : public std::exception
    {
    public:
        UnsupportedBehavoir(const std::string &msg) : m_msg(msg) {}

        const char *what() const noexcept override
        {
            return m_msg.c_str();
        }

    private:
        std::string m_msg;
    };
}

#endif