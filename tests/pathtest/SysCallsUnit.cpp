#include <path/SysCalls.h>
#include <path/PathException.h>

#include <cppunit/TestCase.h>
#include <cppunit/extensions/HelperMacros.h>

class SysCallsUnit: public CppUnit::TestCase
{
	CPPUNIT_TEST_SUITE(SysCallsUnit);

	CPPUNIT_TEST(init);
	CPPUNIT_TEST(listdir);
    CPPUNIT_TEST(mkdir);
    CPPUNIT_TEST_EXCEPTION(mkdir_fail, PathException);
    CPPUNIT_TEST_EXCEPTION(rmdir_fail, PathException);
    
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
};

CPPUNIT_TEST_SUITE_REGISTRATION(SysCallsUnit);

void SysCallsUnit::init()
{
	SysCalls	sys;
}

void SysCallsUnit::listdir()
{
	SysCalls	sys;

	std::vector<std::string>	dirs = sys.listdir(".");
	CPPUNIT_ASSERT(dirs.size() > 0);

	dirs = sys.listdir("does not exit!");
	CPPUNIT_ASSERT(dirs.size() == 0);
	
}

void SysCallsUnit::mkdir()
{
    SysCalls    sys;
    sys.mkdir("xxx");
    sys.rmdir("xxx");
}

void SysCallsUnit::mkdir_fail()
{
   SysCalls().mkdir("/a/b/c/1");
}

void SysCallsUnit::rmdir_fail()
{
   SysCalls().rmdir("/a/b/c/1");
}
