/**
 * @file NodeIter.cpp
 */
#include <path/NodeIter.h>
#include <path/Node.h>
#include <path/SysCalls.h>
#include <path/SubNode.h>
//#include <path/BadPath.h>

#include <iterator>

namespace path {
    /**
     * Create a default iterator.  This corresponds to the
     * end() iterator.
     */
    NodeIter::NodeIter()
	: m_parent(0),
    m_current(-1),
    m_nodes(0)

    {
    }
    
    NodeIter::NodeIter(const NodeIter &copy)
    : m_parent(copy.m_parent),
    m_current(copy.m_current),
    m_nodes(0)
    {
        if (copy.m_nodes)
            m_nodes = new SubNode(*copy.m_nodes);
    }

    /**
     * Makes iterator return all Nodes within a directory.
     *
     * @param node The Node this is going to iterate through
     */
    NodeIter::NodeIter(const Node &node)
	: m_parent(&node),
    m_current(0),
    m_nodes(0)

    {
        subNodeCreate();
        if (subNodeCount() == 0)
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
    NodeIter::NodeIter(const Node &node, const std::string & pattern, bool regexp)
	: m_parent(&node),
    m_current(0),
    m_nodes(0)

    {
        subNodeCreate();
        if (subNodeCount() == 0)
            m_current = -1;
    }
    
    NodeIter::~NodeIter()
    {
        delete m_nodes;
    }
    
    NodeIter &NodeIter::operator=(const NodeIter &op2)
    {
        if (this == &op2)
            return *this;
        delete m_nodes;
        m_parent = op2.m_parent;
        m_current = op2.m_current;
        if (op2.m_nodes)
            m_nodes = new SubNode(*op2.m_nodes);
        else
            m_nodes = 0;
        return *this;
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
     * Traverse into each subdirectory.
     */
    void NodeIter::setRecursive()
    {
    }
    
    Node *NodeIter::findNode()
    {
        if (!m_parent)
            return 0;
        return subNode(m_current);
    }
    
    int NodeIter::size() const
    {
        if (!m_parent)
            return 0;
        return subNodeCount();
    }
    /**
     * @param index First is 0.  
     * @return Node refered by index.
     */
    Node *NodeIter::subNode(int index) const
    {
        Node *n = 0;
        
        subNodeCreate();
        if (!m_nodes)
            return 0;
        if (index < 0 || index >= static_cast<int>(m_nodes->m_entries.size()))
            return 0;
        n = m_nodes->m_entries[index].m_node;
        if (!n)
        {
            std::string		name = m_nodes->m_entries[index].m_name;
            Path			path = *m_parent + name;
            n = Node::create(path);
            m_nodes->m_entries[index].m_node = n;
        }
        return n;
    }
    
    /**
     * Return how many files are in this directory
     */
    int NodeIter::subNodeCount() const
    {
        if (!m_nodes)
            return 0;
        return m_nodes->m_entries.size();
        
    }
    /**
     * If m_nodes is already initialized, this returns immediately.
     *
     * Otherwise, it calls System.listdir() and saves the list
     * of filenames.
     */
    void NodeIter::subNodeCreate() const
    {
        if (m_nodes)
            return;
        m_nodes = new SubNode;
        Strings	files = System.listdir(m_parent->path());
        std::sort(files.begin(), files.end());
        std::copy(files.begin(), files.end(),
                  std::back_insert_iterator<std::vector<SubNode::Entry> > (m_nodes->m_entries));
        
    }
}
