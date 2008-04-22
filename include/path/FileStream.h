/**  
 * @file FileStream.h
 *
 * Implementation of the Class FileStream
 *
 * Created on:      11-May-2007 5:09:30 PM
 * Original author: Pete Ware
 */
#if !defined(_PATH_FILESTREAM_H_)
#define _PATH_FILESTREAM_H_

#include <path/Node.h>
#include <fstream>

namespace path 
{
    class FileStream : public Node, public std::fstream
    {
        
    public:
        FileStream(const Path &p, std::ios_base::openmode mode);
        virtual ~FileStream();
        
    };
}
#endif // !defined(_PATH_FILESTREAM_H_)
