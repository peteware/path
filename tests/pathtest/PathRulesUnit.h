/**
 * @file PathRulesUnit.h
 * @ingroup PathTest
 */

#include <cppunit/TestCase.h>
#include <cppunit/extensions/HelperMacros.h>
#include <path/PathRules.h>

class PathRulesUnit: public CppUnit::TestCase
{
	CPPUNIT_TEST_SUITE(PathRulesUnit);
    
	CPPUNIT_TEST(init);
	CPPUNIT_TEST(canonical);
	CPPUNIT_TEST(convert);
    
	CPPUNIT_TEST_SUITE_END();
public:
    virtual void setUp();
    virtual void tearDown();
    /// Set the rules and returns the previous one
    path::PathRules * setRules (path::PathRules *rules);
    /// Return the rules
    path::PathRules *rules() const;
protected:
    /// Rules to use for the test.
    path::PathRules * m_rules;
	/// Make sure constructors/destructor works
	void init();
	/// Test conversion to canonical form
	void canonical();
	/// Test conversion to Path form
	void convert();
};
