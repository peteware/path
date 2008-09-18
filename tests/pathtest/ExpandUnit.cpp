/**
 * @file ExpandUnit.cpp
 * @ingroup PathTest
 */

#include <path/Strings.h>

#include <cppunit/TestCase.h>
#include <cppunit/extensions/HelperMacros.h>

/**
 * Implements unit tests for expand() in Path class
 *
 */
class ExpandUnit : public CppUnit::TestCase
{
	CPPUNIT_TEST_SUITE(ExpandUnit);
    
	CPPUNIT_TEST(simple);
    CPPUNIT_TEST(nested);
    CPPUNIT_TEST(braces);
    CPPUNIT_TEST(split);
    CPPUNIT_TEST(recurse);
    
    CPPUNIT_TEST_SUITE_END();
protected:
	/// Test simple expansion
	void simple();
    /// Test that nested variables expand.
    void nested();
    /// Test that $(xxx) works
    void braces();
    /// Test that path::split() works
    void split();
	/// Test that expand var to itself $VAR=$VAR
	void recurse();
};

CPPUNIT_TEST_SUITE_REGISTRATION(ExpandUnit);

void ExpandUnit::simple()
{
    path::StringMap   env;
    env["HOME"] = "abc";
    
    CPPUNIT_ASSERT_EQUAL(std::string("abc"), path::expand("$HOME", env, true));
    CPPUNIT_ASSERT_EQUAL(std::string("xxxabc abc"), path::expand("xxx$HOME abc", env, true));
    CPPUNIT_ASSERT_EQUAL(std::string(""), path::expand("$x", env, true));
    CPPUNIT_ASSERT_EQUAL(std::string("$HOME"), path::expand("$$HOME", env, true));
    CPPUNIT_ASSERT_EQUAL(env["HOME"], path::expand("~", env, true));
    CPPUNIT_ASSERT_EQUAL(std::string("~"), path::expand("~", env, false));
    CPPUNIT_ASSERT_EQUAL(std::string("x~"), path::expand("x~", env, true));
    
    env["AB_123"] = "x";
    CPPUNIT_ASSERT_EQUAL(std::string("zx abc"), path::expand("z$AB_123 abc", env, true));
    
    CPPUNIT_ASSERT_EQUAL(std::string("abc"), path::expand("abc$", env, true));
}

void ExpandUnit::nested()
{
    path::StringMap env;

    env["X"] = "$HOME";
    env["HOME"] = "abc";
    CPPUNIT_ASSERT_EQUAL(std::string("abc"), path::expand("$X", env, true));
    CPPUNIT_ASSERT_EQUAL(std::string("abcabc"), path::expand("$X$HOME", env, true));
}

void ExpandUnit::braces()
{
    path::StringMap env;

    env["X"] = "abc";
    env["X2"] = "xyz";
    env["X$HOME"] = "def";
    env["X 2 $"] = "jklf";
    CPPUNIT_ASSERT_EQUAL(std::string("abc"), path::expand("$(X)", env, true));
    CPPUNIT_ASSERT_EQUAL(std::string("def"), path::expand("$(X$HOME)", env, true));
    CPPUNIT_ASSERT_EQUAL(std::string("abca"), path::expand("$(X)a", env, true));
    CPPUNIT_ASSERT_EQUAL(std::string("jklfa"), path::expand("$(X 2 $)a", env, true));
    CPPUNIT_ASSERT_EQUAL(std::string(""), path::expand("$(X", env, true));
}

void ExpandUnit::split()
{
    path::Strings  strings;

    strings.clear();
    path::split("", ',', strings);
    CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(0), strings.size());

    strings.clear();
    path::split("a", ',', strings);
    CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(1), strings.size());
    CPPUNIT_ASSERT_EQUAL(std::string("a"), strings[0]);
    
    strings.clear();
    path::split("a,b", ',', strings);
    CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(2), strings.size());
    CPPUNIT_ASSERT_EQUAL(std::string("a"), strings[0]);
    CPPUNIT_ASSERT_EQUAL(std::string("b"), strings[1]);

    strings.clear();
    path::split(",", ',', strings);
    CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(2), strings.size());
    CPPUNIT_ASSERT_EQUAL(std::string(""), strings[0]);
    CPPUNIT_ASSERT_EQUAL(std::string(""), strings[1]);

    strings.clear();
    path::split("//abc/d/e//", '/', strings);
    CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(7), strings.size());
    CPPUNIT_ASSERT_EQUAL(std::string(""), strings[0]);
    CPPUNIT_ASSERT_EQUAL(std::string(""), strings[1]);
    CPPUNIT_ASSERT_EQUAL(std::string("abc"), strings[2]);
    CPPUNIT_ASSERT_EQUAL(std::string("d"), strings[3]);
    CPPUNIT_ASSERT_EQUAL(std::string("e"), strings[4]);
    CPPUNIT_ASSERT_EQUAL(std::string(""), strings[5]);
    CPPUNIT_ASSERT_EQUAL(std::string(""), strings[6]);
}

void ExpandUnit::recurse()
{
    path::StringMap env;

    env["X"] = "$X";
    env["X2"] = "$(X2)";
    CPPUNIT_ASSERT_EQUAL(std::string(""), path::expand("$X", env, true));
    CPPUNIT_ASSERT_EQUAL(std::string(""), path::expand("$(X2)", env, true));
}

