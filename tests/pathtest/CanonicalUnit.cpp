#include <path/Canonical.h>

#include <cppunit/TestCase.h>
#include <cppunit/extensions/HelperMacros.h>

#include <sstream>
#include <vector>
#include <string>

using namespace path;
/**
 * Implements unit tests for Canonical class
 *
 */
class CanonicalUnit : public CppUnit::TestCase
{
	CPPUNIT_TEST_SUITE(CanonicalUnit);

	CPPUNIT_TEST(init);
    CPPUNIT_TEST(testOstream);
	CPPUNIT_TEST(testDrive);
    CPPUNIT_TEST(testCompare);
    CPPUNIT_TEST(testAdd);
    CPPUNIT_TEST(testCopyInfo);
    
    CPPUNIT_TEST_SUITE_END();
protected:
	/// Test constructor
	void init();
	/// Test output operator <<
	void testOstream();
    /// Test the setDrive()/drive()
    void testDrive();
    /// Test the == and != operator
    void testCompare();
    /// Test the .add() and variations
    void testAdd();
    /// Test the copyInfo() method
    void testCopyInfo();
};

CPPUNIT_TEST_SUITE_REGISTRATION(CanonicalUnit);

void CanonicalUnit::init()
{
	Canonical	c1;
	CPPUNIT_ASSERT(c1.components().empty());
	CPPUNIT_ASSERT(c1.protocol().empty());
	CPPUNIT_ASSERT(c1.host().empty());
	CPPUNIT_ASSERT(c1.extra().empty());
    CPPUNIT_ASSERT(c1.drive().empty());

	Canonical	c2 = c1;
	CPPUNIT_ASSERT(c2.components().empty());

	Canonical	c3;
    c3.setProtocol("http");
    c3.setHost("peteware.com");
    c3.setExtra("8080");
	CPPUNIT_ASSERT_EQUAL(std::string("http"), c3.protocol());
	CPPUNIT_ASSERT_EQUAL(std::string("peteware.com"), c3.host());
	CPPUNIT_ASSERT_EQUAL(std::string("8080"), c3.extra());
	Strings	dirs;
	dirs.push_back("a");
	dirs.push_back("b");
	dirs.push_back("c");
	for (Strings::const_iterator iter = dirs.begin();
		iter != dirs.end(); ++iter)
	{
		c1.add(*iter);
	}
	CPPUNIT_ASSERT_EQUAL(dirs.size(), c1.components().size());
	CPPUNIT_ASSERT(dirs == c1.components());

	dirs.clear();
	dirs.push_back("x");
	Canonical	c4 (c3, dirs);
	CPPUNIT_ASSERT_EQUAL(c3.protocol(), c4.protocol());
	CPPUNIT_ASSERT_EQUAL(c3.host(), c4.host());
	CPPUNIT_ASSERT_EQUAL(c3.extra(), c4.extra());
	CPPUNIT_ASSERT(c3.components() != c4.components());
	CPPUNIT_ASSERT(c4.components() == dirs);
}

void CanonicalUnit::testOstream()
{
	Canonical	c1;
    c1.setProtocol("ftp").setHost("ftp.peteware.com").setExtra("8080").add("a");
	c1.add("b");
	std::ostringstream	out;

	out << c1;
	CPPUNIT_ASSERT_EQUAL(std::string("ftp://ftp.peteware.com:8080/a/b/"), out.str());
    
    std::ostringstream  out2;
    Canonical c2;
    c2.add("a");
    c2.setDrive("C");
    out2 << c2;
    CPPUNIT_ASSERT_EQUAL(std::string("C:a/"), out2.str());
    std::ostringstream  out3;
    c2.setAbs(true);
    out3 << c2;
    CPPUNIT_ASSERT_EQUAL(std::string("C:/a/"), out3.str());
    
}

void CanonicalUnit::testDrive()
{
    Canonical  c1;
    c1.setDrive("abc");
    CPPUNIT_ASSERT_EQUAL(std::string("abc"), c1.drive());
    c1.setDrive("abc:");
    CPPUNIT_ASSERT_EQUAL(std::string("abc:"), c1.drive());
    /// Test copy operator
    Canonical c2(c1);
    Canonical c3;
    CPPUNIT_ASSERT_EQUAL(c1.drive(), c2.drive());
    
    c3 = c1;
    CPPUNIT_ASSERT_EQUAL(c1.drive(), c3.drive());    
}

void CanonicalUnit::testCompare()
{
    Canonical  c1;
    Canonical  c2;
    CPPUNIT_ASSERT(c1 == c2);
    CPPUNIT_ASSERT(!(c1 != c2));
    
    c1 = Canonical("a", "b");
    CPPUNIT_ASSERT(c1 != c2);
    c2 = Canonical("a");
    CPPUNIT_ASSERT(c1 != c2);
    c2.add("b");
    CPPUNIT_ASSERT(c1 == c2);
    c2.add("c");
    CPPUNIT_ASSERT(c1 != c2);
    
    c1 = c2;
    c1.setProtocol("xyz");
    CPPUNIT_ASSERT(c1 != c2);
    
    c1 = c2;
    c1.setHost("xyz");
    CPPUNIT_ASSERT(c1 != c2);
    
    c1 = c2;
    c1.setDrive("xyz");
    CPPUNIT_ASSERT(c1 != c2);
    
    c1 = c2;
    c1.setExtra("xyz");
    CPPUNIT_ASSERT(c1 != c2);
    
}

void CanonicalUnit::testAdd()
{
    Canonical  c1("a", "b", "c", "d");
    Canonical  c2;
    c2.add("a").add("b").add("c").add("d");
    
    CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(4), c1.components().size());
    CPPUNIT_ASSERT_EQUAL(c1, c2);
}

void CanonicalUnit::testCopyInfo()
{
    Canonical   c1("a", "b", "c");
    Canonical   c2;
    
    c1.setDrive("C");
    c1.setProtocol("http");
    c1.setExtra("8080");
    c1.setHost("www.peteware.com");
    
    c2.copyInfo(c1);
    CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(0), c2.components().size());
    CPPUNIT_ASSERT_EQUAL(c1.protocol(), c2.protocol());
    CPPUNIT_ASSERT_EQUAL(c1.host(), c2.host());
    CPPUNIT_ASSERT_EQUAL(c1.extra(), c2.extra());
    CPPUNIT_ASSERT_EQUAL(std::string(""), c2.drive());

    c2.setHost("nowhere");
    c2.copyInfo(c1).setDrive("A");
    CPPUNIT_ASSERT_EQUAL(c1.host(), c2.host());
    CPPUNIT_ASSERT_EQUAL(std::string("A"), c2.drive());
}
