/**
 * @file PathException.cpp
 *
 * Implementation of the Class PathException
 */

#include <path/PathException.h>
#include <stdio.h>

namespace path {
    
    PathException::PathException()
	: Exception(),
    m_filename(),
    m_errno(0)
    {
    }
    
    PathException::PathException(const std::string &filename, int errno)
	: Exception(),
    m_filename(filename),
    m_errno(errno)
    {
        m_message = m_filename + ":" + strerror(m_errno);
    }

	PathException::PathException(const std::string &filename)
		: Exception(),
		m_filename(filename),
		m_errno(errno)
	{
		m_message = m_filename + ":" + strerror(m_errno);
	}
    
    PathException::~PathException() throw()
    {
        
    }
    
    /**
     * Return the operating system related error number.
     */
    int PathException::err() const
    {
        return m_errno;
    }
    
    /**
     * Returns filename associated with the error.
     * 
     * This should be set to the actual operating systems underlying filename so any
     * error messages are as accurate as possible.
     */
    std::string PathException::filename() const
    {
        return m_filename;
    }
}
