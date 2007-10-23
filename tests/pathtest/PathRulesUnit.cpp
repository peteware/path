#include <PathRules.h>
#include <UnixRules.h>
#include <Cannonical.h>

#include <cppunit/TestCase.h>
#include <cppunit/extensions/HelperMacros.h>

class PathRulesUnit: public CppUnit::TestCase
{
	CPPUNIT_TEST_SUITE(PathRulesUnit);

	CPPUNIT_TEST(init);
	CPPUNIT_TEST(cannonical);

	CPPUNIT_TEST_SUITE_END();
protected:
	/// Make sure constructors/destructor works
	void init();
	/// Test converstion to cannonical form
	void cannonical();
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
	CPPUNIT_ASSERT_EQUAL(3UL, cannon.components().size());	
}
