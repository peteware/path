/**
 * @file SubNode.cpp
 */
#include <path/SubNode.h>
#include <path/Node.h>

namespace path 
{
    SubNode::Entry::Entry() : m_name(), m_node(0)
    {
        
    }
    
    SubNode::Entry::Entry(const std::string &name) : m_name(name), m_node(0)
    {
    }
    
    SubNode::Entry::Entry(const Entry&copy)
    {
        m_name = copy.m_name;
        m_node = 0;
    }
    
    SubNode::Entry::Entry &SubNode::Entry::operator=(const SubNode::Entry &op2)
    {
        if (this != &op2)
        {
            m_name = op2.m_name;
            m_node = new Node(*op2.m_node);
        }
        return *this;
    }
}
