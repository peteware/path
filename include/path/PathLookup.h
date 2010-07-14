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
 * With a list of directories and a filter, this finds files along
 * that path.  It saves the results so multiple calls don't re-read
 * directories.
 *
 * The order of directories reflect
 */
class PathLookup
{
public:
    /// Default constructor
    PathLookup();
    /// Add lookup paths to end
    void push_back(const Paths &paths);
    /// Add lookup paths to the front
    void push_front (const Paths &paths);
    /// Return a copy of lookup paths
    Paths paths() const;
    /// Clear the list of paths
    void clear();
    Path find (const std::string & path);


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
