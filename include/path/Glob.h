#ifndef _PATH_GLOB_H_
#define _PATH_GLOB_H_

#include <string>

namespace path {
    /**
     * Implements csh style pattern matching.
     */
    class Glob
    {
    public:
        /// Construct with a shell pattern
        Glob (const std::string &pattern);
        /// Copy constructor
        Glob (const Glob &copy);
        /// Destructor
        ~Glob();
    private:
        /// Implements state for pattern matching
        struct Pattern;
        /// The original pattern
        std::string     m_pattern;
        /// The pattern turned into a FSA
        Pattern *       m_compiled;
        
        
    };
}

#endif /* _PATH_GLOB_H_ */
