/**
 * @file Win32Rules.cpp
 */
#include <path/Win32Rules.h>
#include <path/Canonical.h>
#include <path/Path.h>

namespace path {
    /**
     * Provides a default instance of Win32Rules
     */
    Win32Rules Win32Rules::rules;
    
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
    Canonical Win32Rules::canonical(const std::string &path) const
    {
        Canonical canon;
        
        if (path.size() >= 2 && path[1] == ':')
        {
            canon = PathRules::canonical(path.substr(2, path.size() - 2));
            canon.setDrive(path.substr(0,1));
            canon.setAbs(true);
        }
        else
        {
            canon = PathRules::canonical(path);
        }
        return canon;
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

    std::string Win32Rules::unquote(const std::string & subdir) const
    {
        return subdir;
    }
    
    /**
     * Shortcut for handling a Win32 style path
     *
     * Useful for creating a path from a string such as:
     * @code
     * Path     p(Win32Path("C:\\a\\b\\c"));
     * @endcode
     * This results in a path, p, that uses the default rules for
     * names but you can specify it as a string using Win32
     * style.  Note that the "\\" is for C++ as a backslash
     * is a special character to the compiler.
     *
     * Note that this declared in <path/Path.h> even though
     * it is implemented in Win32Rules.cpp.  I did this so
     * people could use the Path() constructor easily.
     *
     * @sa UnixPath(),  URLPath()
     *
     * @param path A string with a Windows/DOS style path
     * @return A Canonical object representing that path
     */
    path::Canonical Win32Path(const std::string &path)
    {
        return path::Win32Rules::rules.canonical(path);
    }
}
