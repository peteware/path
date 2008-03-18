/*
 *  Win32RulesUnit.cpp
 *  path
 *
 *  Created by Peter Ware on 2/22/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

#include <path/Win32Rules.h>
#include <path/Cannonical.h>
#include <path/Path.h>

#include <cppunit/TestCase.h>
#include <cppunit/extensions/HelperMacros.h>

class Win32RulesUnit : public CppUnit::TestCase
{
    CPPUNIT_TEST_SUITE(Win32RulesUnit);
    
    CPPUNIT_TEST(init);
    CPPUNIT_TEST(cannon);
    CPPUNIT_TEST(convert);
    
    CPPUNIT_TEST_SUITE_END();
protected:
    void init();
    void cannon();
    void convert();
};

CPPUNIT_TEST_SUITE_REGISTRATION(Win32RulesUnit);

void Win32RulesUnit::init()
{
    Win32Rules  rules;
    Win32Rules  rules2;
    
    rules = rules2;
}

void Win32RulesUnit::cannon()
{
    Win32Rules  rules;
    Cannonical  cannon;
    
    cannon = rules.cannonical("a\\b\\c");
    CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(3), cannon.components().size());
    
    cannon = rules.cannonical("\\a");
    CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(1), cannon.components().size());
    CPPUNIT_ASSERT_EQUAL(std::string("a"), cannon.components()[0]);
    CPPUNIT_ASSERT(cannon.abs());
    
    cannon = rules.cannonical("C:\\temp");
    CPPUNIT_ASSERT_EQUAL(std::string("C"), cannon.drive());
    CPPUNIT_ASSERT_EQUAL(std::string("temp"), cannon.components()[0]);
    CPPUNIT_ASSERT(cannon.abs());
    
}

void Win32RulesUnit::convert()
{
    Win32Rules  rules;
    Cannonical  cannon;
    Path        path;
    
    // Test empty
    path = Path(cannon, &rules);
    CPPUNIT_ASSERT_EQUAL(std::string(""), path.str());
    CPPUNIT_ASSERT(!path.abs());
    CPPUNIT_ASSERT(path.rules() == &rules);
    
    cannon.add("a");
    path = Path(cannon, &rules);
    CPPUNIT_ASSERT_EQUAL(std::string("a"), path.str());
    CPPUNIT_ASSERT(!path.abs());
    CPPUNIT_ASSERT(path.rules() == &rules);
    
    cannon.setAbs(true);
    path = Path(cannon, &rules);
    CPPUNIT_ASSERT_EQUAL(std::string("\\a"), path.str());
    cannon.add("b");

    path = Path(cannon, &rules);
    CPPUNIT_ASSERT_EQUAL(std::string("\\a\\b"), path.str());
    
    std::string s = "C:\\temp\\x.c";
    path = Path (Win32Path(s), &rules);
    CPPUNIT_ASSERT_EQUAL(s, path.path());
    CPPUNIT_ASSERT_EQUAL(std::string("C"), path.drive());
    CPPUNIT_ASSERT_EQUAL(static_cast<std::string::size_type> (2), path.cannon().components().size());
}
