/*
 *  PathUnitTest.h
 *  path
 *
 *  Created by Peter Ware on 2/15/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

#include <cppunit/TestCase.h>
#include <cppunit/extensions/HelperMacros.h>

class PathRulesUnit: public CppUnit::TestCase
{
	CPPUNIT_TEST_SUITE(PathRulesUnit);
    
	CPPUNIT_TEST(init);
	CPPUNIT_TEST(cannonical);
	CPPUNIT_TEST(convert);
    
	CPPUNIT_TEST_SUITE_END();
public:
    virtual void setUp();
    virtual void tearDown();
    /// Set the rules and returns the previous one
    PathRules * setRules (PathRules *rules);
    /// Return the rules
    PathRules *rules() const;
protected:
    /// Rules to use for the test.
    PathRules * m_rules;
	/// Make sure constructors/destructor works
	void init();
	/// Test conversion to cannonical form
	void cannonical();
	/// Test conversion to Path form
	void convert();
};
