/**
 * @file Permission.h
 */
#if !defined(_PATH_PERMISSION_H_)
#define _PATH_PERMISSION_H_

#include <path/PathException.h>
namespace path {
/**
 * @class Permission path/Permission.h
 * An operation failed because of permissions.
 */
class Permission : public PathException
{

public:
    Permission();
    virtual ~Permission() throw();

};
}
#endif // !defined(_PATH_PERMISSION_H_)
