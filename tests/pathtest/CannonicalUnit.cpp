#include <path/Cannonical.h>

#include <cppunit/TestCase.h>
#include <cppunit/extensions/HelperMacros.h>

#include <sstream>
#include <vector>
#include <string>

/**
 * Implements unit tests for Cannonical class
 *
 */
class CannonicalUnit : public CppUnit::TestCase
{
	CPPUNIT_TEST_SUITE(CannonicalUnit);

	CPPUNIT_TEST(init);
    CPPUNIT_TEST(testOstream);
	CPPUNIT_TEST(testDrive);
    CPPUNIT_TEST_SUITE_END();
protected:
	/// Test constructor
	void init();
	/// Test output operator <<
	void testOstream();
    /// Test the setDrive()/drive()
    void testDrive();
};

CPPUNIT_TEST_SUITE_REGISTRATION(CannonicalUnit);

void CannonicalUnit::init()
{
	Cannonical	c1;
	CPPUNIT_ASSERT(c1.components().empty());
	CPPUNIT_ASSERT(c1.protocol().empty());
	CPPUNIT_ASSERT(c1.host().empty());
	CPPUNIT_ASSERT(c1.extra().empty());
    CPPUNIT_ASSERT(c1.drive().empty());

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
    
    std::ostringstream  out2;
    Cannonical c2;
    c2.add("a");
    c2.setDrive("C");
    out2 << c2;
    CPPUNIT_ASSERT_EQUAL(std::string("C:a/"), out2.str());
    std::ostringstream  out3;
    c2.setAbs(true);
    out3 << c2;
    CPPUNIT_ASSERT_EQUAL(std::string("C:/a/"), out3.str());
    
}

void CannonicalUnit::testDrive()
{
    Cannonical  c1;
    c1.setDrive("abc");
    CPPUNIT_ASSERT_EQUAL(std::string("abc"), c1.drive());
    c1.setDrive("abc:");
    CPPUNIT_ASSERT_EQUAL(std::string("abc:"), c1.drive());
    /// Test copy operator
    Cannonical c2(c1);
    Cannonical c3;
    CPPUNIT_ASSERT_EQUAL(c1.drive(), c2.drive());
    
    c3 = c1;
    CPPUNIT_ASSERT_EQUAL(c1.drive(), c3.drive());

    
}