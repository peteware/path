/**
 * @file UriRules.cpp
 */
#include <path/UriRules.h>
#include <path/Canonical.h>
//#include <path/Path.h>

namespace path {
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
	 *
	 * @param path A string to parse into a path.
     */
    Canonical UriRules::canonical(const std::string &path) const
    {
        return Canonical();
    }
    
    /**
     * Return a string properly quoted with any system special components replaces.
     * For example, UriRules would replace spaces with %040.  Only single path
     * components should be passed.  For example, passing 'a/b' to UnixRules would
     * return 'a_b'.
	 *
	 * @param subdir The string to remove any '/' characters
	 * @return the quoted string
     */
    std::string UriRules::quote(const std::string & subdir) const
    {
        return std::string();
    }
}
