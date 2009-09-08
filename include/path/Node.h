/**  
 * @file Node.h
 */
#if !defined(_PATH_NODE_H_)
#define _PATH_NODE_H_

#include <path/Path.h>
#include <string>

namespace path {
    // Forward declarations
    class PathIter;
    class NodeInfo;

    
    /**
     * @class Node path/Node.h
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

        #ifdef notdef
        /// Return basic info about the Node (size, type, etc).
        const NodeInfo &info() const;
        /// Return the size in bytes of this file
        off_t size() const; 
        /// Check if this Node exists
        bool exists() const;
        /// Return if this is a directory
        bool isDir() const;
        #endif
        /// Resolve symbolic links, etc
        Node realpath() const;
        
        /// Create a new node and handle exceptions if it doesn't exist
        static Node * create(const Path &path);
        
    protected:
        
    private:
        mutable NodeInfo * m_cache;
    };
}
#endif // !defined(_PATH_NODE_H)
