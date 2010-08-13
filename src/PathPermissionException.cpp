/**
 * @file Permission.cpp
 *
 * Implementation of the Class Permission
 */
#include <path/Permission.h>

namespace path {

Permission::Permission()
    : PathException()
{
}

Permission::Permission(const std::string &path, int err)
    : PathException (path,err)
{
}

Permission::~Permission() throw()
{

}
}
