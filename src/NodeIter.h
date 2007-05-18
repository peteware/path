/**  
 * @file NodeIter.h
 *
 * Implementation of the Class NodeIter
 *
 * Created on:      11-May-2007 5:09:31 PM
 * Original author: Pete Ware
 */
#if !defined(EA_4D95992E_8689_4bc6_9B21_068D858352A2__INCLUDED_)
#define EA_4D95992E_8689_4bc6_9B21_068D858352A2__INCLUDED_

#include "Node.h"
#include <iterator>

/**
 * Used to iterate over the Nodes within a Directory.
 * 
 * There are several ways to iterator over a directory:
 * 
 * -# Just list the contents of the directory.  This is the default
 * 
 * -# List the contents of the directory and all subdirectories (recursively).
 * This can be done eithe:
 *   - Depth first: All subdirectories are visited first.
 *   - Breadth first: All Files are visited then subdirectories
 *   - In order: Directories and Files are traversed in the order they are listed.
 * This is the most efficient.
 * 
 * Additionally, you can use either shell style expansion (glob), regular
 * expressions, or a predicate function to determine if a File or Directory should
 * be examined.
 * 
 */
class NodeIter //: public std::forward_iterator
{

public:
	/// The end() iterator
	NodeIter();
	NodeIter(Node node);
	NodeIter(Node node, const std::string pattern, bool regexp);
	Node & operator->();
	bool operator!=(const NodeIter op2);
	Node operator*();
	NodeIter operator++();
	bool operator==(const NodeIter op2);
	void setRecursive();

};
#endif // !defined(EA_4D95992E_8689_4bc6_9B21_068D858352A2__INCLUDED_)
