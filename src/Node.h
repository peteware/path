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
#include "Path.h"
#include <string>

// Forward declarations
class NodeIter;
class NodeInfo;

/**
 * A Node represents both files, directories and any other object that can be in a
 * filesystem.
 */
class Node : public Path
{
public:
	/// Default constructor (avoid using)
	Node();

	/// Construct from a string
	Node(const std::string &p);

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

	/// Create a new node and handle exceptions if it doesn't exit
	static Node * create(Path path);

protected:
	Node(const Path &path);

private:
	mutable NodeInfo * m_cache;
};
#endif // !defined(_PATH_NODE_H)
