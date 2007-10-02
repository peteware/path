/**
 * @file UnixRules.cpp
 *
 * Implementation of the Class UnixRules
 *  Created on:      11-May-2007 5:09:33 PM
 *  Original author: Pete Ware
 */
#include "UnixRules.h"
#include "Cannonical.h"
#include "Path.h"

UnixRules	UnixRules::rules;

UnixRules::UnixRules()
{
}

UnixRules::~UnixRules()
{
}

/**
 * Converts Path into a 'canonical' form.  This allows a Path to be converted from
 * one PathRules to another PathRules.
 */
Cannonical UnixRules::cannonical(const std::string &path) const
{
	return Cannonical();
}

/**
 * Converts the canonical representation of a path to a form used by the rules.
 * 
 * Any special characters are converted to a safe form.  For example, in UnixRules,
 * a '/' is converted to '|' (or whatever).
 */
Path UnixRules::convert(const Cannonical &canonical) const 
{
	return Path();
}

/**
 * Return a string properly quoted with any system special components replaces.
 * For example, UriRules would replace spaces with %040.  Only single path
 * components should be passed.  For example, passing 'a/b' to UnixRules would
 * return 'a_b'.
 */
std::string UnixRules::quote(const std::string & subdir) const
{
	return std::string();
}
