/**
 * @file Unimplemented.cpp
 *
 * Implementation of the Class Unimplemented
 */
#include <path/Unimplemented.h>

namespace path {
    
    Unimplemented::Unimplemented(const std::string &operation)
        : Exception(operation)
    {
    }
    
    Unimplemented::~Unimplemented() throw()
    {
    }
}
