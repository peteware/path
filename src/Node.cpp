/**
 * @file Node.cpp
 *
 * Implementation of the Class Node
 *  Created on:      11-May-2007 5:09:30 PM
 *  Original author: Pete Ware
 */
#include <path/Node.h>
#include <path/NodeInfo.h>
#include <path/NodeIter.h>
#include <path/SubNode.h>
#include <path/SysCalls.h>
#include <path/Cannonical.h>

/**
 * Create an empty Node.
 *
 * I'm not happy about this but it became necessary to support NodeIter from Node::end().
 */
Node::Node()
	: m_cache(0),
      m_nodes(0)
{
}

/**
 * Construct from a NUL terminated string.  May throw PathException.
 */
Node::Node(const char *path)
    : Path(path),
      m_cache(0),
      m_nodes(0)
{
}

/**
 * Construct from a std::string.  May throw PathException
 */
Node::Node(const std::string &str)
	: Path(Cannonical(str)),
	  m_cache(0),
      m_nodes(0)
{
}


/**
 * Create a Node from a Path.
 * 
 * If there is no corresponding filesystem object, then an exception is raised.
 */
Node::Node(const Path &path)
    : Path(path),
     m_cache(0),
     m_nodes(0)
{
}


Node::~Node()
{
	delete m_cache;
    delete m_nodes;
}


/**
 * Take a path String and return a Node.  If there is no corresponding file object,
 * a NULL is returned; otherwise a Node allocated with 'new' is returned.
 * 
 * This is the same as calling the Node::Node() constructor but it catches any
 * exception.
 */
Node * Node::create(const Path &path)
{
	return new Node(path);
}

/**
 * Returns if Node exists.
 */
bool Node::exists() const
{
	return  false;
}

NodeIter Node::glob(const std::string & pattern) const
{
	return  NodeIter();
}


/**
 * Returns pointer to a newly allocated Directory of the Path represents a
 * directory.  Returns NULL otherwise.
 * 
 * Caller assumes responsibility for memory deallocation.
 */
bool Node::isDir() const 
{
	return false;
}

/**
 * Return a new Node with all symbolic linkes resolved.
 */
Node Node::realpath() const
{
	return Node();
}


/**
 * Return the size in bytes
 */
size_t Node::size() const
{
	return 0;
}

NodeIter Node::begin()
{
    subNodeCreate();
    if (!m_nodes || m_nodes->m_entries.size() == 0)
        return end();
    else
        return  NodeIter(*this);
}

/**
 * Return an iterator to the end of Nodes
 */
NodeIter Node::end()
{

	//return  NodeIter(Node());
	return  NodeIter();
}

Node *Node::subNode(int index) const
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
		Path			path(name);
		n = Node::create(path);
 		m_nodes->m_entries[index].m_node = n;
	}
	return n;
}

int Node::subNodeCount() const
{
    if (!m_nodes)
        return 0;
    return m_nodes->m_entries.size();
    
}

void Node::subNodeCreate() const
{
    if (m_nodes)
        return;
	m_nodes = new SubNode;
	std::vector<std::string>	files = SysCalls().listdir(path());
	std::copy(files.begin(), files.end(),
			  std::back_insert_iterator<std::vector<SubNode::Entry> > (m_nodes->m_entries));
    
}
