/**
 * @file SysUnixBase.cpp
 */
#include <path/SysUnixBase.h>
#include <path/PathException.h>
#include <path/NodeInfo.h>
#include <path/UnixRules.h>

#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/param.h>

SysUnixBase::SysUnixBase    defSysUniBase;

SysCalls &System = defSysUniBase;

SysUnixBase::SysUnixBase()
    : SysCalls()
{
}

SysUnixBase::~SysUnixBase()
{
}

/**
 * @return A pointer to the UnixRules::rules
 */
const PathRules *SysUnixBase::rules() const
{
    return &UnixRules::rules;
}

void SysUnixBase::mkdir(const std::string & dir, int mode) const
{
    int status = ::mkdir(dir.c_str(), mode);
    if (status < 0)
        throw PathException(dir, errno);
}

void SysUnixBase::rmdir(const std::string & dir) const
{
    int status = ::rmdir(dir.c_str());
    if (status < 0)
        throw PathException(dir, errno);
}

void SysUnixBase::touch(const std::string &file) const
{
    int fd = ::open(file.c_str(), O_WRONLY|O_CREAT, 0777);
    if (fd < 0)
        throw PathException(file, errno);
    (void) ::close(fd);
}

void SysUnixBase::remove(const std::string &file) const
{
    int status = ::unlink(file.c_str());
    if (status < 0)
        throw PathException(file, errno);
}

Strings SysUnixBase::listdir(const std::string &path) const
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

/**
 * Gets the basic information about a file and returns
 * the a new NodeInfo object.
 *
 * @param path The path to look for
 * @return Newly created NodeInfo object.
 */
NodeInfo * SysUnixBase::stat(const std::string & path) const 
{
    struct stat     statbuf;
    NodeInfo *node = 0;
    NodeInfo::Type type = NodeInfo::OTHER;
    
    if (::stat(path.c_str(), &statbuf) < 0)
        return node;
    node = new NodeInfo();
    
    node->setSize(statbuf.st_size);
    switch (statbuf.st_mode & S_IFMT) {
        case S_IFDIR:
            type = NodeInfo::DIRECTORY;
            break;
        case S_IFREG:
            type = NodeInfo::FILE;
            break;
        case S_IFLNK:
            type = NodeInfo::SYMLINK;
            break;
        case S_IFCHR:
        case S_IFBLK:
            type = NodeInfo::DEVICE;
            break;
        default:
            type = NodeInfo::OTHER;
            break;
    }
    node->setType(type);
	return node;
}

bool SysUnixBase::exists(const std::string &path) const
{
    return (::access(path.c_str(), F_OK) >= 0);
}

std::string SysUnixBase::getcwd() const
{
    char        buf[MAXPATHLEN];
    
    ::getcwd(buf, sizeof(buf));
    return std::string(buf);
}