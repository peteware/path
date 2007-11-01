#include <PathRules.h>
#include <UnixRules.h>
#include <Cannonical.h>
#include <Path.h>

#include <cppunit/TestCase.h>
#include <cppunit/extensions/HelperMacros.h>

class PathRulesUnit: public CppUnit::TestCase
{
	CPPUNIT_TEST_SUITE(PathRulesUnit);

	CPPUNIT_TEST(init);
	CPPUNIT_TEST(cannonical);
	CPPUNIT_TEST(convert);

	CPPUNIT_TEST_SUITE_END();
protected:
	/// Make sure constructors/destructor works
	void init();
	/// Test conversion to cannonical form
	void cannonical();
	/// Test conversion to Path form
	void convert();
};

CPPUNIT_TEST_SUITE_REGISTRATION(PathRulesUnit);

void PathRulesUnit::init()
{
	UnixRules	unix_rules;
}

void PathRulesUnit::cannonical()
{
	UnixRules	unix_rules;
	Cannonical	cannon = unix_rules.cannonical("/a/b/c");

	CPPUNIT_ASSERT(cannon.protocol().empty());
	CPPUNIT_ASSERT(cannon.host().empty());
	CPPUNIT_ASSERT(cannon.extra().empty());
	CPPUNIT_ASSERT_EQUAL(std::string("a"), cannon.components()[0]);
	CPPUNIT_ASSERT_EQUAL(std::string("b"), cannon.components()[1]);
	CPPUNIT_ASSERT_EQUAL(std::string("c"), cannon.components()[2]);
	CPPUNIT_ASSERT_EQUAL(3UL, cannon.components().size());
	CPPUNIT_ASSERT_EQUAL(true, cannon.abs());
	
	cannon = unix_rules.cannonical("");
	CPPUNIT_ASSERT_EQUAL(0UL, cannon.components().size());
	CPPUNIT_ASSERT_EQUAL(false, cannon.abs());

	cannon = unix_rules.cannonical("///");
	CPPUNIT_ASSERT_EQUAL(0UL, cannon.components().size());
	CPPUNIT_ASSERT_EQUAL(true, cannon.abs());
	
	cannon = unix_rules.cannonical("a");
	CPPUNIT_ASSERT_EQUAL(std::string("a"), cannon.components()[0]);
	CPPUNIT_ASSERT_EQUAL(1UL, cannon.components().size());
	CPPUNIT_ASSERT_EQUAL(false, cannon.abs());

	cannon = unix_rules.cannonical("ab/cd/");
	CPPUNIT_ASSERT_EQUAL(std::string("ab"), cannon.components()[0]);
	CPPUNIT_ASSERT_EQUAL(std::string("cd"), cannon.components()[1]);
	CPPUNIT_ASSERT_EQUAL(2UL, cannon.components().size());
	CPPUNIT_ASSERT_EQUAL(false, cannon.abs());
}

void PathRulesUnit::convert()
{
	Cannonical	cannon;
	UnixRules	rules;
	Path		path = rules.convert(cannon);

	CPPUNIT_ASSERT_EQUAL(std::string(""), path.str());
	CPPUNIT_ASSERT(!path.abs());
	
	cannon.add("a");
	cannon.add("b");

	path = rules.convert(cannon);

	CPPUNIT_ASSERT_EQUAL(std::string("a/b"), path.str());
	CPPUNIT_ASSERT(!path.abs());

	cannon.setAbs(true);
	path = rules.convert(cannon);
	CPPUNIT_ASSERT_EQUAL(std::string("/a/b"), path.str());
	CPPUNIT_ASSERT(path.abs());
}
