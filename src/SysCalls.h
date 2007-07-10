/**  
 * @file SysCalls.h
 *
 * Implementation of the Class SysCalls
 *
 * Created on:      11-May-2007 5:09:32 PM
 * Original author: Pete Ware
 */
#if !defined(EA_9DFD253C_57CC_4b8b_AC60_205874CCB105__INCLUDED_)
#define EA_9DFD253C_57CC_4b8b_AC60_205874CCB105__INCLUDED_

#include <string>
// Forward declarations
class NodeInfo;

/**
 * Implmeents the basic set of system calls to create, remote and traverse
 * directorys.
 */
class SysCalls
{

public:
	SysCalls();
	virtual ~SysCalls();

	void mkdir(const std::string & dir, int mode) const;
	virtual void rmdir(const std::string & dir) const;
	virtual NodeInfo * stat(const std::string & path) const;

};
#endif // !defined(EA_9DFD253C_57CC_4b8b_AC60_205874CCB105__INCLUDED_)
