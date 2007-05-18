/**
 * @file NodeIter.cpp
 *
 * Implementation of the Class NodeIter
 *  Created on:      11-May-2007 5:09:31 PM
 *  Original author: Pete Ware
 */
#include "NodeIter.h"


/**
 * Create a default iterator.  This corresponds to the
 * end() iterator.
 */

NodeIter::NodeIter()
{
}

/**
 * Makes iterator return all Nodes within a directory.
 */
NodeIter::NodeIter(Node node){

}


/**
 * Makes iterator return all Nodes within a directory.
 */
NodeIter::NodeIter(Node node, const std::string pattern, bool regexp){

}


Node & NodeIter::operator->()
{
	static Node	s_node;
	return s_node;
}


/**
 * Compares two iterators to see if they refer to different Nodes
 */
bool NodeIter::operator!=(const NodeIter op2){

	return  NULL;
}


/**
 * Return a Node refering to the next item to be examined.
 * 
 * Returns an empty Node if there are no more nodes to examine.
 */
Node NodeIter::operator*(){

	return  Node();
}


/**
 * Moves to the next Node in the
 */
NodeIter NodeIter::operator++(){

	return NodeIter();
}


/**
 * Compares two iterators to see if they refer to the same Node
 */
bool NodeIter::operator==(const NodeIter op2){

	return  NULL;
}


/**
 * Traverse into each subdirectory.
 */
void NodeIter::setRecursive(){

}