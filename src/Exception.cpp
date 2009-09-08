/**
 *  @file Exception.cpp
 *
 * Implementation of class Exception
 */

#include <path/Exception.h>

namespace path {
    
    Exception::Exception ()
    {
    }
    
    Exception::Exception(const std::string &message)
        : m_message(message)
    {
    }
    
    Exception::~Exception() throw()
    {
    }
    
    const char *Exception::what() const throw()
    {
        return m_message.c_str();
    }
}
