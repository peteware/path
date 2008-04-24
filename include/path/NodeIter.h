/**
 * @file NodeIter.h
 */
#if !defined(_PATH_NODEITER_H_)
#define _PATH_NODEITER_H_

#include <iterator>
#include <string>

namespace path {
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
    class NodeIter :  public std::iterator<std::forward_iterator_tag, Node>
    {
        
    public:
        /// The end() iterator
        NodeIter();
        /// Copy constructor
        NodeIter(const Node &node);
        /// Regular expression macher
        NodeIter(const Node &node, const std::string &pattern, bool regexp);
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
        void setRecursive();
    private:
        /// Returns the node this iterator is referencing
        Node *      findNode();
        /// Return number of SubNode's in Node
        int         size() const;
        /// Actual Node being iterator over
        const Node *m_parent;
        /// Current index
        int			m_current;
    };
}
#endif // !defined(_PATH_NODEITER_H_)
