/**
 * @file Node.cpp
 */
#include <path/Node.h>
#include <path/NodeInfo.h>
#include <path/NodeIter.h>
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
	: m_cache(0)
    {
    }
    
    /**
     * May throw PathException.
     *
     * @param str A string representing a directory
     */
    Node::Node(const char *str)
    : Path(str),
    m_cache(0)
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
    m_cache(0)
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
    m_cache(0)
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
    m_cache(0)
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
    m_cache(0)
    {
    }

    /**
     * Clean up the m_cache and m_nodes
     */
    Node::~Node()
    {
        delete m_cache;
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
        m_cache = 0;
        return *this;
    }
    
    /**
     * Return a new Node with all symbolic links resolved.
     */
    Node Node::realpath() const
    {
        throw Unimplemented("Node::realpath");
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
    
}
