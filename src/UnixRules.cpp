/**
 * @file UnixRules.cpp
 *
 * Implementation of the Class UnixRules
 */
#include <path/UnixRules.h>
#include <path/Canonical.h>
#include <path/Path.h>

namespace path {
    UnixRules   UnixRules::rules;
    
    UnixRules::UnixRules()
        : PathRules('/')
    {
    }
    
    UnixRules::~UnixRules()
    {
    }
    
    /**
     * Converts Path into a 'canonical' form.  This allows a Path to be converted from
     * one PathRules to another PathRules.
     *
     * @param path A string to parse into a path.
     */
    Canonical UnixRules::canonical(const std::string &path) const
    {
        return PathRules::canonical(path);
    }
    
    /**
     * Return a string properly quoted with any system special components replaces.
     * For example, UriRules would replace spaces with %040.  Only single path
     * components should be passed.  For example, passing 'a/b' to UnixRules would
     * return 'a_!_b'.
     *
     * @param subdir The string to remove any '/' characters
     * @return the quoted string
     */
    std::string UnixRules::quote(const std::string & subdir) const
    {
        std::string quoted;

        for (std::string::const_iterator iter = subdir.begin();
             iter != subdir.end(); ++iter)
        {
            if (*iter == '/')
            {
                quoted.push_back('_');
                quoted.push_back('!');
                quoted.push_back('_');
            }
            else
            {
                quoted.push_back(*iter);
            }
        }
        return quoted;
    }
    
    std::string UnixRules::unquote(const std::string &subdir) const
    {
        std::string unquoted;
        int state = 0;

        for (std::string::const_iterator iter = subdir.begin();
             iter != subdir.end(); ++iter)
        {
            if (*iter == '_')
            {
                if (state == 0)
                    state = 1;
                else if (state == 1)
                {
                    // only push first '_' since this one his handled in next state
                    // contemplate: '__!_'
                    unquoted.push_back('_');
                }
                else
                {
                    state = 0;
                    unquoted.push_back('/');
                }
            }
            else if (*iter == '!')
            {
                if (state == 1)
                    state = 2;
                else
                {
                    state = 0;
                    unquoted.push_back('_');
                    unquoted.push_back('!');
                }
            }
            else
            {
                if (state >= 1)
                    unquoted.push_back('_');
                if (state >= 2)
                    unquoted.push_back('!');
                state = 0;
                unquoted.push_back(*iter);
            }
        }
        if (state >= 1)
            unquoted.push_back('_');
        if (state >= 2)
            unquoted.push_back('!');
        return unquoted;
    }

    /**
     * Shortcut for handling a Unix style path
     *
     * Useful for creating a path from a string such as:
     * @code
     * Path     p(UnixPath("/a/b/c"));
     * @endcode
     * This results in a path, p, that uses the default rules for
     * names but you can specify it as a string.
     *
     * Note that this declared in <path/Path.h> even though
     * it is implemented in UnixRules.cpp.  I did this so
     * people could use the Path() constructor easily.
     *
     * @sa Win32Path(),  URLPath()
     *
     * @param path A string with a Unix style path
     * @return A Canonical object representing that path
     */
    path::Canonical UnixPath(const std::string &path)
    {
        return path::UnixRules::rules.canonical(path);
    }
}

