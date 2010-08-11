/**
 * @file BadPath.cpp
 *
 * Implementation of the Class BadPath
 */
#include <path/BadPath.h>

namespace path {

BadPath::BadPath()
    : PathException()
{
}

BadPath::BadPath(const std::string &path, int err)
    : PathException (path, err)
{
}

BadPath::~BadPath() throw()
{
}

}
