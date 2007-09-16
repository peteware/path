/**  
 * @file PathException.h
 *
 * Implementation of the Class PathException
 *
 * Created on:      11-May-2007 5:09:32 PM
 * Original author: Pete Ware
 */
#if !defined(_PATH_PATHEXCEPTION_H_)
#define _PATH_PATHEXCEPTION_H_

#include <string>
#include <exception>

/**
 * Anytime a Node interacts with the filesystem, there's a chance for something to
 * go wrong.  All such exceptions derive from this.
 * 
 * The actual name of the filesystem object is used in the error message.  The
 * value of errno is saved.  what() is set to be the value of strerror() plus the
 * filename.
 */
class PathException : public std::exception
{

public:
	PathException();

	virtual ~PathException() throw();
	int err() const;
	std::string filename() const;
	virtual const char* what();

};
#endif // !defined(_PATH_PATHEXCEPTION_H_)
