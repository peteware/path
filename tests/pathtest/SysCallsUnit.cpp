#include <path/SysCalls.h>

#include <cppunit/TestCase.h>
#include <cppunit/extensions/HelperMacros.h>

class SysCallsUnit: public CppUnit::TestCase
{
	CPPUNIT_TEST_SUITE(SysCallsUnit);

	CPPUNIT_TEST(init);
	CPPUNIT_TEST(listdir);

	CPPUNIT_TEST_SUITE_END();
protected:
	/// Test basic initialization
	void init();
	/// Test listing a directory
	void listdir();
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
