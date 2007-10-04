#include <PathRules.h>
#include <UnixRules.h>

#include <cppunit/TestCase.h>
#include <cppunit/extensions/HelperMacros.h>

class PathRulesUnit: public CppUnit::TestCase
{
	CPPUNIT_TEST_SUITE(PathRulesUnit);

	CPPUNIT_TEST(init);

	CPPUNIT_TEST_SUITE_END();
protected:
	/// Make sure constructors/destructor works
	void init();
};

CPPUNIT_TEST_SUITE_REGISTRATION(PathRulesUnit);

void PathRulesUnit::init()
{
	UnixRules	unix_rules;
}

