#include <Cannonical.h>

#include <cppunit/TestCase.h>
#include <cppunit/extensions/HelperMacros.h>

#include <sstream>
#include <vector>
#include <string>

/**
 * Implements unit tests for Cannonical class
 */

class CannonicalUnit : public CppUnit::TestCase
{
	CPPUNIT_TEST_SUITE(CannonicalUnit);

	CPPUNIT_TEST(init);
    CPPUNIT_TEST(testOstream);
	CPPUNIT_TEST_SUITE_END();
protected:
	/// Test constructor
	void init();
	/// Test output operator <<
	void testOstream();
};

CPPUNIT_TEST_SUITE_REGISTRATION(CannonicalUnit);

void CannonicalUnit::init()
{
	Cannonical	c1;
	CPPUNIT_ASSERT(c1.components().empty());
	CPPUNIT_ASSERT(c1.protocol().empty());
	CPPUNIT_ASSERT(c1.host().empty());
	CPPUNIT_ASSERT(c1.extra().empty());

	Cannonical	c2 = c1;
	CPPUNIT_ASSERT(c2.components().empty());

	Cannonical	c3 ("http", "peteware.com", "8080");
	CPPUNIT_ASSERT_EQUAL(std::string("http"), c3.protocol());
	CPPUNIT_ASSERT_EQUAL(std::string("peteware.com"), c3.host());
	CPPUNIT_ASSERT_EQUAL(std::string("8080"), c3.extra());
	std::vector<std::string>	dirs;
	dirs.push_back("a");
	dirs.push_back("b");
	dirs.push_back("c");
	for (std::vector<std::string>::const_iterator iter = dirs.begin();
		iter != dirs.end(); ++iter)
	{
		c1.add(*iter);
	}
	CPPUNIT_ASSERT_EQUAL(dirs.size(), c1.components().size());
	CPPUNIT_ASSERT(dirs == c1.components());

	dirs.clear();
	dirs.push_back("x");
	Cannonical	c4 (c3, dirs);
	CPPUNIT_ASSERT_EQUAL(c3.protocol(), c4.protocol());
	CPPUNIT_ASSERT_EQUAL(c3.host(), c4.host());
	CPPUNIT_ASSERT_EQUAL(c3.extra(), c4.extra());
	CPPUNIT_ASSERT(c3.components() != c4.components());
	CPPUNIT_ASSERT(c4.components() == dirs);
}

void CannonicalUnit::testOstream()
{
	Cannonical	c1("ftp", "ftp.peteware.com", "8080");
	c1.add("a");
	c1.add("b");
	std::ostringstream	out;

	out << c1;
	CPPUNIT_ASSERT_EQUAL(std::string("ftp://ftp.peteware.com:8080/a/b/"), out.str());

}
