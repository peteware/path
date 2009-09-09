/**
 * @file PathIter.h
 */
#if !defined(_PATH_PATHITER_H_)
#define _PATH_PATHITER_H_

#include <iterator>
#include <string>
#include <vector>

namespace path {
    // Forward declarations
    class Path;
    /**
     * @class PathIter path/PathIter.h
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
    class PathIter :  public std::iterator<std::forward_iterator_tag, Path>
    {
        
    public:
        /// The end() iterator
        PathIter();
        /// Copy constructor
        PathIter(const PathIter &copy);
        /// Create from a Node.
        PathIter(const Path &node);
        /// Regular expression macher
        PathIter(const Path &node, const std::string &pattern, bool regexp);
        /// Destructor
        ~PathIter();
        /// Assignment operator
        PathIter &operator=(const PathIter &op2);
        /// Dereferencing
        Path * operator->();
        /// Dereferencing
        Path & operator*();
        /// Comparison
        bool operator!=(const PathIter & op2) const;
        /// Comparison
        bool operator==(const PathIter &op2) const;
        /// Prefix increment
        PathIter &operator++();
        /// Postfix increment
        PathIter operator++(int);
        /// Add another element to the iter
        void addPath(const Path &path);
        /// Make this a recursive iterator
        PathIter & setRecursive();
        /// Check if matches against pattern
        bool match(const Path &path) const;

    private:
        /// Returns the node this iterator is referencing
        Path *      findNode(int index) const;
        /// List all Node's in node and add to m_nodeList
        void addNodes(const Path *node);
        /// Return number of Node
        int         size() const;
        /// Actual Node being iterated over
        const Path *m_parent;
        /// List of subdirs
        std::vector<Path *> m_nodeList;
        /// Current index
        int                     m_current;
        /// Traverse subdirectories, too
        bool        m_recursive;
    };
}
#endif // !defined(_PATH_PATHITER_H_)
