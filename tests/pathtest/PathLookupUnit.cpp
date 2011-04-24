/**
 * @file PathLookupUnit.cpp
 * @ingroup PathTest
 */
#include <path/PathLookup.h>

#include <cppunit/TestCase.h>
#include <cppunit/extensions/HelperMacros.h>

using namespace path;

/**
 * Implements unit tests for PathLookup class
 *
 */ 
class PathLookupUnit : public CppUnit::TestCase
{
	CPPUNIT_TEST_SUITE(PathLookupUnit);
    
	CPPUNIT_TEST(init);
    
	CPPUNIT_TEST_SUITE_END();
    
protected:
	/// Test constructor
    void init();
};

CPPUNIT_TEST_SUITE_REGISTRATION(PathLookupUnit);

void PathLookupUnit::init()
{
    PathLookup look;
    CPPUNIT_ASSERT(look.find("abc").empty());
    look.push_back(".");
    look.find("abc");
}
