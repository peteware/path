/**  
 * @file BadPath.h
 *
 * Implementation of the Class BadPath
 *
 * Created on:      11-May-2007 5:09:29 PM
 * Original author: Pete Ware
 */
#if !defined(_PATH_BADPATH_H_)
#define _PATH_BADPATH_H_

#include <path/PathException.h>

namespace path
{
    class BadPath : public PathException
    {
    public:
        BadPath();
        virtual ~BadPath() throw();
        
    };
}
#endif // !defined(_PATH_BADPATH_H_)
