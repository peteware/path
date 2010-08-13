/**
 * @file BadPathException.h
 */
#if !defined(_PATH_BADPATHEXCEPTION_H_)
#define _PATH_BADPATHEXCEPTION_H_

#include <path/PathException.h>

namespace path
{
/**
 * @class BadPathException path/BadPathException.h
 * Handle faults related to BadPathException's.
 */
class BadPathException : public PathException
{
public:
    BadPathException();
    BadPathException(const std::string &path, int err);
    virtual ~BadPathException() throw();

};
}
#endif // !defined(_PATH_BADPATHEXCEPTION_H_)
