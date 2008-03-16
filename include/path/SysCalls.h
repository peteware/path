/**  
 * @file SysCalls.h
 *
 * Implementation of the Class SysCalls
 *
 * Created on:      11-May-2007 5:09:32 PM
 * Original author: Pete Ware
 */
#if !defined(_PATH_SYSCALLS_H_)
#define _PATH_SYSCALLS_H_


#include <path/Strings.h>
#include <string>
#include <vector>

// Forward declarations
class NodeInfo;

/**
 * Implements the basic set of system calls to create, remove and traverse
 * directories.
 */
class SysCalls
{

public:
	SysCalls();
	virtual ~SysCalls();

    /// Create a Directory
	virtual void mkdir(const std::string & dir, int mode = 0777) const;
    /// Remove a directory
	virtual void rmdir(const std::string & dir) const;
    /// Create empty file or if it exists update modified time
    virtual void touch(const std::string & file) const;
    /// Remove a file
    virtual void remove(const std::string &file) const;
    /// Return a vector with directory contents
	virtual Strings listdir(const std::string &dir) const;
    /// Return info about a file or directory
	virtual NodeInfo * stat(const std::string & path) const;
    /// Return the current working directory
    virtual std::string getcwd() const;

};
#endif // !defined(_PATH_SYSCALLS_H_)
