/**
 * @file BadPath.h
 */
#if !defined(_PATH_BADPATH_H_)
#define _PATH_BADPATH_H_

#include <path/PathException.h>

namespace path
{
/**
 * @class BadPath path/BadPath.h
 * Handle faults related to BadPath's.
 */
class BadPath : public PathException
{
public:
    BadPath();
    virtual ~BadPath() throw();

};
}
#endif // !defined(_PATH_BADPATH_H_)
