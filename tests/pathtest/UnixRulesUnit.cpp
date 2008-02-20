/*
 *  UnixRulesUnit.cpp
 *  path
 *
 *  Created by Peter Ware on 2/15/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

#include <path/UnixRules.h>
#include <path/Cannonical.h>
#include <path/Path.h>

#include <cppunit/TestCase.h>
#include <cppunit/extensions/HelperMacros.h>

#include "PathRulesUnit.h"

class UnixRulesUnit: public CppUnit::TestCase
{
	CPPUNIT_TEST_SUB_SUITE(UnixRulesUnit, PathRulesUnit);
    
	CPPUNIT_TEST(init);
    
	CPPUNIT_TEST_SUITE_END();
protected:
	/// Make sure constructors/destructor works
	void init();

};

CPPUNIT_TEST_SUITE_REGISTRATION(UnixRulesUnit);

void UnixRulesUnit::init()
{
	UnixRules	unix_rules;
}
