#include <path/Node.h>
#include <path/NodeIter.h>

#include <cppunit/TestCase.h>
#include <cppunit/extensions/HelperMacros.h>

class NodeUnit: public CppUnit::TestCase
{
	CPPUNIT_TEST_SUITE(NodeUnit);

	CPPUNIT_TEST(init);
	CPPUNIT_TEST(iter);

	CPPUNIT_TEST_SUITE_END();
protected:
	/// Test basic initialization
	void init();
	/// Test node iteration
	void iter();
};

CPPUNIT_TEST_SUITE_REGISTRATION(NodeUnit);

void NodeUnit::init()
{
	Node	node (".");
	Node	empty;
}

void NodeUnit::iter()
{
	Node	node(".");
	int		count = 0;

	for (Node::iterator iter = node.begin(); iter != node.end(); ++iter)
	{
		std::cout << (*iter).str() << " ";
		++count;
	}
	if (count > 0)
		std::cout << std::endl;
	
}
