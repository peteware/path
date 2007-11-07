/**
 * @file NodeIter.cpp
 *
 * Implementation of the Class NodeIter
 *  Created on:      11-May-2007 5:09:31 PM
 *  Original author: Pete Ware
 */
#include <path/NodeIter.h>
#include <path/Node.h>
#include <path/SysCalls.h>
#include <path/BadPath.h>

#include <iterator>

struct NodeIter::Internal 
{
	struct Entry 
	{
		Entry() : m_name(), m_node(0)
		{
		}
		
		Entry(const std::string &name) : m_name(name), m_node(0)
		{
		}

		Entry(const Entry&copy)
		{
			m_name = copy.m_name;
			m_node = 0;
		}

		Entry &operator=(const Entry &op2)
		{
			if (this != &op2)
			{
				m_name = op2.m_name;
				m_node = new Node(*op2.m_node);
			}
			return *this;
		}
		std::string		m_name;
		Node *			m_node;
	};
	std::vector<Entry>	m_entries;
};

/**
 * Create a default iterator.  This corresponds to the
 * end() iterator.
 */
NodeIter::NodeIter()
	: m_nodes(0),
	  m_parent(),
	  m_current(-1)
{
}

/**
 * Makes iterator return all Nodes within a directory.
 */
NodeIter::NodeIter(const Node &node)
	: m_nodes(0),
	  m_parent(node),
	  m_current(0)
{
	m_nodes = new Internal;
	std::vector<std::string>	files = SysCalls().listdir(node.path());
	std::copy(files.begin(), files.end(),
			  std::back_insert_iterator<std::vector<Internal::Entry> > (m_nodes->m_entries));
}

/**
 * Makes iterator return all Nodes within a directory.
 */
NodeIter::NodeIter(const Node &node, const std::string & pattern, bool regexp)
	: m_nodes(0),
	  m_parent(node),
	  m_current(0)
{
}

Node & NodeIter::operator->()
{
	Node *	n = findNode();
	return *n;

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
	if (m_current >= 0 && m_current + 1< static_cast<int> (m_nodes->m_entries.size()))
		++m_current;
	else
		m_current = -1;
	return *this;
}

/**
 * Compares two iterators to see if they refer to the same Node
 */
bool NodeIter::operator==(const NodeIter & op2) const
{
	// obvious case
	if (this == &op2)
		return true;
	// same m_nodes and same index
	if (m_nodes == op2.m_nodes && m_current == op2.m_current)
		return true;
	// be smart and asssume if parent the same and index same
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
	Node *n = 0;

	if (!m_nodes || m_current >= static_cast<int>(m_nodes->m_entries.size()))
		return 0;
	n = m_nodes->m_entries[m_current].m_node;
	if (!n)
	{
		std::string		name = m_nodes->m_entries[m_current].m_name;
		Path			path(name);
		n = Node::create(path);
		m_nodes->m_entries[m_current].m_node = n;
	}
	return n;
}

int NodeIter::size() const
{
	if (!m_nodes)
		return 0;
	return m_nodes->m_entries.size();
}
