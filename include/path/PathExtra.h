/**
 * @file PathExtra.h
 */
#ifndef _PATH_PATHEXTRA_H_
#define _PATH_PATHEXTRA_H_

#include <string>

namespace path {
    
    // Forward declarations
    class Path;
    class PathRules;
    class Canonical;
    class NodeInfo;
    
    /**
     * @class PathExtra path/PathExtra.h
     *
     * This exists entirely to make a Path be smaller and simpler to 
     * insure binaryu compatibility.  The typical Path
     * class is just a string.  But we can cache some
     * extra information such as the normalized path
     * or if it is an absolute path.  We create the
     * extra info on the fly as it is needed.
     */
    class PathExtra
    {
    private:
        friend class Path;
        
        /// Default constructor
        PathExtra();
        /// Destructor
        ~PathExtra();
        
        /**
         * The path as set.
         * 
         * This is the uninterpreted string and is the value returned by str().
         */
        mutable std::string *           m_path;
        /// These are the rules we use for this path; may be NULL
        const PathRules *		m_rules;
        /// The path in canonical form; may be NULL
        mutable Canonical *m_canon;
        /// Cached value path converted by path();
        mutable std::string *   m_pathStr;
        mutable NodeInfo * m_cache;
    };
}
#endif /* _PATH_PATHEXTRA_H_ */
