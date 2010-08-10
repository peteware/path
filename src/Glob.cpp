#include <path/Glob.h>

#include <vector>

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
    union Chars
    {
        char        m_one;
        char        m_range[2];
        char *      m_list;
    };
    struct Transition
    {
        Transition();
        ~Transition();
        bool match (char ch) const
        {
            switch (m_type)
            {
            case CHAR_CLASS_ANY:
                return true;
            case CHAR_CLASS_ONE:
                return m_input.m_one == ch;
            case CHAR_CLASS_RANGE:
                return m_input.m_range[0] <= ch && m_input.m_range[1] >= ch;
            case CHAR_CLASS_LIST:
                for(const char *p = m_input.m_list; *p; ++p)
                {
                    if (*p == ch)
                        return true;
                }
                return false;
            }
            return false;
        }
        int             m_next;
        CharClass       m_type;
        Chars           m_input;
    };
    typedef std::vector<Transition>     Transitions;
    struct State
    {
        State();
        ~State();
        int             m_fail;
        Transitions     m_trans;
    };
    typedef std::vector<State>          States;

    States      m_states;
};

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
    : m_pattern (copy.m_pattern),
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

bool Glob::compile()
{
    if (m_compiled)
        return true;
    return true;
}

bool Glob::match (const std::string &word)
{
    compile();
    if (!m_compiled || m_compiled->m_states.empty())
        return false;

    Pattern::State *state  = &m_compiled->m_states[0];
    for (std::string::const_iterator iter = word.begin();
         iter != word.end(); ++iter)
    {
        if (!state)
            return false;
        for (Pattern::Transitions::const_iterator t = state->m_trans.begin();
             t != state->m_trans.end(); ++t)
        {
            if (t->match (*iter))
            {
                state = &m_compiled->m_states[t->m_next];
                break;
            }
        }
    }
    return true;
}

Glob::Pattern::Transition::Transition()
    : m_next (-1),
      m_type (CHAR_CLASS_ONE)
{
    m_input.m_one = '\0';
}

Glob::Pattern::Transition::~Transition()
{
    if (m_type == CHAR_CLASS_LIST)
        delete [] m_input.m_list;
}

Glob::Pattern::State::State()
    : m_fail (-1),
      m_trans()
{
}


Glob::Pattern::State::~State()
{
}

}
