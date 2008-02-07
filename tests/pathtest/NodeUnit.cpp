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
    CPPUNIT_TEST(iter_file);
    CPPUNIT_TEST(opers);
	CPPUNIT_TEST_SUITE_END();
public:
    virtual void setUp();
    virtual void tearDown();
protected:
	/// Test basic initialization
	void init();
	/// Test node iteration
	void iter();
    /// Make sure we handle regular files
    void iter_file();
    /// Test NodeIter operators
    void opers();
    
    struct DirHiearchy 
    {
        Path    m_path;
        bool    m_isDir;
        DirHiearchy(const Path &p, bool isDir) : m_path (p), m_isDir(isDir){};
    };
    std::vector<DirHiearchy>    m_files;
    Path            m_base; // Directory for temporary m_files
    
    void initFiles();
    void buildFiles();
    void cleanFiles();
};

CPPUNIT_TEST_SUITE_REGISTRATION(NodeUnit);

void NodeUnit::setUp()
{
    m_base = "temp";
    initFiles();
}

void NodeUnit::tearDown()
{
    cleanFiles();
}

void NodeUnit::initFiles()
{
    m_files.push_back(DirHiearchy(m_base, true));
    m_files.push_back(DirHiearchy(m_base.join("1"), false));
    m_files.push_back(DirHiearchy(m_base.join("22"), false));
    m_files.push_back(DirHiearchy(m_base.join("333"), false));
    m_files.push_back(DirHiearchy(m_base.join("4444"), false));
    m_files.push_back(DirHiearchy(m_base.join("subdir"), true));
    //m_files.push_back(DirHiearchy(m_base.join("subdir").join("abc"), false));
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

    for (std::vector<DirHiearchy>::reverse_iterator iter = m_files.rbegin();
         iter != m_files.rend(); ++iter)
    {
        if (iter->m_isDir) 
        {
            try
            {
                SysCalls().rmdir(iter->m_path.path());                
            }
            catch (PathException e)
            {
                std::cout << "rmdir: " << e.what() << std::endl;
            }
        }
    }
}

void NodeUnit::init()
{
	Node	node (".");
    Node    node2 ("..");
    Node    node3 (Path (".")); 
    
    node = node2;
    Node    node4 = node;
    node4 = Path ("..");
}

void NodeUnit::iter()
{
    buildFiles();
	Node	node(m_base);

    std::vector<Node>   nodes;
    std::copy(node.begin(), node.end(), std::back_insert_iterator<std::vector<Node> > (nodes));
	int count = 0;
	for (Node::iterator iter = node.begin(); iter != node.end(); ++iter)
	{
		++count;
	}
    // We don't include m_base and don't go into subdirs
	CPPUNIT_ASSERT_EQUAL(static_cast<int>(m_files.size() - 1), count);
}

void NodeUnit::iter_file()
{
    Path    testfile = m_base.join("regularfile");
    buildFiles();
    SysCalls().touch(testfile.str());
    Node    n (testfile);
    CPPUNIT_ASSERT_EQUAL(0, std::distance(n.begin(), n.end()));
    SysCalls().remove(testfile.str());
}

void NodeUnit::opers()
{
    buildFiles();
    Node        node(".");
    Node::iterator  iter = node.begin();
    
    // Honestly, I couldn't figure out how to figure out
    // what the first node being returned is!  So no 
    // comparison on results; just make sure they compile
    iter->size();
    node = *iter;
}
