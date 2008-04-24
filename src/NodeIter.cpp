/**
 * @file NodeIter.cpp
 */
#include <path/NodeIter.h>
#include <path/Node.h>
#include <path/SysCalls.h>
//#include <path/BadPath.h>

#include <iterator>

namespace path {
    /**
     * Create a default iterator.  This corresponds to the
     * end() iterator.
     */
    NodeIter::NodeIter()
	: m_parent(0),
    m_current(-1)
    {
    }
    
    /**
     * Makes iterator return all Nodes within a directory.
     */
    NodeIter::NodeIter(const Node &node)
	: m_parent(&node),
    m_current(0)
    {
        if (m_parent->subNodeCount() == 0)
            m_current = -1;
    }
    
    /**
     * Makes iterator return all Nodes within a directory.
     */
    NodeIter::NodeIter(const Node &node, const std::string & pattern, bool regexp)
	: m_parent(&node),
    m_current(0)
    {
        if (m_parent->subNodeCount() == 0)
            m_current = -1;
    }
    
    Node * NodeIter::operator->()
    {
        Node *	n = findNode();
        return n;
        
    }
    
    /**
     * Return a Node refering to the next item to be examined.
     * 
     * Returns an empty Node if there are no more nodes to examine.
     */
    Node &NodeIter::operator*()
    {
        Node *	n = findNode();
        return *n;
    }
    
    /**
     * Prefix increment Moves to the next Node in the
     */
    NodeIter &NodeIter::operator++()
    {
        if (m_current >= 0 && m_current + 1 < size())
            ++m_current;
        else
            m_current = -1;
        return *this;
    }
    
    /**
     * Postfix increment
     */
    NodeIter NodeIter::operator++(int)
    {
        NodeIter    iter(*this);
        ++(*this);
        return iter;
    }
    
    /**
     * Compares two iterators to see if they refer to the same Node
     */
    bool NodeIter::operator==(const NodeIter & op2) const
    {
        // Most comparisons are non-end against end() so make sure that is fast.
        if (m_current != op2.m_current)
            return false;
        // obvious case
        if (this == &op2)
            return true;
        if (m_parent == op2.m_parent && m_current == op2.m_current)
            return true;
        // now check for end()
        if (m_current == -1 && op2.m_current == -1)
            return true;
        return false;
    }
    
    /**
     * Compares two iterators to see if they refer to different Nodes
     */
    bool NodeIter::operator!=(const NodeIter & op2) const
    {
        return !(*this == op2);
        
    }
    
    /**
     * Traverse into each subdirectory.
     */
    void NodeIter::setRecursive()
    {
    }
    
    Node *NodeIter::findNode()
    {
        if (!m_parent)
            return 0;
        return m_parent->subNode(m_current);
    }
    
    int NodeIter::size() const
    {
        if (!m_parent)
            return 0;
        return m_parent->subNodeCount();
    }
}
