/**
 * @file SysCalls.cpp
 *
 * Implementation of the Class SysCalls
 *  Created on:      11-May-2007 5:09:33 PM
 *  Original author: Pete Ware
 */
#include <path/SysCalls.h>
#include <path/Unimplemented.h>

#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/param.h>

SysCalls::SysCalls()
{
}

SysCalls::~SysCalls()
{
}

void SysCalls::mkdir(const std::string & dir, int mode) const
{
    int status = ::mkdir(dir.c_str(), mode);
    if (status < 0)
        throw PathException(dir, errno);
}

void SysCalls::rmdir(const std::string & dir) const
{
    int status = ::rmdir(dir.c_str());
    if (status < 0)
        throw PathException(dir, errno);
}

void SysCalls::touch(const std::string &file) const
{
    int fd = ::open(file.c_str(), O_WRONLY|O_CREAT, 0777);
    if (fd < 0)
        throw PathException(file, errno);
    (void) ::close(fd);
}

void SysCalls::remove(const std::string &file) const
{
    int status = ::unlink(file.c_str());
    if (status < 0)
        throw PathException(file, errno);
}

Strings SysCalls::listdir(const std::string &path) const
{
	Strings	dirs;

	DIR *dir = opendir(path.c_str());
	if (!dir)
		return dirs;

	struct dirent	*entry_ptr;
	struct dirent	entry;
	while (readdir_r(dir, &entry, &entry_ptr) == 0) 
	{
		if (!entry_ptr)
			break;
#ifdef notdef
		if ((entry.d_namlen == 1 || entry.d_namlen == 2) &&
			(strcmp(entry.d_name, ".") == 0 || strcmp(entry.d_name, "..") == 0))
			continue;
#endif
		if (strcmp(entry.d_name, ".") == 0 || strcmp(entry.d_name, "..") == 0)
			continue;
		dirs.push_back(entry.d_name);
	}
	closedir(dir);
	return dirs;
}

NodeInfo * SysCalls::stat(const std::string & path) const 
{
	return NULL;
}

std::string SysCalls::getcwd() const
{
    char        buf[MAXPATHLEN];
    
    ::getcwd(buf, sizeof(buf));
    return std::string(buf);
}
