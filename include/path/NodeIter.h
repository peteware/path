/**
 * @file NodeIter.h
 */
#if !defined(_PATH_NODEITER_H_)
#define _PATH_NODEITER_H_

#include <iterator>
#include <string>
#include <vector>

namespace path {
    // Forward declarations
    class Node;
    class SubNode;    
    /**
     * @class NodeIter path/NodeIter.h
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
    class NodeIter :  public std::iterator<std::forward_iterator_tag, Node>
    {
        
    public:
        /// The end() iterator
        NodeIter();
        /// Copy constructor
        NodeIter(const NodeIter &copy);
        /// Create from a Node.
        NodeIter(const Node &node);
        /// Regular expression macher
        NodeIter(const Node &node, const std::string &pattern, bool regexp);
        /// Destructor
        ~NodeIter();
        /// Assignment operator
        NodeIter &operator=(const NodeIter &op2);
        /// Dereferencing
        Node * operator->();
        /// Dereferencing
        Node & operator*();
        /// Comparison
        bool operator!=(const NodeIter & op2) const;
        /// Comparison
        bool operator==(const NodeIter &op2) const;
        /// Prefix increment
        NodeIter &operator++();
        /// Postfix increment
        NodeIter NodeIter::operator++(int);
        /// Make this a recursive iterator
        NodeIter & setRecursive();
    private:
        /// Return a Node
        Node *subNode(int index) const;
        /// Return how many subnodes there are
        int subNodeCount() const;
        /// Initialzie m_nodes (if needed)
        void subNodeCreate();
       
        /// Returns the node this iterator is referencing
        Node *      findNode();
        /// List all Node's in node and add to m_nodeList
        void addNodes(const Node *node);
        /// Return number of SubNode's in Node
        int         size() const;
        /// Actual Node being iterated over
        const Node *m_parent;
        mutable SubNode * m_nodes;
        std::vector<Node *> m_nodeList;

        /// Current index
        int			m_current;
        /// Traverse subdirectories, too
        bool        m_recursive;
    };
}
#endif // !defined(_PATH_NODEITER_H_)
