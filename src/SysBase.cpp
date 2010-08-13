/**
 * @file SysBase.cpp
 */
#include <path/SysBase.h>
#include <path/Unimplemented.h>
#include <path/NodeInfo.h>


namespace path {

SysBase::SysBase()
    : m_env(0)
{
}

SysBase::~SysBase()
{
    delete m_env;
}

const RulesBase *SysBase::rules() const
{
    throw Unimplemented("SysBase::rules");
}
void SysBase::mkdir(const std::string & dir, int mode) const
{
    throw Unimplemented("SysBase::mkdir");
}

void SysBase::rmdir(const std::string & dir) const
{
    throw Unimplemented("SysBase::rmdir");
}

void SysBase::touch(const std::string &file, int mode) const
{
    throw Unimplemented("SysBase::touch");
}

void SysBase::remove(const std::string &file) const
{
    throw Unimplemented("SysBase::remove");
}

Strings SysBase::listdir(const std::string &path) const
{
    throw Unimplemented("SysBase::listdir");
}

/**
 * Gets the basic information about a file and returns
 * the a new NodeInfo object.
 *
 * @param path The path to look for
 * @return Newly created NodeInfo object.
 */
NodeInfo * SysBase::stat(const std::string & path) const
{
    throw Unimplemented("SysBase::stat");
}

bool SysBase::exists(const std::string &path) const
{
    throw Unimplemented("SysBase::exists");
}

std::string SysBase::getcwd() const
{
    throw Unimplemented("SysBase::getcwd");
}

StringMap& SysBase::env() const
{
    throw Unimplemented("Syscalls::env");
}
}
