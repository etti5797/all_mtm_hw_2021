
#ifndef EXCEPTIONS_H_
#define EXCEPTIONS_H_

#include <iostream>
using std::string;
using std::endl;

namespace mtm
{ 
    class Exception : public std::exception{};
    
    class IllegalArgument : public Exception
    {
        public:
        const char* what() const noexcept override;
    };

    class IllegalCell  : public Exception
    {
        public:
        const char* what() const noexcept override;
    };

    class CellEmpty  : public Exception
    {
        public:
        const char* what() const noexcept override;
    };

    class MoveTooFar : public Exception
    {
        public:
        const char* what() const noexcept override;
    };

    class CellOccupied  : public Exception
    {
        public:
        const char* what() const noexcept override;
    };

    class OutOfRange  : public Exception
    {
        public:
        const char* what() const noexcept override;
    };

    class OutOfAmmo : public Exception
    {
        public:
        const char* what() const noexcept override;
    };

    class IllegalTarget : public Exception
    {
        public:
        const char* what() const noexcept override;
    };
}



#endif