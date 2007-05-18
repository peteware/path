/**  
 * @file Node.h
 *
 * Implementation of the Class Node
 *
 * Created on:      11-May-2007 5:09:30 PM
 * Original author: Pete Ware
 */
#if !defined(EA_C4756561_E746_4a8c_820A_6323A12D0D03__INCLUDED_)
#define EA_C4756561_E746_4a8c_820A_6323A12D0D03__INCLUDED_

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

	Node(const Path path);
	NodeIter begin();
	static Node * create(Path path);
	NodeIter end();
	bool exists();
	NodeIter glob(const std::string pattern);
	bool isDir() const;
	const void realpath();
	size_t size();

private:
	NodeInfo * m_cache;

};
#endif // !defined(EA_C4756561_E746_4a8c_820A_6323A12D0D03__INCLUDED_)
