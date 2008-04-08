/**
 * @file Unimplemented.cpp
 *
 * Implementation of the Class Unimplemented
 *  Created on:      11-May-2007 5:09:33 PM
 *  Original author: Pete Ware
 */
#include <path/Unimplemented.h>


Unimplemented::Unimplemented(const std::string &operation)
    : exception(),
      m_what(operation)
{
}

Unimplemented::~Unimplemented() throw()
{

}

const char* Unimplemented::what() const throw()
{
	return m_what.c_str();
}
