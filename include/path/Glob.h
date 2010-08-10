#ifndef _PATH_GLOB_H_
#define _PATH_GLOB_H_

#include <string>

namespace path {
/**
 * Implements csh style pattern matching using
 * the characters '*','?', '[]', '{}' and '^'.  It treats
 * '~' at the start as a regular character.  Examples:
 * - *.C
 * - *.[ch]
 * - test.{c,cpp,h}
 * - test.?
 * - *[0-9].cpp
 * - *[^0-9].cpp
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
    /// Compile pattern (done automatically)
    bool compile();
    /// Compare against pattern
    bool match (const std::string &word);
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
