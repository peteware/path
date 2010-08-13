/**
 * @file PathBadException.cpp
 *
 * Implementation of the Class PathBadException
 */
#include <path/PathBadException.h>

namespace path {

PathBadException::PathBadException()
    : PathException()
{
}

PathBadException::PathBadException(const std::string &path, int err)
    : PathException (path, err)
{
}

PathBadException::~PathBadException() throw()
{
}

}
