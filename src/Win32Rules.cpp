/**
 * @file Win32Rules.cpp
 *
 * Implementation of the Class Win32Rules
 *  Created on:      11-May-2007 5:09:34 PM
 *  Original author: Pete Ware
 */
#include <path/Win32Rules.h>
#include <path/Cannonical.h>
#include <path/Path.h>

Win32Rules::Win32Rules()
	: PathRules('/')
{
}

Win32Rules::~Win32Rules()
{
}

/**
 * Converts Path into a 'canonical' form.  This allows a Path to be converted from
 * one PathRules to another PathRules.
 */
Cannonical Win32Rules::canonical(const Path &path) const
{
	return Cannonical();
}

/**
 * Converts the canonical representation of a path to a form used by the rules.
 * 
 * Any special characters are converted to a safe form.  For example, in UnixRules,
 * a '/' is converted to '|' (or whatever).
 */
Path Win32Rules::convert(const Cannonical &canonical) const 
{
	return Path();
}


/**
 * Return a string properly quoted with any system special components replaces.
 * For example, UriRules would replace spaces with %040.  Only single path
 * components should be passed.  For example, passing 'a/b' to UnixRules would
 * return 'a_b'.
 */
std::string Win32Rules::quote(const std::string & path) const
{
	return std::string();
}
