/**
 * @file Win32RulesUnit.cpp
 * @ingroup PathTest
 */

#include <path/Win32Rules.h>
#include <path/Canonical.h>
#include <path/Path.h>

#include <cppunit/TestCase.h>
#include <cppunit/extensions/HelperMacros.h>

using namespace path;

class Win32RulesUnit : public CppUnit::TestCase
{
    CPPUNIT_TEST_SUITE(Win32RulesUnit);
    
    CPPUNIT_TEST(init);
    CPPUNIT_TEST(canon);
    CPPUNIT_TEST(convert);
    
    CPPUNIT_TEST_SUITE_END();
protected:
    void init();
    void canon();
    void convert();
};

CPPUNIT_TEST_SUITE_REGISTRATION(Win32RulesUnit);

void Win32RulesUnit::init()
{
    Win32Rules  rules;
    Win32Rules  rules2;
    
    rules = rules2;
}

void Win32RulesUnit::canon()
{
    Win32Rules  rules;
    Canonical  canon;
    
    canon = rules.canonical("a\\b\\c");
    CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(3), canon.components().size());
    
    canon = rules.canonical("\\a");
    CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(1), canon.components().size());
    CPPUNIT_ASSERT_EQUAL(std::string("a"), canon.components()[0]);
    CPPUNIT_ASSERT(canon.abs());
    
    canon = rules.canonical("C:\\temp");
    CPPUNIT_ASSERT_EQUAL(std::string("C"), canon.drive());
    CPPUNIT_ASSERT_EQUAL(std::string("temp"), canon.components()[0]);
    CPPUNIT_ASSERT(canon.abs());
    
}

void Win32RulesUnit::convert()
{
    Win32Rules  rules;
    Canonical  canon;
    Path        path;
    
    // Test empty
    path = Path(canon, &rules);
    CPPUNIT_ASSERT_EQUAL(std::string(""), path.str());
    CPPUNIT_ASSERT(!path.abs());
    CPPUNIT_ASSERT(path.rules() == &rules);
    
    canon.add("a");
    path = Path(canon, &rules);
    CPPUNIT_ASSERT_EQUAL(std::string("a"), path.str());
    CPPUNIT_ASSERT(!path.abs());
    CPPUNIT_ASSERT(path.rules() == &rules);
    
    canon.setAbs(true);
    path = Path(canon, &rules);
    CPPUNIT_ASSERT_EQUAL(std::string("\\a"), path.str());
    canon.add("b");

    path = Path(canon, &rules);
    CPPUNIT_ASSERT_EQUAL(std::string("\\a\\b"), path.str());
    
    std::string s = "C:\\temp\\x.c";
    path = Path (Win32Path(s), &rules);
    CPPUNIT_ASSERT_EQUAL(s, path.path());
    CPPUNIT_ASSERT_EQUAL(std::string("C"), path.drive());
    CPPUNIT_ASSERT_EQUAL(static_cast<std::string::size_type> (2), path.canon().components().size());
}
