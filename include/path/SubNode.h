/**
 * @file SubNode.h
 */
#ifndef _PATH_SUBNODE_H_
#define _PATH_SUBNODE_H_

#include <string>
#include <vector> 

namespace path 
{
    // Forward declaration
    class Node;

    /**
     * @class SubNode path/SubNode.h
     * Used for keeping track of directory entries
     */
    struct SubNode
    {
        struct Entry 
        {
            Entry();
            Entry(const std::string &name);
            Entry(const Entry&copy);
            Entry &operator=(const Entry &op2);
            
            std::string		m_name;
            Node *			m_node;
        };
        std::vector<Entry>	m_entries;
    };
}
#endif
