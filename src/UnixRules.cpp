/**
 * @file UnixRules.cpp
 *
 * Implementation of the Class UnixRules
 *  Created on:      11-May-2007 5:09:33 PM
 *  Original author: Pete Ware
 */
#include <path/UnixRules.h>
#include <path/Cannonical.h>
#include <path/Path.h>

UnixRules	UnixRules::rules;

UnixRules::UnixRules()
	: PathRules('/')
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
	return PathRules::cannonical(path);
}

/**
 * Return a string properly quoted with any system special components replaces.
 * For example, UriRules would replace spaces with %040.  Only single path
 * components should be passed.  For example, passing 'a/b' to UnixRules would
 * return 'a_b'.
 */
std::string UnixRules::quote(const std::string & subdir) const
{
	return subdir;
}

/**
 * Convert a Unix style path into the cannonical representation
 *
 * This is a good way to create a path that is compatible with
 * the local operating system but still have independent paths.
 * @code
 * Path p (UnixRules::cannon("/a/b/c");
 * @endcode
 *
 * @param path The Unix style path to convert.
 */
Cannonical UnixRules::cannon(const std::string &path)
{
    return UnixRules::rules.cannonical(path);
}

/**
 * Shortcut for handling a Unix style path
 *
 * Useful for creating a path from a string such as:
 * @code
 * Path     p(UnixPath("/a/b/c"));
 * @endcode
 * This results in a path, p, that uses the default rules for
 * names but you can specify it as a string.
 *
 * Note that this declared in <path/Path.h> even though
 * it is implemented in UnixRules.cpp.  I did this so
 * people could use the Path() constructor easily.
 *
 * @sa Win32Path(),  URLPath()
 *
 * @param path A string with a Unix style path
 * @return A Cannonical object representing that path
 */
Cannonical UnixPath(const std::string &path)
{
    return UnixRules::rules.cannonical(path);
}