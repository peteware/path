/**
 * @file Node.cpp
 */
#include <path/Node.h>
#include <path/NodeInfo.h>
#include <path/NodeIter.h>
#include <path/SubNode.h>
#include <path/SysCalls.h>
#include <path/Canonical.h>
#include <path/PathException.h>
#include <path/Unimplemented.h>

#include <sys/errno.h>  // System dependency?

namespace path {
    
    /**
     * Create an empty Node.
     *
     * I'm not happy about this but it became necessary to support NodeIter from Node::end().
     */
    Node::Node()
	: m_cache(0),
    m_nodes(0)
    {
    }
    
    /**
     * May throw PathException.
     *
     * @param str A string representing a directory
     */
    Node::Node(const char *str)
    : Path(str),
    m_cache(0),
    m_nodes(0)
    {
        if (!exists())
            throw PathException(path(), errno);
    }
    
    /**
     * Construct from a std::string.  May throw PathException
     *
     * @param str A string representing a directory
     */
    Node::Node(const std::string &str)
	: Path(Canonical(str)),
    m_cache(0),
    m_nodes(0)
    {
        if (!exists())
            throw PathException(path(), errno);
    }
    
    
    /**
     * Create a Node from a Path.
     * 
     * If there is no corresponding filesystem object, then an exception is raised.
     *
     * @param p Path to be copied from
     */
    Node::Node(const Path &p)
    : Path(p),
    m_cache(0),
    m_nodes(0)
    {
        if (!exists())
            throw PathException(path(), errno);
    }
    
    /**
     * Use a Canonical object to construct this using the given set of rules
     * to translate convert the Canonical path into a string.
     *
     * If there is no corresponding filesystem object, then an exception is raised.
     *
     * @param can The Canonical path
     * @param rules PathRules to use to translate into a path name
     */
    Node::Node(const Canonical &can, const PathRules *rules)
    : Path(can, rules),
    m_cache(0),
    m_nodes(0)
    {
        if (!exists())
            throw PathException(path(), errno);
    }
    
    /**
     * We bypass the check for existence.  Let's assume
     * if the orig existed, it still does.
     *
     * @param orig The Node being copied
     */
    Node::Node(const Node &orig)
    : Path(orig),
    m_cache(0),
    m_nodes(0)
    {
    }

    /**
     * Clean up the m_cache and m_nodes
     */
    Node::~Node()
    {
        delete m_cache;
        delete m_nodes;
    }

    /**
     * Call the Path assignment operator then delete m_cache and m_nodes
     * and set them to NULL
     *
     * @param op2 The right hand side of the assignment
     * @return a Reference to this object so you can chain use the result
     */
    Node &Node::operator=(const Node &op2)
    {
        if (this == &op2)
            return *this;
        Path::operator=(op2);
        delete m_cache;
        delete m_nodes;
        m_cache = 0;
        m_nodes = 0;
        return *this;
    }
    
    Node::iterator Node::begin()
    {
        subNodeCreate();
        if (!m_nodes || m_nodes->m_entries.size() == 0)
            return end();
        else
            return  NodeIter(*this);
    }
    
    Node::const_iterator Node::begin() const
    {
        subNodeCreate();
        if (!m_nodes || m_nodes->m_entries.size() == 0)
            return end();
        else
            return  NodeIter(*this);
    }
    
    /**
     * Return an iterator to the end of Nodes
     */
    Node::iterator Node::end()
    {
        return  NodeIter();
    }
    
    /**
     * Return an iterator to the end of Nodes
     */
    Node::const_iterator Node::end() const
    {
        return  NodeIter();
    }
    
    /**
     * Use shell pattern expansion to list
     * contents of a directory.  Returns an
     * iterator to the list.  Note that this
     * only works within the specied directory
     * that this Node already represents.
     *
     * Not yet implemented
     *
     * @param pattern A shell pattern ("*.C", "*", *.[Cho]")
     */
    Node::iterator Node::glob(const std::string & pattern)
    {
        throw Unimplemented("Node::glob");
        return  NodeIter();
    }

    /**
     * @param pattern A shell pattern ("*.C", "*", *.[Cho]")
     */
    Node::const_iterator Node::glob(const std::string & pattern) const
    {
        throw Unimplemented("Node::glob");
        return  NodeIter();
    }
    
    const NodeInfo & Node::info() const
    {
        if (!m_cache)
            m_cache = System.stat(path());
        return *m_cache;
    }

    /**
     * This is a shorthand for Node:info().size().
     * @return bytes used by file
     */
    off_t Node::size() const
    {
        return info().size();
    }
    
    /**
     * Returns if Node still exists.  Remember, you'll get
     * PathException when constructing the Node but
     * someone else can always remove the file.  Just
     * to increase your stress level, there's no
     * guarantee that the file won't get removed
     * between the time you call this and when
     * you do the next operation.  Don't worry; be happy!
     *
     * Summary: It's nice for the user to check
     * but the reality is you should always be prepared
     * for file operations to fail.
     *
     * @return True if the file exists, false otherwise.
     */
    bool Node::exists() const
    {
        return  System.exists(path());
    }
    
    /**
     * Returns pointer to a newly allocated Directory of the Path represents a
     * directory.  Returns NULL otherwise.
     * 
     * Caller assumes responsibility for memory deallocation.
     */
    bool Node::isDir() const 
    {
        return info().isDir();
    }
    
    /**
     * Return a new Node with all symbolic linkes resolved.
     */
    Node Node::realpath() const
    {
        throw Unimplemented("Node::realpath");
    }
    

    /**
     * @param index First is 0.  
     * @return Node refered by index.
     */
    Node *Node::subNode(int index) const
    {
        Node *n = 0;
        
        subNodeCreate();
        if (!m_nodes)
            return 0;
        if (index < 0 || index >= static_cast<int>(m_nodes->m_entries.size()))
            return 0;
        n = m_nodes->m_entries[index].m_node;
        if (!n)
        {
            std::string		name = m_nodes->m_entries[index].m_name;
            Path			path = *this + name;
            n = Node::create(path);
            m_nodes->m_entries[index].m_node = n;
        }
        return n;
    }
    
    /**
     * Return how many files are in this directory
     */
    int Node::subNodeCount() const
    {
        if (!m_nodes)
            return 0;
        return m_nodes->m_entries.size();
        
    }

    
    /**
     * Take a path String and return a Node.  If there is no corresponding file object,
     * a NULL is returned; otherwise a Node allocated with 'new' is returned.
     * 
     * This is the same as calling the Node::Node() constructor but it catches any
     * exception.
     *
     * @param path The path to create a Node for
     * @return Newly created Node or NULL if it doesn't already exist
     */
    Node * Node::create(const Path &path)
    {
        try
        {
            return new Node(path);
        }
        catch (PathException)
        {
            return 0;
        }
    }
    
    /**
     * If m_nodes is already initialized, this returns immediately.
     *
     * Otherwise, it calls System.listdir() and saves the list
     * of filenames.
     */
    void Node::subNodeCreate() const
    {
        if (m_nodes)
            return;
        m_nodes = new SubNode;
        Strings	files = System.listdir(path());
        std::sort(files.begin(), files.end());
        std::copy(files.begin(), files.end(),
                  std::back_insert_iterator<std::vector<SubNode::Entry> > (m_nodes->m_entries));
        
    }
}
