/**
 * @file SysBaseUnit.cpp
 * @ingroup PathTest
 */
#include <path/SysBase.h>
#include <path/PathException.h>

#include <stdlib.h>

#include <cppunit/TestCase.h>
#include <cppunit/extensions/HelperMacros.h>

using namespace path;

class SysBaseUnit: public CppUnit::TestCase
{
	CPPUNIT_TEST_SUITE(SysBaseUnit);

	CPPUNIT_TEST(init);
	CPPUNIT_TEST(listdir);
    CPPUNIT_TEST(mkdir);
    CPPUNIT_TEST_EXCEPTION(mkdir_fail, PathException);
    CPPUNIT_TEST_EXCEPTION(rmdir_fail, PathException);
	CPPUNIT_TEST(env);
    
	CPPUNIT_TEST_SUITE_END();
protected:
	/// Test basic initialization
	void init();
	/// Test listing a directory
	void listdir();
    /// Test create a directory
    void mkdir();
    /// Test that mkdir raises the correct exception
    void mkdir_fail();
    /// Test that mkdir raises the correct exception
    void rmdir_fail();
    /// Test that env() works
    void env();
};

CPPUNIT_TEST_SUITE_REGISTRATION(SysBaseUnit);

void SysBaseUnit::init()
{
	SysBase	sys;
}

void SysBaseUnit::listdir()
{
	Strings	dirs = System.listdir(".");
	CPPUNIT_ASSERT(dirs.size() > 0);

	dirs = System.listdir("does not exit!");
	CPPUNIT_ASSERT(dirs.size() == 0);
	
}

void SysBaseUnit::mkdir()
{
    System.mkdir("xxx");
    System.rmdir("xxx");
}

void SysBaseUnit::mkdir_fail()
{
   System.mkdir("/a/b/c/1");
}

void SysBaseUnit::rmdir_fail()
{
   System.rmdir("/a/b/c/1");
}

void SysBaseUnit::env()
{
    StringMap   m = System.env();
    
    CPPUNIT_ASSERT_EQUAL(std::string(getenv("HOME")), m["HOME"]);
}

