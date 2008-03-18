/*
 *  UnixRulesUnit.cpp
 *  path
 *
 *  Created by Peter Ware on 2/15/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

#include <path/UnixRules.h>
#include <path/Canonical.h>
#include <path/Path.h>

#include <cppunit/TestCase.h>
#include <cppunit/extensions/HelperMacros.h>

#include "PathRulesUnit.h"

class UnixRulesUnit: public PathRulesUnit
{
	CPPUNIT_TEST_SUB_SUITE(UnixRulesUnit, PathRulesUnit);
    
	CPPUNIT_TEST(init);
    
	CPPUNIT_TEST_SUITE_END();
public:
    virtual void setUp();
    virtual void tearDown();    
protected:
	/// Make sure constructors/destructor works
	void init();

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
