/**
 * @file PathPermissionException.h
 */
#if !defined(_PATH_PATHPERMISSIONEXCEPTION_H_)
#define _PATH_PATHPERMISSIONEXCEPTION_H_

#include <path/PathException.h>
namespace path {
/**
 * @class PathPermissionException path/PathPermissionException.h
 * An operation failed because of pathpermissionexceptions.
 */
class PathPermissionException : public PathException
{

public:
    /// Default constructor
    PathPermissionException();
    /// Include path and errno
    PathPermissionException (const std::string &path, int err);
    /// Destructor
    virtual ~PathPermissionException() throw();

};
}
#endif // !defined(_PATH_PATHPERMISSIONEXCEPTION_H_)
