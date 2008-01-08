#include <path/Node.h>
#include <path/NodeIter.h>
#include <path/SysCalls.h>
#include <path/PathException.h>

#include <cppunit/TestCase.h>
#include <cppunit/extensions/HelperMacros.h>

class NodeUnit: public CppUnit::TestCase
{
	CPPUNIT_TEST_SUITE(NodeUnit);

	CPPUNIT_TEST(init);
	CPPUNIT_TEST(iter);

	CPPUNIT_TEST_SUITE_END();
public:
    virtual void setUp();
    virtual void tearDown();
protected:
	/// Test basic initialization
	void init();
	/// Test node iteration
	void iter();
    
    struct DirHiearchy 
    {
        Path    m_path;
        bool    m_isDir;
        DirHiearchy(const Path &p, bool isDir) : m_path (p), m_isDir(isDir){};
    };
    std::vector<DirHiearchy>    m_files;
    
    void initFiles();
    void buildFiles();
    void cleanFiles();
};

CPPUNIT_TEST_SUITE_REGISTRATION(NodeUnit);

void NodeUnit::setUp()
{
    initFiles();
}

void NodeUnit::tearDown()
{
    cleanFiles();
}

void NodeUnit::initFiles()
{
    Path    base("temp");
    m_files.push_back(DirHiearchy(base, true));
    m_files.push_back(DirHiearchy(base.join("1"), false));
    m_files.push_back(DirHiearchy(base.join("22"), false));
    m_files.push_back(DirHiearchy(base.join("333"), false));
    m_files.push_back(DirHiearchy(base.join("4444"), false));
    m_files.push_back(DirHiearchy(base.join("subdir"), true));
    m_files.push_back(DirHiearchy(base.join("subdir").join("abc"), false));
}

void NodeUnit::buildFiles()
{
    for (std::vector<DirHiearchy>::iterator iter = m_files.begin();
         iter != m_files.end(); ++iter)
    {
        if (iter->m_isDir) 
        {
            SysCalls().mkdir(iter->m_path.path());
        }
        else
        {
            SysCalls().touch(iter->m_path.path());
        }
    }
}

void NodeUnit::cleanFiles()
{
    for (std::vector<DirHiearchy>::iterator iter = m_files.begin();
         iter != m_files.end(); ++iter)
    {
        if (!iter->m_isDir) 
        {
            try
            {
                SysCalls().remove(iter->m_path.path());
            }
            catch (PathException e)
            {
                //std::cout << "remove: " << e.what() << std::endl;
            }
        }
    }

    for (std::vector<DirHiearchy>::iterator iter = m_files.begin();
         iter != m_files.end(); ++iter)
    {
        if (iter->m_isDir) 
        {
            try
            {
                SysCalls().rmdir(iter->m_path.path());                
            }
            catch (PathException e)
            {
                //std::cout << "rmdir: " << e.what() << std::endl;
            }
        }
    }
}

void NodeUnit::init()
{
	Node	node (".");
	Node	empty;
    Node    node2 = node;
    
    empty = node2;
}

void NodeUnit::iter()
{
    buildFiles();
	Node	node("temp");
	int		count = 0;

    std::vector<Node>   nodes;
    std::copy(node.begin(), node.end(), std::back_insert_iterator<std::vector<Node> > (nodes));
#ifdef notdef
	for (Node::iterator iter = node.begin(); iter != node.end(); ++iter)
	{
		std::cout << *iter << " ";
		++count;
	}
	if (count > 0)
		std::cout << std::endl;
#endif
}
