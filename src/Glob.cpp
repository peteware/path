#include <path/Glob.h>

namespace path
{
/**
 * Contains the finite state automata to recognize
 * a shell style file pattern.  This is a structure private to
 * Glob.
 */
struct Glob::Pattern
{
    enum CharClass
    {
        CHAR_CLASS_ANY,
        CHAR_CLASS_ONE,
        CHAR_CLASS_LIST,
        CHAR_CLASS_RANGE
    };
    struct State
    {
        State();
        ~State();
        int         m_next;
        CharClass   m_type;
        char        m_one;
        char        m_last;
        char *      m_List;
    };
}

/**
 * @param pattern The csh-style file pattern
 */
Glob::Glob (const std::string &pattern)
    : m_pattern (pattern),
      m_compiled (0)
{
}

/**
 * @param copy The Glob object to copy
 */
Glob::Glob (const Glob &copy)
    : m_pattern (copy.m_pattern)
      m_compiled (0)
{
}

/**
 * Clean up the m_compiled pattern
 */
Glob::~Glob()
{
    delete m_compiled;
}

}
