/**  
 * @file Node.h
 *
 * Implementation of the Class Node
 *
 * Created on:      11-May-2007 5:09:30 PM
 * Original author: Pete Ware
 */
#if !defined(_PATH_NODE_H_)
#define _PATH_NODE_H_

#include <path/Path.h>
#include <string>

// Forward declarations
class NodeIter;
class NodeInfo;
class SubNode;

/**
 * A Node represents both files, directories and any other object 
 * that can be in a filesystem.
 */
class Node : public Path
{
public:
	/// Default constructor (avoid using)
	Node();

	/// Construct from a string
    Node(const char *path);

	/// Construct from a string
	Node(const std::string &p);

	/// Construct from a string
	Node(const Path &path);

	///  Destructor
	virtual ~Node();

	typedef NodeIter	iterator;
	typedef const NodeIter	const_iterator;
	/// Return iterator for examining files in this directory
	NodeIter begin();

	const NodeIter begin() const;

	/// Shorthand to only match a specific file
	NodeIter glob(const std::string &pattern) const;

	/// And return the end of the list
	NodeIter end();

	/// Check if this Node exists
	bool exists() const;

	/// Return if this is a directory
	bool isDir() const;

	/// Resolve symbolic links, etc
	Node realpath() const;

	/// Return the size of the node in bytes
	size_t size() const;

    /// Return a Node
    Node *subNode(int index) const;
    
    /// Return how many subnodes there are
    int subNodeCount() const;
    
    
	/// Create a new node and handle exceptions if it doesn't exit
	static Node * create(const Path &path);

protected:
    void subNodeCreate() const;

private:
	mutable NodeInfo * m_cache;
    mutable SubNode * m_nodes;
};
#endif // !defined(_PATH_NODE_H)
