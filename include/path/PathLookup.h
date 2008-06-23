/**
 * @file PathLookup.h
 */
#ifndef _PATH_PATHLOOKUP_H_
#define _PATH_PATHLOOKUP_H_

#include <path/Path.h>

#include <vector>
#include <map>

namespace path
{
    // Forward declarations
    class Path;

    /**
     * @class PathLookup path/PathLookup.h
     *
     * Makes it easy to search for a file along a path.
     *
     * With a list of directories and a filter, this
     * finds files along that path.  It saves the
     * results so multiple calls don't re-read
     * directories.
     *
     * The order of directories reflect 
     */
    class PathLookup 
    {
    public:
        /// Default constructor
        PathLookup();
        /// Set the lookup paths
        void setPaths(const Paths &paths);
        /// Return the lookup paths
        Paths paths() const;
        /// AddIter()
        /// AddPath()
        /// AddPath+recursive flag?
        //setFilter(func(Path));
        
    private:
        /// Define a struct that contains directory
        /// and 
        /// List of search paths (in order)
        Paths   m_pathList;
    };
}
#endif /* _PATH_PATHLOOKUP_H_ */
