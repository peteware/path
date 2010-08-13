/**
 * @file PathPermissionException.cpp
 *
 * Implementation of the Class PathPermissionException
 */
#include <path/PathPermissionException.h>

namespace path {

PathPermissionException::PathPermissionException()
    : PathException()
{
}

PathPermissionException::PathPermissionException(const std::string &path, int err)
    : PathException (path,err)
{
}

PathPermissionException::~PathPermissionException() throw()
{

}
}
