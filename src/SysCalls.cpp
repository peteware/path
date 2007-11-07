/**
 * @file SysCalls.cpp
 *
 * Implementation of the Class SysCalls
 *  Created on:      11-May-2007 5:09:33 PM
 *  Original author: Pete Ware
 */
#include <path/SysCalls.h>

#include <sys/types.h>
#include <dirent.h>

SysCalls::SysCalls()
{
}

SysCalls::~SysCalls()
{
}

void SysCalls::mkdir(const std::string & dir, int mode) const
{
}

void SysCalls::rmdir(const std::string & dir) const
{
}

std::vector<std::string> SysCalls::listdir(const std::string &path) const
{
	std::vector<std::string>	dirs;

	DIR *dir = opendir(path.c_str());
	if (!dir)
		return dirs;

	struct dirent	*entry_ptr;
	struct dirent	entry;
	while (readdir_r(dir, &entry, &entry_ptr) == 0) 
	{
		if (!entry_ptr)
			break;
		if ((entry.d_namlen == 1 || entry.d_namlen == 2) &&
			(strcmp(entry.d_name, ".") == 0 || strcmp(entry.d_name, "..") == 0))
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
