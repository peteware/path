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

PathRules::PathRules()
{
}

PathRules::~PathRules()
{
}

/**
 * Converts Path into a 'canonical' form.  This allows a Path to be converted from
 * one PathRules to another PathRules.
 */
Cannonical PathRules::cannonical(const Path &path) const
{
	return Cannonical();
}

/**
 * Converts the canonical representation of a path to a form used by the rules.
 * 
 * Any special characters are converted to a safe form.  For example, in UnixRules,
 * a '/' is converted to '|' (or whatever).
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
std::string PathRules::quote(const std::string & path) const
{
	return std::string();
}