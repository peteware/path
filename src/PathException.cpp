/**
 * @file PathException.cpp
 *
 * Implementation of the Class PathException
 *  Created on:      11-May-2007 5:09:32 PM
 *  Original author: Pete Ware
 */

#include <path/PathException.h>

PathException::PathException()
	: std::exception(),
	  m_filename(),
	  m_errno(0)
{
}

PathException::PathException(const std::string &filename, int errno)
	: std::exception(),
	  m_filename(filename),
	  m_errno(errno)
{
}





PathException::~PathException() throw()
{

}


/**
 * Return the operating system related error number.
 */
int PathException::err() const
{
	return 0;
}


/**
 * Returns filename associated with the error.
 * 
 * This should be set to the actual operating systems underlying filename so any
 * error messages are as accurate as possible.
 */
std::string PathException::filename() const
{
	return std::string();
}


/**
 * Returns strerror() + filename as a message.
 */
const char* PathException::what() const throw()
{
	return  NULL;
}
