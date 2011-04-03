/*
 * @file PathLookup.cpp
 */

#include <path/PathLookup.h>

#include <algorithm>
#include <iterator>

namespace path {

PathLookup::PathLookup()
    : m_pathList()
{
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

Path PathLookup::find (const std::string &path)
{
    return Path();
}
}
