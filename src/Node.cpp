/**
 * @file Node.cpp
 *
 * Implementation of the Class Node
 *  Created on:      11-May-2007 5:09:30 PM
 *  Original author: Pete Ware
 */
#include "Node.h"
#include "NodeInfo.h"
#include "NodeIter.h"

/**
 * Create an empty Node.
 *
 * I'm not happy about this but it became necessary to support NodeIter from Node::end().
 */
Node::Node()
	: m_cache(0)
{
}

/**
 * Create a Node from a Path.
 * 
 * If there is no corresponding filesystem object, then an exception is raised.
 */
Node::Node(const Path &path)
	: m_cache(0)
{
}

Node::Node(const std::string &str)
	: Path(str),
	  m_cache(0)
{
}


Node::~Node()
{
	delete m_cache;
}

NodeIter Node::begin()
{
	return  NodeIter(*this);
}


/**
 * Take a path String and return a Node.  If there is no corresponding file object,
 * a NULL is returned; otherwise a Node allocated with 'new' is returned.
 * 
 * This is the same as calling the Node::Node() constructor but it catches any
 * exception.
 */
Node * Node::create(Path path)
{
	return  NULL;
}

/**
 * Return an iterator to the end of Nodes
 */
NodeIter Node::end()
{

	//return  NodeIter(Node());
	return  NodeIter();
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
