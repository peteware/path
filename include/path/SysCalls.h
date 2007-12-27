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

	void mkdir(const std::string & dir, int mode) const;
	virtual void rmdir(const std::string & dir) const;
	virtual std::vector<std::string> listdir(const std::string &dir) const;
	virtual NodeInfo * stat(const std::string & path) const;

};
#endif // !defined(_PATH_SYSCALLS_H_)