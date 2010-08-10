/**
 * @file SysUnixBase.cpp
 */
#include <path/SysUnixBase.h>
#include <path/PathException.h>
#include <path/NodeInfo.h>
#include <path/UnixRules.h>
#include <path/Unimplemented.h>

#include <errno.h>
#ifdef __APPLE__
#define LINUX
#endif

#ifdef LINUX
#include <dirent.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/param.h>
#endif

extern "C" {
extern char **environ;
}

namespace path {
#ifdef LINUX
SysUnixBase::SysUnixBase    defSysUnixBase;

SysCalls &System = defSysUnixBase;
#endif
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
#ifdef LINUX
    int status = ::mkdir(dir.c_str(), mode);
    if (status < 0)
        throw PathException(dir, errno);
#else
    throw Unimplemented ("SysUnixBase::mkdir");
#endif
}

void SysUnixBase::rmdir(const std::string & dir) const
{
#ifdef LINUX
    int status = ::rmdir(dir.c_str());
    if (status < 0)
        throw PathException(dir, errno);
#else
    throw Unimplemented ("SysUnixBase::rmdir");
#endif
}

void SysUnixBase::touch(const std::string &file, int mode) const
{
#ifdef LINUX
    int fd = ::open(file.c_str(), O_WRONLY|O_CREAT, mode);
    if (fd < 0)
        throw PathException(file, errno);
    (void) ::close(fd);
#else
    throw Unimplemented ("SysUnixBase::touch");
#endif
}

void SysUnixBase::remove(const std::string &file) const
{
#ifdef LINUX
    int status = ::unlink(file.c_str());
    if (status < 0)
        throw PathException(file, errno);
#else
    throw Unimplemented ("SysUnixBase::remove");
#endif
}

Strings SysUnixBase::listdir(const std::string &path) const
{
#ifdef LINUX
    Strings dirs;

    DIR *dir = opendir(path.c_str());
    if (!dir)
        return dirs;

    struct dirent   *entry_ptr;
    struct dirent   entry;
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
#else
    throw Unimplemented ("SysUnixBase::listdir");
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
NodeInfo * SysUnixBase::stat(const std::string & path) const
{
#ifdef LINUX
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
    throw Unimplemented ("SysUnixBase::stat");
#endif
}

bool SysUnixBase::exists(const std::string &path) const
{
#ifdef LINUX
    return (::access(path.c_str(), F_OK) >= 0);
#else
    throw Unimplemented ("SysUnixBase::exists");
#endif
}

std::string SysUnixBase::getcwd() const
{
#ifdef LINUX
    char        buf[MAXPATHLEN];

    ::getcwd(buf, sizeof(buf));
    return std::string(buf);
#else
    throw Unimplemented ("SysUnixBase::getcwd");
#endif
}

StringMap &SysUnixBase::env() const
{
#ifdef LINUX
    if (!m_env)
    {
        m_env = new StringMap();
        for (char **e = environ; *e !=  0; e++)
        {
            char * equalptr = ::index(*e, '=');
            if (equalptr == 0)
                equalptr = *e;
            std::string key (*e, equalptr);
            std::string val (equalptr+1, (*e) + strlen(*e));


            (*m_env)[key] = val;
        }
    }
    return *m_env;
#else
    throw Unimplemented ("SysUnixBase::env");
#endif
}
}
