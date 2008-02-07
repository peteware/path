/**
 * @file PathRules.cpp
 *
 * Implementation of the Class PathRules
 *  Created on:      11-May-2007 5:09:32 PM
 *  Original author: Pete Ware
 */
#include <path/PathRules.h>
#include <path/Cannonical.h>
#include <path/Path.h>
#include <path/Unimplemented.h>

#include <string>
#include <iostream>

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
Cannonical PathRules::cannonical(const std::string &path) const
{
	Cannonical	cannon;
	std::vector<std::string>	components;
	bool		first = true;
	
	split(path, m_sep, components);
	std::vector<std::string>::iterator iter = components.begin();
	while (iter != components.end())
	{
		if (iter->empty())
		{
			if (first)
				cannon.setAbs(true);
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
	cannon.components().swap(components);
	return cannon;
}

/**
 * Converts the canonical representation of a path to a form used by the rules.
 * 
 * Any special characters are converted to a safe form.  For example,
 * in UnixRules, a '/' is converted to '|' (or whatever).
 */
Path PathRules::convert(const Cannonical &canonical) const 
{
	throw Unimplemented("PathRules::convert()");
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

std::string PathRules::join(const Cannonical &cannon) const
{
    std::string     p;
    if (!cannon.protocol().empty())
    {
        p += cannon.protocol() + ":";
        if (!cannon.host().empty())
            p += "//" + cannon.host() + "/";
    }
    if (cannon.abs())
        p += m_sep;
    bool first = true;
    for (std::vector<std::string>::const_iterator iter = cannon.components().begin();
         iter != cannon.components().end(); ++iter)
    {
        if (first)
            first = false;
        else
            p += m_sep;
        p += *iter;
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
void PathRules::split(const std::string &path, char sep, std::vector<std::string> &subdirs)
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
