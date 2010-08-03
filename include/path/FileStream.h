/**
 * @file FileStream.h
 */
#if !defined(_PATH_FILESTREAM_H_)
#define _PATH_FILESTREAM_H_

#include <path/Node.h>
#include <fstream>

namespace path
{
/**
 * @class FileStream path/FileStream.h
 * Implements a Node that supports fstream
 */
class FileStream : public Node, public std::fstream
{

public:
    FileStream(const Path &p, std::ios_base::openmode mode);
    virtual ~FileStream();

};
}
#endif // !defined(_PATH_FILESTREAM_H_)
