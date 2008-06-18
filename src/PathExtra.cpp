/**
 * @file PathExtra.cpp
 */
#include <path/PathExtra.h>
#include <path/Canonical.h>
#include <path/NodeInfo.h>

namespace path {
    PathExtra::PathExtra()
    : m_path(0),
    m_rules(0),
    m_canon(0),
    m_pathStr(0),
    m_cache(0)
    {
    }
    
    PathExtra::~PathExtra(void)
    {
        delete m_path;
        delete m_canon;
        delete m_pathStr;
        delete m_cache;
    }
}
