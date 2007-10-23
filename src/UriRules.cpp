/**
 * @file UriRules.cpp
 *
 * Implementation of the Class UriRules
 *  Created on:      11-May-2007 5:09:33 PM
 *  Original author: Pete Ware
 */
#include "UriRules.h"


UriRules::UriRules()
	: PathRules('/')
{
}

UriRules::~UriRules()
{
}

/**
 * Converts Path into a 'canonical' form.  This allows a Path to be converted from
 * one PathRules to another PathRules.
 */
Cannonical UriRules::canonical(const std::string &path) const
{
	return Cannonical();
}

/**
 * Converts the canonical representation of a path to a form used by the rules.
 * 
 * Any special characters are converted to a safe form.  For example, in UnixRules,
 * a '/' is converted to '|' (or whatever).
 */
Path UriRules::convert(const Cannonical &canonical) const
{
	return Path();
}

/**
 * Return a string properly quoted with any system special components replaces.
 * For example, UriRules would replace spaces with %040.  Only single path
 * components should be passed.  For example, passing 'a/b' to UnixRules would
 * return 'a_b'.
 */
std::string UriRules::quote(const std::string & subdir) const
{
	return std::string();
}
