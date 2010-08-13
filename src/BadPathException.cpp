/**
 * @file BadPathException.cpp
 *
 * Implementation of the Class BadPathException
 */
#include <path/BadPathException.h>

namespace path {

BadPathException::BadPathException()
    : PathException()
{
}

BadPathException::BadPathException(const std::string &path, int err)
    : PathException (path, err)
{
}

BadPathException::~BadPathException() throw()
{
}

}
