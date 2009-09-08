/**
 * @file PathRules.cpp
 */
#include <path/PathRules.h>
#include <path/Canonical.h>
#include <path/Path.h>
#include <path/Unimplemented.h>

#include <string>
#include <iostream>

namespace path {
    
    /**
     * @param sep Sepearator charcter within path, for example '/'.
     */
    PathRules::PathRules(char sep)
        : m_sep(sep)
    {
    }
    
    PathRules::~PathRules()
    {
    }
    
    /**
     * Convert the canonical representation into a 
     * suitable string.  No varaiable ($VAR) expansion
     * happens.  Special characters, i.e. path_sep such as
     * '/' are escaped.
     *
     * @param canon The protocol, drive, components to stringify
     * @return The PathRules specific string
     */
    std::string PathRules::str(const Canonical &canon) const
    {
        std::string     p;
        if (!canon.protocol().empty())
        {
            p += canon.protocol() + ":";
            if (!canon.host().empty())
                p += "//" + canon.host() + "/";
        }
        if (!canon.drive().empty())
        {
            p += canon.drive() + ":";
        }
        if (canon.abs())
            p += m_sep;
        bool first = true;
        for (Strings::const_iterator iter = canon.components().begin();
             iter != canon.components().end(); ++iter)
        {
            if (first)
                first = false;
            else
                p += m_sep;
            p += quote(*iter);
        }
        return p;
    }
    
    /**
     * This allows Path to implement it's manipulations without
     * knowing system implementation details.
     *
     * @param path The path to convert to Canonical
     */
    Canonical PathRules::canonical(const std::string &path) const
    {
        Canonical       canon;
        Strings     components;
        bool            first = true;
        
        split(path, m_sep, components);
        Strings::iterator iter = components.begin();
        while (iter != components.end())
        {
            if (iter->empty())
            {
                if (first)
                    canon.setAbs(true);
                iter = components.erase(iter);
            }
            else {
                // The previous erase goes to the next component
                // and a second ++iter in for loop would go beyond
                // the end
                ++iter;
            }
            first = false;
            
        }
        canon.components().swap(components);
        return canon;
    }
    
    /**
     * Return a string properly quoted with any system special components replaces.
     * For example, UriRules would replace spaces with %040.  Only single path
     * components should be passed.  For example, passing 'a/b' to UnixRules would
     * return 'a_b'.
     *
     * See unquote() which does the inverse.
     *
     * @param subdir Element to be quoted
     * @return Element with special characters translated
     */
    std::string PathRules::quote(const std::string & subdir) const
    {
        throw Unimplemented("PathRules::quote()");
    }

    /**
     * Take an already quoted element and return it with things
     * translated back to te original.
     *
     * @param subdir Subdirectory to have any quoted characters unquoted
     */
    std::string PathRules::unquote(const std::string &subdir) const
    {
        throw Unimplemented("PathRules::unquote()");
    }
    
}
