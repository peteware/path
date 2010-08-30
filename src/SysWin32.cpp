/**
 * @file SysWin32.cpp
 */
#include <path/SysWin32.h>
#include <path/PathException.h>
#include <path/NodeInfo.h>
#include <path/RulesWin32.h>
#include <path/Unimplemented.h>

#include <errno.h>

#ifdef __WINNT__
#include <io.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#endif

namespace path {
#ifdef __WINNT__
SysWin32    defSysWin32;

SysBase &System = defSysWin32;
#endif

SysWin32::SysWin32()
    : SysBase()
{
}

SysWin32::~SysWin32()
{
}

/**
 * @return A pointer to the RulesUnix::rules
 */
const RulesBase *SysWin32::rules() const
{
    return &RulesWin32::rules;
}

void SysWin32::mkdir(const std::string & dir, int mode) const
{
#ifdef __WINNT__
    if (::mkdir (dir.c_str()) < 0)
    {
        throw PathException (dir, errno);
    }
#else
    throw Unimplemented ("SysWin32::mkdir");
#endif
}

void SysWin32::rmdir(const std::string & dir) const
{
#ifdef __WINNT__
    if (::rmdir (dir.c_str()) < 0)
    {
        throw PathException (dir, errno);
    }
#else
    throw Unimplemented ("SysWin32::rmdir");
#endif
}

void SysWin32::touch(const std::string &file, int mode) const
{
    throw Unimplemented ("SysWin32::touch");
}

void SysWin32::remove(const std::string &file) const
{
#ifdef __WINNT__
    if (::unlink (file.c_str()) <0)
    {
        throw PathException (file, errno);
    }
#else
    throw Unimplemented ("SysWin32::remove");
#endif
}

Strings SysWin32::listdir(const std::string &path) const
{
#ifdef __WINNT__
    Strings     dirs;
    DIR *dir = ::opendir (path.c_str());
    if (!dir)
        return dirs;
    struct dirent   *entry_ptr;
    struct dirent   entry;
    while ((entry_ptr = ::readdir(dir)) != 0)
    {
        if (entry.d_namlen == 1 && strcmp(entry.d_name, ".") == 0)
            continue;
        if (entry.d_namlen == 2 && strcmp(entry.d_name, "..") == 0)
            continue;
        dirs.push_back(entry.d_name);
    }
    ::closedir(dir);
    return dirs;
#else
    throw Unimplemented ("SysWin32::listdir");
#endif
}

/**
 * Gets the basic information about a file and returns
 * a new NodeInfo object (you must delete it).  Throws
 * a PathException if path cannot be accessed.
 *
 * @param path The path to look for
 * @return Newly created NodeInfo object.
 */
NodeInfo * SysWin32::stat(const std::string & path) const
{
#ifdef __WINNT__
    struct stat     statbuf;
    NodeInfo *node = 0;
    NodeInfo::Type type = NodeInfo::OTHER;

    if (::stat(path.c_str(), &statbuf) < 0)
        throw PathException(path, errno);
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
#else
    throw Unimplemented ("SysWin32::stat");
#endif
}

bool SysWin32::exists(const std::string &path) const
{
    throw Unimplemented ("SysWin32::exists");
}

std::string SysWin32::getcwd() const
{
    throw Unimplemented ("SysWin32::getcwd");
}

StringMap &SysWin32::env() const
{
    throw Unimplemented ("SysWin32::env");
}
}
