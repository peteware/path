#ifndef _PATH_SYSUNIXBASE_H_
#define _PATH_SYSUNIXBASE_H_
/*
 *  SysUnixBase.h
 *  path
 *
 *  Created by Peter Ware on 4/2/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

#include <path/SysCalls.h>

class SysUnixBase: public SysCalls
{
public:
	SysUnixBase();
	virtual ~SysUnixBase();
    
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
    /// Return if the path exists.
    virtual bool exists(const std::string &path) const;
    /// Return the current working directory
    virtual std::string getcwd() const;
};
#endif /* _PATH_SYSUNIXBASE_H_ */