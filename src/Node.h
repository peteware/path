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
	Node();
	virtual ~Node();

	NodeIter begin();
	NodeIter end();
	NodeIter glob(const std::string &pattern) const;

	bool exists() const;
	bool isDir() const;
	void realpath() const;
	size_t size() const;

	static Node * create(Path path);

protected:
	Node(const Path &path);

private:
	mutable NodeInfo * m_cache;
};
#endif // !defined(_PATH_NODE_H)
