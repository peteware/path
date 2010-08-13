/**
 * @file SysUnixBase.h
 */
#ifndef _PATH_SYSUNIXBASE_H_
#define _PATH_SYSUNIXBASE_H_

#include <path/SysBase.h>

namespace path {
// Forward declarations
class RulesBase;

/**
 * @class SysUnixBase path/SysUnixBase.h
 * Implements base functionality for Unix like systems
 * (Linux, MacOS, Solaris, etc)
 */
class SysUnixBase: public SysBase
{
public:
    SysUnixBase();
    virtual ~SysUnixBase();

    /// Return RulesBase suitable for Unix-like systems
    virtual const RulesBase *rules() const;
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
protected:
    /// Use errno to throw appropriate exception
    void throwException (const std::string &path, int err) const;
};
}
#endif /* _PATH_SYSUNIXBASE_H_ */
