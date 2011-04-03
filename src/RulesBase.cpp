/**
 * @file RulesBase.cpp
 */
#include <path/RulesBase.h>
#include <path/Canonical.h>
#include <path/Path.h>
#include <path/Unimplemented.h>

#include <string>
#include <iostream>

namespace path {

/**
 * @param sep Sepearator charcter within path, for example '/'.
 */
RulesBase::RulesBase(char sep)
    : m_sep(sep)
{
}

RulesBase::~RulesBase()
{
}

/**
 * Convert the canonical representation into a
 * suitable string.  No varaiable ($VAR) expansion
 * happens.  Special characters, i.e. path_sep such as
 * '/' are escaped.
 *
 * @param canon The protocol, drive, components to stringify
 * @return The RulesBase specific string
 */
std::string RulesBase::str(const Canonical &canon) const
{
    std::string     pathStr
    ;
    if (!canon.protocol().empty())
    {
        pathStr += canon.protocol() + ":";
        if (!canon.host().empty())
            pathStr += "//" + canon.host() + "/";
    }
    if (!canon.drive().empty())
    {
        pathStr += canon.drive() + ":";
    }
    if (canon.abs())
        pathStr += m_sep;
    bool first = true;
    for (Strings::const_iterator iter = canon.components().begin();
         iter != canon.components().end(); ++iter)
    {
        if (first)
            first = false;
        else
            pathStr += m_sep;
        if (!quote(*iter, 0))
            pathStr += *iter;
        else 
        {
            std::string quoteStr;
            //quote(*iter, &quoteStr);
            pathStr += quoteStr;
        }
    }
    return pathStr;
}

/**
 * This allows Path to implement it's manipulations without
 * knowing system implementation details.
 *
 * @param path The path to convert to Canonical
 * @return Canonical representation of path
 */
Canonical RulesBase::canonical(const std::string &path) const
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
 * For example, RulesUri would replace spaces with %040.  Only single path
 * components should be passed.  For example, passing 'a/b' to RulesUnix would
 * return 'a_!_b'.
 *
 * See unquote() which does the inverse.
 *
 * It is safe to pass the same string as the dest.  The implementations
 * optimize for no quoting and avoid allocating any strings.
 *
 * @param subdir Element to be quoted
 * @param dest Result is placed here
 * @return Element with special characters translated
 */
bool RulesBase::quote(const std::string & subdir, std::string *) const
{
    throw Unimplemented("RulesBase::quote()");
}

/**
 * Take an already quoted element and return it with things
 * translated back to te original.
 *
 * @param subdir Subdirectory to have any quoted characters unquoted
 * @param dest Results are placed here
 * @return true if anything changed, false otherwise
 */
bool RulesBase::unquote(const std::string &subdir, std::string *dest) const
{
    throw Unimplemented("RulesBase::unquote()");
}

}
