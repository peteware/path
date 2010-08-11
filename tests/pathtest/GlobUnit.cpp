/**
 * @file GlobUnit.cpp
 * @ingroup PathTest
 */
#include <path/Glob.h>

#include <cppunit/TestCase.h>
#include <cppunit/extensions/HelperMacros.h>

#include <sstream>
#include <vector>
#include <string>

using namespace path;
/**
 * Implements unit tests for Glob class
 *
 */
class GlobUnit : public CppUnit::TestCase
{
    CPPUNIT_TEST_SUITE(GlobUnit);

    CPPUNIT_TEST(init);

    CPPUNIT_TEST_SUITE_END();
protected:
    /// Test constructor
    void init();
};

CPPUNIT_TEST_SUITE_REGISTRATION(GlobUnit);

void GlobUnit::init()
{
    Glob	g ("a");

    CPPUNIT_ASSERT (!g.match ("b"));
    CPPUNIT_ASSERT (g.match ("a"));
}
