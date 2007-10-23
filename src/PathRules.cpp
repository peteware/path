/**
 * @file PathRules.cpp
 *
 * Implementation of the Class PathRules
 *  Created on:      11-May-2007 5:09:32 PM
 *  Original author: Pete Ware
 */
#include "PathRules.h"
#include "Cannonical.h"
#include "Path.h"
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
	
	split(path, m_sep, cannon.components());
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
	return Path();
}

/**
 * Return a string properly quoted with any system special components replaces.
 * For example, UriRules would replace spaces with %040.  Only single path
 * components should be passed.  For example, passing 'a/b' to UnixRules would
 * return 'a_b'.
 */
std::string PathRules::quote(const std::string & subdir) const
{
	return std::string();
}

/**
 * Calling this with "//abc/d/e//" would return a vector of
 * "", "", "abc", "d", "e", "", ""
 * @param path The string to split
 * @param sep The character to use to split the path
 * @param subdirs Vector of strings that each component is push_back()'d on
 */
void PathRules::split(const std::string &path, char sep, std::vector<std::string> &subdirs)
{
	std::cout << "splitting\n";
	std::string::size_type	start = 0;
	std::string::size_type end = 3;

	while (start < path.size())
	{
		end = path.find_first_of(sep, start);
		subdirs.push_back(path.substr(start, end));
		start = ++end;
	}
}
