/**
 * @file FileStream.cpp
 */

#include <path/FileStream.h>

namespace path 
{
    FileStream::FileStream(const Path &p, std::ios_base::openmode mode)
	: Node(p),
    std::fstream(path_c(), mode)
    {
    }
    
    FileStream::~FileStream()
    {
    }
}
