/**
 * @file FileStream.cpp
 *
 * Implementation of the Class FileStream
 *  Created on:      11-May-2007 5:09:30 PM
 *  Original author: Pete Ware
 */

#include <path/FileStream.h>

namespace path 
{
    FileStream::FileStream(const Path &p)
	: Node(p)
    {
    }
    
    FileStream::~FileStream()
    {
    }
}