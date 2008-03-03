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
	: PathRules('\\')
{
}

Win32Rules::~Win32Rules()
{
}

/**
 * Converts Path into a 'canonical' form.  This allows a Path to be converted from
 * one PathRules to another PathRules.
 */
Cannonical Win32Rules::cannonical(const std::string &path) const
{
    Cannonical cannon;
    if (path.size() >= 2 && path[1] == ':')
    {
        cannon = PathRules::cannonical(path.substr(2, path.size() - 2));
        cannon.setDrive(path.substr(0,1));
    }
    else
    {
        cannon = PathRules::cannonical(path);
    }
	return cannon;
}

/**
 * Converts the canonical representation of a path to a form used by the rules.
 * 
 * Any special characters are converted to a safe form.  For example, in UnixRules,
 * a '/' is converted to '|' (or whatever).
 */
Path Win32Rules::convert(const Cannonical &cannonical) const 
{
	return Path(cannonical, this);
}


/**
 * Return a string properly quoted with any system special components replaces.
 * For example, UriRules would replace spaces with %040.  Only single path
 * components should be passed.  For example, passing 'a/b' to UnixRules would
 * return 'a_b'.
 */
std::string Win32Rules::quote(const std::string & path) const
{
	return path;
}
