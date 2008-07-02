/**
 * @file SysCalls.cpp
 */
#include <path/SysCalls.h>
#include <path/Unimplemented.h>
#include <path/NodeInfo.h>


namespace path {
    
    SysCalls::SysCalls()
    : m_env(0)
    {
    }
    
    SysCalls::~SysCalls()
    {
        delete m_env;
    }
    
    const PathRules *SysCalls::rules() const
    {
        throw Unimplemented("SysCalls::rules");
    }
    void SysCalls::mkdir(const std::string & dir, int mode) const
    {
        throw Unimplemented("SysCalls::mkdir");
    }
    
    void SysCalls::rmdir(const std::string & dir) const
    {
        throw Unimplemented("SysCalls::rmdir");
    }
    
    void SysCalls::touch(const std::string &file, int mode) const
    {
        throw Unimplemented("SysCalls::touch");
    }
    
    void SysCalls::remove(const std::string &file) const
    {
        throw Unimplemented("SysCalls::remove");
    }
    
    Strings SysCalls::listdir(const std::string &path) const
    {
        throw Unimplemented("SysCalls::listdir");
    }
    
    /**
     * Gets the basic information about a file and returns
     * the a new NodeInfo object.
     *
     * @param path The path to look for
     * @return Newly created NodeInfo object.
     */
    NodeInfo * SysCalls::stat(const std::string & path) const 
    {
        throw Unimplemented("SysCalls::stat");
    }
    
    bool SysCalls::exists(const std::string &path) const
    {
        throw Unimplemented("SysCalls::exists");
    }

    std::string SysCalls::getcwd() const
    {
        throw Unimplemented("SysCalls::getcwd");
    }
    
    StringMap& SysCalls::env() const
    {
        throw Unimplemented("Syscalls::env");
    }
}
