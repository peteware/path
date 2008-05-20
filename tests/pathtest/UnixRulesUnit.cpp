/**
 * @file UnixRulesUnit.cpp
 * @ingroup PathTest
 */

#include <path/UnixRules.h>
#include <path/Canonical.h>
#include <path/Path.h>

#include <cppunit/TestCase.h>
#include <cppunit/extensions/HelperMacros.h>

#include "PathRulesUnit.h"
using namespace path;

class UnixRulesUnit: public PathRulesUnit
{
	CPPUNIT_TEST_SUB_SUITE(UnixRulesUnit, PathRulesUnit);
    
	CPPUNIT_TEST(init);
    CPPUNIT_TEST(testQuote);
    
	CPPUNIT_TEST_SUITE_END();
public:
    virtual void setUp();
    virtual void tearDown();    
protected:
	/// Make sure constructors/destructor works
	void init();
    void testQuote();

};

CPPUNIT_TEST_SUITE_REGISTRATION(UnixRulesUnit);

void UnixRulesUnit::setUp()
{
    setRules(new UnixRules());
}

void UnixRulesUnit::tearDown()
{
    PathRulesUnit::tearDown();
}

void UnixRulesUnit::init()
{
	UnixRules	unix_rules;
}

void UnixRulesUnit::testQuote()
{
    CPPUNIT_ASSERT_EQUAL(std::string("a"), rules()->quote("a"));
    CPPUNIT_ASSERT_EQUAL(std::string(""), rules()->quote(""));
    CPPUNIT_ASSERT_EQUAL(std::string("a_b"), rules()->quote("a/b"));
    CPPUNIT_ASSERT_EQUAL(std::string("a__b"), rules()->quote("a//b"));
    CPPUNIT_ASSERT_EQUAL(std::string("_"), rules()->quote("/"));
    CPPUNIT_ASSERT_EQUAL(std::string("abc__"), rules()->quote("abc//"));
}