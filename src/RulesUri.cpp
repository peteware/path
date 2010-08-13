/**
 * @file RulesUri.cpp
 */
#include <path/RulesUri.h>
#include <path/Canonical.h>
#include <path/Unimplemented.h>

namespace path {
RulesUri::RulesUri()
    : RulesBase('/')
{
}

RulesUri::~RulesUri()
{
}

/**
 * Converts Path into a 'canonical' form.  This allows a Path to be converted from
 * one RulesBase to another RulesBase.
 *
 * @param path A string to parse into a path.
 */
Canonical RulesUri::canonical(const std::string &path) const
{
    return Canonical();
}

/**
 * Return a string properly quoted with any system special components replaces.
 * For example, RulesUri would replace spaces with %040.  Only single path
 * components should be passed.  For example, passing 'a/b' to RulesUnix would
 * return 'a_b'.
 *
 * @param subdir The string to remove any '/' characters
 * @return the quoted string
 */
bool RulesUri::quote(const std::string & subdir, std::string *dest) const
{
    throw Unimplemented ("RulesUri::quote");
    return false;
}
}
