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
 * Create a Node from a Path.
 * 
 * If there is no corresponding filesystem object, then an exception is raised.
 */
Node::Node(const Path &path)
	: m_cache(0)
{
}

Node::~Node()
{
	delete m_cache;
}

NodeIter Node::begin()
{
	return  NodeIter();
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
void Node::realpath() const
{

}


/**
 * Return the size in bytes
 */
size_t Node::size() const
{

	return 0;
}
