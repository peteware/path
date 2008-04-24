/**  
 * @file Node.h
 */
#if !defined(_PATH_NODE_H_)
#define _PATH_NODE_H_

#include <path/Path.h>
#include <string>

namespace path {
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
    private:
        /// Default constructor (avoid using)
        Node();
    public:
        /// Construct from a string
        Node(const char *str);
        /// Construct from a string
        Node(const std::string &p);
        /// Construct from a string
        Node(const Path &path);
        /// Construct from Canonical
        Node(const Canonical &can, const PathRules *rules = 0);
        /// Copy constructor
        Node(const Node &orig);
        ///  Destructor
        virtual ~Node();
        /// Assignment operator
        Node &operator=(const Node &op2);       

        /// How to iterate through directory
        typedef NodeIter	iterator;
        /// And the const version of iterator
        typedef const NodeIter	const_iterator;
        /// Return iterator for examining files in this directory
        iterator begin();
        /// Return iterator for examining files in this directory, const version
        const_iterator begin() const;
        /// And return the end of the list
        iterator end();
        /// And return the end of the list, const version
        const_iterator end() const;
        /// Shorthand to only match a specific file in this directory
        iterator glob(const std::string &pattern);
        /// Shorthand to only match a specific file, const version
        const_iterator glob(const std::string &pattern) const;
        
        /// Return basic info about the Node (size, type, etc).
        const NodeInfo &info() const;
        /// Return the size in bytes of this file
        off_t size() const; 
        /// Check if this Node exists
        bool exists() const;
        /// Return if this is a directory
        bool isDir() const;
        /// Resolve symbolic links, etc
        Node realpath() const;
        
        /// Return a Node
        Node *subNode(int index) const;
         /// Return how many subnodes there are
        int subNodeCount() const;
        
        /// Create a new node and handle exceptions if it doesn't exist
        static Node * create(const Path &path);
        
    protected:
        /// Initialzie m_nodes (if needed)
        void subNodeCreate() const;
        
    private:
        mutable NodeInfo * m_cache;
        mutable SubNode * m_nodes;
    };
}
#endif // !defined(_PATH_NODE_H)
