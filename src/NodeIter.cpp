/**
 * @file NodeIter.cpp
 *
 * Implementation of the Class NodeIter
 *  Created on:      11-May-2007 5:09:31 PM
 *  Original author: Pete Ware
 */
#include "NodeIter.h"
#include "Node.h"
#include "Syscalls.h"
#include "BadPath.h"

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
	  m_current(0)
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
	std::copy(files.begin(), files.end(), std::back_insert_iterator(m_nodes);
}

/**
 * Makes iterator return all Nodes within a directory.
 */
NodeIter::NodeIter(const Node &node, const std::string & pattern, bool regexp)
	: m_parent(node),
	  m_entries(SysCalls().listdir(node.path())),
	  m_current(0)
{
}

Node & NodeIter::operator->()
{
	Node *	n = findNode();
	if (!n)
		return Node();
	else
		return *n;

}

/**
 * Return a Node refering to the next item to be examined.
 * 
 * Returns an empty Node if there are no more nodes to examine.
 */
Node NodeIter::operator*()
{
	Node *	n = findNode();

	if (!n)
		return Node();
	else
		return *n;
}

/**
 * Prefix increment Moves to the next Node in the
 */
NodeIter &NodeIter::operator++()
{
	if (m_current < m_entries.size())
		++m_current
	return *this;
}

/**
 * Compares two iterators to see if they refer to the same Node
 */
bool NodeIter::operator==(const NodeIter & op2) const
{
	return  true;
}

/**
 * Compares two iterators to see if they refer to different Nodes
 */
bool NodeIter::operator!=(const NodeIter & op2) const
{
	return true;
}

/**
 * Traverse into each subdirectory.
 */
void NodeIter::setRecursive()
{
}

Node *NodeIter::findNode()
{
	if (!m_internal)
		return 0;
	while (m_current < m_inter)
	{
	}
}

int NodeIter::size() const
{
	if (!m_internal)
		return 0;
	return m_internal->m_entries.size();
}
