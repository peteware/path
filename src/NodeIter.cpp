/**
 * @file NodeIter.cpp
 */
#include <path/NodeIter.h>
#include <path/Node.h>
#include <path/SysCalls.h>

#include <iterator>

namespace path {
    /**
     * Create a default iterator.  This corresponds to the
     * end() iterator.
     */
    NodeIter::NodeIter()
	: m_parent(0),
    m_nodeList(),
    m_current(-1),
    m_recursive(false)
    {
    }
    
    /**
     * @param copy The NodeIter to copy
     */
    NodeIter::NodeIter(const NodeIter &copy)
    : m_parent(copy.m_parent),
    m_nodeList(),
    m_current(copy.m_current),
    m_recursive(copy.m_recursive)
    {
        for (std::vector<Path *>::const_iterator iter = copy.m_nodeList.begin();
             iter != copy.m_nodeList.end(); ++iter)
        {
            m_nodeList.push_back(new Path(**iter));
        }
    }

    /**
     * Makes iterator return all Nodes within a directory.
     *
     * @param node The Node this is going to iterate through
     */
    NodeIter::NodeIter(const Path &node)
	: m_parent(&node),
    m_nodeList(),
    m_current(0),
    m_recursive(false)
    {
        addNodes(m_parent);
        if (size() == 0)
            m_current = -1;
    }
    
    /**
     * Makes iterator return all Nodes within a directory.
     *
     * Not yet implemented, just iterates through all
     *
     * @param node The Node this is going to interate through
     * @param pattern Pattern to match (shell or regular expression)
     * @param regexp This is a regular expression, not a shell pattern
     */
    NodeIter::NodeIter(const Path &node, const std::string & pattern, bool regexp)
	: m_parent(&node),
    m_nodeList(),
    m_current(0),
    m_recursive(false)
    {
        addNodes(m_parent);
        if (size() == 0)
            m_current = -1;
    }

    /**
     * Delete all items in m_nodeList
     */
    NodeIter::~NodeIter()
    {
        for(std::vector<Path *>::iterator iter = m_nodeList.begin();
            iter != m_nodeList.end(); ++iter)
            delete *iter;
        m_nodeList.clear();
    }

    /**
     * @param op2 Right hand side
     * @return A reference to this object
     */
    NodeIter &NodeIter::operator=(const NodeIter &op2)
    {
        if (this == &op2)
            return *this;
        m_parent = op2.m_parent;
        m_current = op2.m_current;
        for(std::vector<Path *>::iterator iter = m_nodeList.begin();
            iter != m_nodeList.end(); ++iter)
            delete *iter;
        m_nodeList.clear();
        for (std::vector<Path *>::const_iterator iter = op2.m_nodeList.begin();
             iter != op2.m_nodeList.end(); ++iter)
        {
            m_nodeList.push_back(new Path(**iter));
        }
        m_recursive = op2.m_recursive;
        return *this;
    }
    
    /**
     * @return current node
     */
    Path * NodeIter::operator->()
    {
        Path *	n = findNode(m_current);
        return n;
    }
    
    /**
     * Return a Node refering to the next item to be examined.
     * 
     * @return an empty Node if there are no more nodes to examine.
     */
    Path &NodeIter::operator*()
    {
        Path *	n = findNode(m_current);
        return *n;
    }
    
    /**
     * Prefix increment moves to the next Node.
     *
     * @return Reference to this NodIter
     */
    NodeIter &NodeIter::operator++()
    {
        if (m_current < 0 || m_current + 1 >= size())
            m_current = - 1;
        else
        {
            ++m_current;
            if (m_recursive) 
            {
                Path *n = findNode(m_current);
                if (n && n->isDir())
                    addNodes(n);
            }
        }
        return *this;
    }
    
    /**
     * Postfix increment.
     *
     * It's much, much better to use the pre-fix increment as
     * this one makes a complete copy of the list of subnodes
     * and other data.
     */
    NodeIter NodeIter::operator++(int)
    {
        NodeIter    iter(*this);
        ++(*this);
        return iter;
    }
    
    /**
     * Compares two iterators to see if they refer to the same Node
     *
     * @param op2 Right hand side comparison
     * @return true if same, false otherwise
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
     *
     * @param op2 Right hand side for comparison
     */
    bool NodeIter::operator!=(const NodeIter & op2) const
    {
        return !(*this == op2);
    }
    
    /**
     * Traverse into each subdirectory.  Usually,
     * you should call this at the begining, such as:
     *
     * @code
     * Node::iterator iter = node.begin().setRecursive();
     * @endcode
     *
     * If you call it after incrementing the iterator it
     * won't scan any of the previous subdirectories.
     * 
     * @return A reference to this object
     */
    NodeIter & NodeIter::setRecursive()
    {
        if (m_recursive)
            return *this;
        m_recursive = true;
        Path *n = findNode(m_current);
        if (n && n->isDir())
            addNodes(n);
        return *this;
    }
    
    /**
     * Return how many files are in this directory
     *
     * @return Number of items
     */
    int NodeIter::size() const
    {
        return static_cast<int>(m_nodeList.size());
    }

    /**
     * @param index First is 0.  
     * @return Node refered by index.
     */
    Path *NodeIter::findNode(int index) const
    {
        if (index < 0 || index >= static_cast<int>(m_nodeList.size()))
            return 0;
        
        return m_nodeList[index];
    }

    /**
     * @param node Add list of subnodes from node
     */
    void NodeIter::addNodes(const Path *node)
    {
        if (!node)
            return;

        Strings	files = System.listdir(node->path());
        std::sort(files.begin(), files.end());
        for (Strings::iterator iter = files.begin(); iter != files.end(); ++iter)
        {
            m_nodeList.push_back(new Path(*node + *iter));
        }
    }
}
