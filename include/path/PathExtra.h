/**
 * @file PathExtra.h
 */
#ifndef _PATH_PATHEXTRA_H_
#define _PATH_PATHEXTRA_H_

#include <string>

namespace path {

// Forward declarations
class Path;
class RulesBase;
class Canonical;
class NodeInfo;

/**
 * @class PathExtra path/PathExtra.h
 *
 * Multiple copies of a Path object share the
 * same underlying data.
 */
class PathExtra
{
public:
    //friend class Path;

    /// Default constructor
    PathExtra();
    /// Destructor
    ~PathExtra();

    /**
     * The path as set.
     *
     * This is the uninterpreted string and is the value returned by str().
     */
    std::string *           m_path;
    /// These are the rules we use for this path; may be NULL
    const RulesBase *               m_rules;
    /// The path in canonical form; may be NULL
    Canonical *m_canon;
    /// Cached value path converted by path();
    std::string *   m_pathStr;
    NodeInfo * m_cache;
};
}
#endif /* _PATH_PATHEXTRA_H_ */
