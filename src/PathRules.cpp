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
     * This allows Path to implement it's manipulations without
     * knowing system implementation details.
     */
    Canonical PathRules::canonical(const std::string &path) const
    {
        Canonical	canon;
        Strings	components;
        bool		first = true;
        
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
     * Converts the canonical representation of a path to a form used by the rules.
     * 
     * Any special characters are converted to a safe form.  For example,
     * in UnixRules, a '/' is converted to '|' (or whatever).
     */
    Path PathRules::convert(const Canonical &canonical) const 
    {
        return Path(canonical, this);
    }
    
    /**
     * Return a string properly quoted with any system special components replaces.
     * For example, UriRules would replace spaces with %040.  Only single path
     * components should be passed.  For example, passing 'a/b' to UnixRules would
     * return 'a_b'.
     */
    std::string PathRules::quote(const std::string & subdir) const
    {
        throw Unimplemented("PathRules::quote()");
    }
    
    std::string PathRules::add(const Canonical &canon) const
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
     * Calling this with "//abc/d/e//" would return a vector of
     * "", "", "abc", "d", "e", "", ""
     * @param path The string to split
     * @param sep The character to use to split the path
     * @param subdirs vector of strings that each component is push_back()'d on
     */
    void PathRules::split(const std::string &path, char sep, Strings &subdirs)
    {
        std::string::size_type	start = 0;
        std::string::size_type	end = 0;
        
        while (start < path.size() && end != std::string::npos)
        {
            end = path.find_first_of(sep, start);
            subdirs.push_back(path.substr(start, end - start));
            start = end + 1;
        }
    }
}
