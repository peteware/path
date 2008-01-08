#if !defined(_PATH_NODEITER_H_)
#define _PATH_NODEITER_H_

#include <iterator>
#include <string>

// Forward declarations
class Node;

/**
 * Used to iterate over the Nodes within a Directory.
 * 
 * There are several ways to iterate over a directory:
 * 
 * -# Just list the contents of the directory.  This is the default
 * 
 * -# List the contents of the directory and all subdirectories (recursively).
 *    This can be done either:
 *    - Depth first: All subdirectories are visited first.
 *    - Breadth first: All Files are visited then subdirectories
 *    - In order: Directories and Files are traversed in the order they
 *      are listed.  This is the most efficient.
 * 
 * Additionally, you can use either shell style expansion (glob),
 * regular expressions, or a predicate function to determine if a File
 * or Directory should be examined.
 * 
 */
class NodeIter :  public std::forward_iterator
{

public:
	/// The end() iterator
	NodeIter();
	NodeIter(const Node &node);
	NodeIter(const Node &node, const std::string &pattern, bool regexp);
	Node & operator->();
	Node & operator*();
	bool operator!=(const NodeIter & op2) const;
	NodeIter &operator++();
	bool operator==(const NodeIter &op2) const;
	void setRecursive();
private:
	Node *      findNode();
	int         size() const;
	const Node *m_parent;
	int			m_current;
};
#endif // !defined(_PATH_NODEITER_H_)
