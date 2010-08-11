/**
 * @file SysWin32.cpp
 */
#include <path/SysWin32.h>
#include <path/PathException.h>
#include <path/NodeInfo.h>
#include <path/Win32Rules.h>
#include <path/Unimplemented.h>

#include <errno.h>

namespace path {
#ifdef __WINNT__
SysWin32    defSysWin32;

SysCalls &System = defSysWin32;
#endif

SysWin32::SysWin32()
    : SysCalls()
{
}

SysWin32::~SysWin32()
{
}

/**
 * @return A pointer to the UnixRules::rules
 */
const PathRules *SysWin32::rules() const
{
    return &Win32Rules::rules;
}

void SysWin32::mkdir(const std::string & dir, int mode) const
{
    throw Unimplemented ("SysWin32::mkdir");
}

void SysWin32::rmdir(const std::string & dir) const
{
    throw Unimplemented ("SysWin32::rmdir");
}

void SysWin32::touch(const std::string &file, int mode) const
{
    throw Unimplemented ("SysWin32::touch");
}

void SysWin32::remove(const std::string &file) const
{
    throw Unimplemented ("SysWin32::remove");
}

Strings SysWin32::listdir(const std::string &path) const
{
    throw Unimplemented ("SysWin32::listdir");
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
    throw Unimplemented ("SysWin32::stat");
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
