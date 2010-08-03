/**
 * @file SysCalls.h
 */
#if !defined(_PATH_SYSCALLS_H_)
#define _PATH_SYSCALLS_H_

#include <path/Strings.h>
#include <string>
#include <vector>

namespace path {
// Forward declarations
class NodeInfo;
class SysCalls;
class PathRules;

/**
 * This is the object you should reference for making all System
 * calls.  On a given OS this gets initialized at compile time by
 * exactly one of the classes derived from SysCalls.
 *
 * Examples of other classes derived from SysCalls are:
 * SysWin32, SysUnixBase, SysMacOS, etc.
 */
extern SysCalls &System;

/**
 * @class SysCalls path/SysCalls.h
 * Implements the basic set of system calls to create, remove and traverse
 * directories.
 *
 * These all take std::string as an argument and not a Path -- the
 * intention is these are pretty low level calls and should
 * use not be dependent on Path.
 *
 * Here are some ways to use these in a system independent way:
 *
 * @code
 * Path   p;
 * // ...
 * if (!System.exists (p.path())
 * {
 *   std::cerr << "Creating file " << p.str() << std::endl;
 *   System.touch (p.path());
 * }
 * @endcode
 */
class SysCalls
{

public:
    SysCalls();
    virtual ~SysCalls();

    /// Return the default path rules used by this system
    virtual const PathRules *rules() const;
    /// Create a Directory
    virtual void mkdir(const std::string & dir, int mode = 0777) const;
    /// Remove a directory
    virtual void rmdir(const std::string & dir) const;
    /// Create empty file or if it exists update modified time
    virtual void touch(const std::string & file, int mode = 0777) const;
    /// Remove a file
    virtual void remove(const std::string &file) const;
    /// Return a vector with directory contents
    virtual Strings listdir(const std::string &dir) const;
    /// Return info about a file or directory
    virtual NodeInfo * stat(const std::string & path) const;
    /// Return if the path exists.
    virtual bool exists(const std::string &path) const;
    /// Return the current working directory
    virtual std::string getcwd() const;
    /// Return a map of environment variables
    virtual StringMap &env() const;
protected:
    mutable StringMap *m_env;   ///< Map from environment variable
};
}
#endif // !defined(_PATH_SYSCALLS_H_)
