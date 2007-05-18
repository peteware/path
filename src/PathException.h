/**  
 * @file PathException.h
 *
 * Implementation of the Class PathException
 *
 * Created on:      11-May-2007 5:09:32 PM
 * Original author: Pete Ware
 */
#if !defined(EA_F1AF4BDA_4C40_41ba_ABD8_1C96702933CD__INCLUDED_)
#define EA_F1AF4BDA_4C40_41ba_ABD8_1C96702933CD__INCLUDED_

#include <string>
#include <exception>

/**
 * Anytime a Node interacts witht he filesystem, there's a chance for something to
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

	~PathException();
	int err() const;
	std::string filename() const;
	virtual const char* what();

};
#endif // !defined(EA_F1AF4BDA_4C40_41ba_ABD8_1C96702933CD__INCLUDED_)
