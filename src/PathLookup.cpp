/*
 * @file PathLookup.cpp
 */

#include <path/PathLookup.h>
#include <path/PathIter.h>

#include <algorithm>
#include <iterator>
#include <iostream>

namespace path {

PathLookup::PathLookup()
    : m_pathList()
{
}

PathLookup &
PathLookup::push_back(const Path &path)
{
    m_pathList.push_back(path);
    return *this;
}
    

/**
 * Add new paths to the end of a search list.
 */
void PathLookup::push_back (const Paths &paths)
{
    std::copy (paths.begin(), paths.end(), std::back_insert_iterator<Paths>(m_pathList));
}

/**
 * Add new paths to the front of the search list.
 */
void PathLookup::push_front (const Paths &paths)
{
    // Put paths at the start
    Paths pathList(paths.begin(), paths.end());
    // And previous one after
    std::copy (m_pathList.begin(), m_pathList.end(), std::back_insert_iterator<Paths>(pathList));

    m_pathList = pathList;
}

const Paths &
PathLookup::paths() const
{
    return m_pathList;
}
    
Paths PathLookup::find (const std::string &path)
{
    Paths   results;
    for (Paths::const_iterator dirIter = m_pathList.begin();
         dirIter != m_pathList.end(); ++dirIter)
    {
        const Path &dirPath = *dirIter;
        Path::iterator pathIter = dirPath.begin();
        pathIter.setRecursive();
        while (pathIter != dirPath.end()) 
        {
            const Path &p = *pathIter;
            //std::cout << p << std::endl;
            if (path == p.basename()) 
            {
                results.push_back(p);
            }
            ++pathIter;
        }
    }
    return results;
}
}
