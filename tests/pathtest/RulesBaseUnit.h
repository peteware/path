/**
 * @file RulesBaseUnit.h
 * @ingroup PathTest
 */

#include <cppunit/TestCase.h>
#include <cppunit/extensions/HelperMacros.h>
#include <path/RulesBase.h>

class RulesBaseUnit: public CppUnit::TestCase
{
	CPPUNIT_TEST_SUITE(RulesBaseUnit);
    
	CPPUNIT_TEST(init);
	CPPUNIT_TEST(canonical);
	CPPUNIT_TEST(convert);
    
	CPPUNIT_TEST_SUITE_END();
public:
    virtual void setUp();
    virtual void tearDown();
    /// Set the rules and returns the previous one
    path::RulesBase * setRules (path::RulesBase *rules);
    /// Return the rules
    path::RulesBase *rules() const;
protected:
    /// Rules to use for the test.
    path::RulesBase * m_rules;
	/// Make sure constructors/destructor works
	void init();
	/// Test conversion to canonical form
	void canonical();
	/// Test conversion to Path form
	void convert();
};
