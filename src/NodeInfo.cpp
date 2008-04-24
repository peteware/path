/**
 * @file NodeInfo.cpp
 */
#include <path/NodeInfo.h>

namespace path 
{
    NodeInfo::NodeInfo()
    : m_size(0),
    m_type(OTHER)
    {
    }
    
    NodeInfo::~NodeInfo()
    {
    }
    
    NodeInfo &NodeInfo::setSize(off_t size)
    {
        m_size = size;
        return *this;
    }
    
    off_t NodeInfo::size() const
    {
        return m_size;
    }
    
    NodeInfo &NodeInfo::setType(NodeInfo::Type type)
    {
        m_type = type;
        return *this;
    }
    
    NodeInfo::Type NodeInfo::type() const
    {
        return m_type;
    }
    
    bool NodeInfo::isFile() const
    {
        return m_type == NodeInfo::FILE || m_type == NodeInfo::SYMLINK;
    }
    
    bool NodeInfo::isDir() const
    {
        return m_type == NodeInfo::DIRECTORY;
    }
}
