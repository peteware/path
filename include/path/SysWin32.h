/**
 * @file SysWin32.h
 */
#ifndef _PATH_SYSWIN32_H_
#define _PATH_SYSWIN32_H_

#include <path/SysCalls.h>

namespace path {
// Forward declarations
class PathRules;

/**
 * @class SysWin32 path/SysWin32.h
 * Implements base functionality for Windows systems
 */
class SysWin32: public SysCalls
{
public:
    SysWin32();
    virtual ~SysWin32();

    /// Return PathRules suitable for Windows
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
    virtual StringMap &env() const;
};
}
#endif /* _PATH_SYSWIN32_H_ */
