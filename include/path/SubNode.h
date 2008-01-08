#ifndef _PATH_SUBNODE_H_
#define _PATH_SUBNODE_H_

#include <string>
#include <vector> 

class Node;
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
#endif
