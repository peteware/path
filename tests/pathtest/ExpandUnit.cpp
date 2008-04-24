/*
 *  ExpandUnit.cpp
 *  path
 */

#include <path/Path.h>
#include <path/Strings.h>

#include <cppunit/TestCase.h>
#include <cppunit/extensions/HelperMacros.h>

/**
 * Implements unit tests for Canonical class
 *
 */
class ExpandUnit : public CppUnit::TestCase
{
	CPPUNIT_TEST_SUITE(ExpandUnit);
    
	CPPUNIT_TEST(simple);
    CPPUNIT_TEST(nested);
    
    CPPUNIT_TEST_SUITE_END();
protected:
	/// Test simple expansion
	void simple();
    /// Test that nested variables expand.
    void nested();
};

CPPUNIT_TEST_SUITE_REGISTRATION(ExpandUnit);

void ExpandUnit::simple()
{
    path::Path    p("$HOME");
    path::StringMap   env;
    env["HOME"] = "abc";
    
    CPPUNIT_ASSERT_EQUAL(path::Path("abc"), p.expand(env));
    p = path::Path("xxx$HOME abc");
    CPPUNIT_ASSERT_EQUAL(path::Path("xxxabc abc"), p.expand(env));
    p = path::Path("$x");
    CPPUNIT_ASSERT_EQUAL(path::Path(""), p.expand(env));
    p = path::Path("$$HOME");
    CPPUNIT_ASSERT_EQUAL(path::Path("$HOME"), p.expand(env));
    p = path::Path("~");
    CPPUNIT_ASSERT_EQUAL(path::Path(env["HOME"]), p.expand(env));
    
    env["AB_123"] = "x";
    p = path::Path("z$AB_123 abc");
    CPPUNIT_ASSERT_EQUAL(path::Path("zx abc"), p.expand(env));
}

void ExpandUnit::nested()
{
    path::Path  p("$X");
    path::StringMap env;
    env["X"] = "$HOME";
    env["HOME"] = "abc";
    
    CPPUNIT_ASSERT_EQUAL(path::Path("abc"), p.expand(env));
    p = path::Path("$X$HOME");
    CPPUNIT_ASSERT_EQUAL(path::Path("abcabc"), p.expand(env));
    
}
