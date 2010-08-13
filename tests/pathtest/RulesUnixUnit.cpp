/**
 * @file RulesUnixUnit.cpp
 * @ingroup PathTest
 */

#include <path/RulesUnix.h>
#include <path/Canonical.h>
#include <path/Path.h>

#include <cppunit/TestCase.h>
#include <cppunit/extensions/HelperMacros.h>

#include "RulesBaseUnit.h"
using namespace path;

class RulesUnixUnit: public RulesBaseUnit
{
    CPPUNIT_TEST_SUB_SUITE(RulesUnixUnit, RulesBaseUnit);

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

CPPUNIT_TEST_SUITE_REGISTRATION(RulesUnixUnit);

void RulesUnixUnit::setUp()
{
    setRules(new RulesUnix());
}

void RulesUnixUnit::tearDown()
{
    RulesBaseUnit::tearDown();
}

void RulesUnixUnit::init()
{
    RulesUnix	unix_rules;
}

#define QC(have,want,tmp) rules()->quote(std::string(have), &tmp); CPPUNIT_ASSERT_EQUAL(std::string(want), tmp)
#define UC(have,want,tmp) rules()->unquote(std::string(have), &tmp); CPPUNIT_ASSERT_EQUAL(std::string(want), tmp)

void RulesUnixUnit::testQuote()
{
    std::string     str;

    CPPUNIT_ASSERT(rules()->quote("/", 0));
    CPPUNIT_ASSERT(!rules()->quote("a", 0));

    QC("a", "a", str);
    QC("", "", str);
    QC("a/b", "a_!_b", str);
    QC("a//b", "a_!__!_b", str);
    QC("/", "_!_", str);
    QC("abc/", "abc_!_", str);
    QC("abc//", "abc_!__!_", str);

    UC("a", "a", str);
    UC("_", "_", str);
    UC("_!", "_!", str);
    UC("_!a", "_!a", str);
    UC("_!_", "/", str);
    UC("__", "__", str);
    UC("__a", "__a", str);
    UC("__!_", "_/", str);

}
