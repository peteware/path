/**
 * @file RulesWin32.cpp
 */
#include <path/RulesWin32.h>
#include <path/Canonical.h>
#include <path/Path.h>

namespace path {
/**
 * Provides a default instance of RulesWin32
 */
RulesWin32 RulesWin32::rules;

RulesWin32::RulesWin32()
    : RulesBase('\\')
{
}

RulesWin32::~RulesWin32()
{
}

/**
 * Converts Path into a 'canonical' form.  This allows a Path to
 * be converted from one RulesBase to another RulesBase.
 *
 * @param path A string to parse into a path.
 */
Canonical RulesWin32::canonical(const std::string &path) const
{
    Canonical canon;

    if (path.size() >= 2 && path[1] == ':')
    {
        canon = RulesBase::canonical(path.substr(2, path.size() - 2));
        canon.setDrive(path.substr(0,1));
        canon.setAbs(true);
    }
    else
    {
        canon = RulesBase::canonical(path);
    }
    return canon;
}

/**
 * Return a string properly quoted with any system special
 * components replaces.  For example, RulesUri would replace
 * spaces with %040.  Only single path components should be
 * passed.  For example, passing 'a/b' to RulesUnix would return
 * 'a_b'.
 *
 * @param subdir The string to remove any '\' characters
 * @return the quoted string
 */
bool RulesWin32::quote(const std::string & path, std::string *dest) const
{
    if (dest)
        *dest = path;
    return false;
}

bool RulesWin32::unquote(const std::string & subdir, std::string *dest) const
{
    if (dest)
        *dest = subdir;
    return false;
}

/**
 * Shortcut for handling a Win32 style path
 *
 * Useful for creating a path from a string such as:
 * @code
 * Path     p(Win32Path("C:\\a\\b\\c"));
 * @endcode
 *
 * This results in a path, p, that uses the default rules for
 * names but you can specify it as a string using Win32
 * style.  Note that the "\\" is for C++ as a backslash
 * is a special character to the compiler.
 *
 * Note that this declared in <path/Path.h> even though
 * it is implemented in RulesWin32.cpp.  I did this so
 * people could use the Path() constructor easily.
 *
 * @sa UnixPath(),  URLPath()
 *
 * @param path A string with a Windows/DOS style path
 * @return A Canonical object representing that path
 */
path::Canonical Win32Path(const std::string &path)
{
    return path::RulesWin32::rules.canonical(path);
}
}
