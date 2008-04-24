/**
 * @file Exception.h
 */
#ifndef _PATH_EXCEPTION_H_
#define _PATH_EXCEPTION_H_

#include <string>

namespace path {
    
    /**
     * @class Exception path/Exception.h
     * Base class for all path related exceptions.
     */
    class Exception : public std::exception
    {
    public:
        Exception();
        Exception(const std::string &mesage);
        virtual ~Exception() throw();
        virtual const char *what() const throw();
    protected:
        std::string     m_message;
    };
}
#endif
