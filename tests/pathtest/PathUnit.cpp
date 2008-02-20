#include <path/Path.h>
#include <path/PathRules.h>
#include <path/UnixRules.h>


#include <cppunit/TestCase.h>
#include <cppunit/extensions/HelperMacros.h>

/**
 * Implements unit tests for Path class
 *
 * There are many non-obvious problems in manipulating
 * paths.  This is a fairly complex test suite as
 * as a result.
 *
 * The biggest weakness is it doesn't currently
 * adopt to different PathRules.  Ideally, it
 * should be a base class with derived classes
 * substituting in different PathRules and
 * providing a way to construct appropriate paths.
 * 
 */ 
class PathUnit : public CppUnit::TestCase
{
	CPPUNIT_TEST_SUITE(PathUnit);

	CPPUNIT_TEST(init);
    CPPUNIT_TEST(equal);
    CPPUNIT_TEST(testOstream);
    CPPUNIT_TEST(testBasename);
   	CPPUNIT_TEST(testDirname);
	CPPUNIT_TEST(testExtension);
	CPPUNIT_TEST(testStem);
	CPPUNIT_TEST(testAbs);
	CPPUNIT_TEST(testJoin);
	CPPUNIT_TEST(testRules);
   	CPPUNIT_TEST(testGetcwd);
    
	CPPUNIT_TEST_SUITE_END();

protected:
	/// Test constructor
    void init();
	/// Test comparison operator
    void equal();
	/// Test output operator
    void testOstream();
	/// Test Path::basename()
	void testBasename();
	/// Test Path::dirname()
	void testDirname();
	/// Test Path::extension()
	void testExtension();
	/// Test Path::stem()
	void testStem();
	/// Test Path::abs() and Path:;setAbs()
	void testAbs();
	/// Test Path::join()
	void testJoin();
	/// Check that we can set the path rules
	void testRules();
    /// Check static member function getcwd() works
    void testGetcwd();

};

CPPUNIT_TEST_SUITE_REGISTRATION(PathUnit);

/**
 * Test the constructor
 * -# Default empty constructor
 * -# Assignment
 */
void PathUnit::init()
{
	Path	p1;
	Path	p2;
	std::string	pathstr("xyz");
	Path	p3(pathstr);

	CPPUNIT_ASSERT(0 == p1.pathRules());
	CPPUNIT_ASSERT_EQUAL(p1, p2);
	CPPUNIT_ASSERT_EQUAL(std::string(""), p1.str());
 
	p1 = p3;
	CPPUNIT_ASSERT_EQUAL(std::string(pathstr), p1.str());
}

/**
 * Test are:
 * -# equal paths are equal
 * -# empty paths are equal
 * -# empty and non empty are  not equal
 * -# different are not equal
 * -# != works
 */
void PathUnit::equal()
{
	Path	p0("/a");
	Path	p1("/a/b/c");
	Path	p2("/a");
	Path	p3, p4;

	CPPUNIT_ASSERT_EQUAL(p0, p2);
	CPPUNIT_ASSERT_EQUAL(p3, p4);
	CPPUNIT_ASSERT(!(p0 == p3));
	CPPUNIT_ASSERT(!(p1 == p2));
	CPPUNIT_ASSERT(p0 != p1);
}

/**
 * Check that the streaming operator<<() works.
 */
void PathUnit::testOstream()
{
	std::ostringstream	oss;
	std::string			pathstr("/a/b c d/e ");
	Path				p1(pathstr);

	oss << p1;

	CPPUNIT_ASSERT_EQUAL(pathstr, oss.str());
}

void PathUnit::testBasename()
{
	Path	p1;
	Path	p2;
	// Make sure we don't crap out on empty ones.
	CPPUNIT_ASSERT_EQUAL(p1.basename(), p2);
	CPPUNIT_ASSERT_EQUAL(Path("a"), Path("///a").basename());
	CPPUNIT_ASSERT_EQUAL(Path("b"), Path("/a/b///").basename());
	CPPUNIT_ASSERT_EQUAL(Path("a"), Path("a").basename());
	CPPUNIT_ASSERT_EQUAL(Path("a"), Path("/a").basename());
	CPPUNIT_ASSERT_EQUAL(Path("b"), Path("/a/b").basename());
	CPPUNIT_ASSERT_EQUAL(Path("b"), Path("/a/b/").basename());
	CPPUNIT_ASSERT_EQUAL(Path("/"), Path("/").basename());
	CPPUNIT_ASSERT_EQUAL(Path("/"), Path("////").basename());
	CPPUNIT_ASSERT_EQUAL(Path("b"), Path("b/").basename());
	CPPUNIT_ASSERT_EQUAL(Path("b"), Path ("b///").basename());

}

/**
 * Tests Path::dirname().
 */
void PathUnit::testDirname()
{
	CPPUNIT_ASSERT_EQUAL(Path(""), Path("a").dirname());
	CPPUNIT_ASSERT_EQUAL(Path(""), Path("a////").dirname());
	CPPUNIT_ASSERT_EQUAL(Path("/a"), Path("/a/b").dirname());
	CPPUNIT_ASSERT_EQUAL(Path("/"), Path("/a").dirname());
	CPPUNIT_ASSERT_EQUAL(Path("a"), Path("a///b").dirname());

}

void PathUnit::testExtension()
{
	CPPUNIT_ASSERT_EQUAL(std::string(".c"), Path("a.c").extension());
	CPPUNIT_ASSERT_EQUAL(std::string(".c"), Path("/a/b/t.c").extension());
	CPPUNIT_ASSERT_EQUAL(std::string(".bak"), Path("a.bak").extension());
	CPPUNIT_ASSERT_EQUAL(std::string(".bak"), Path("a.c.bak").extension());
	CPPUNIT_ASSERT_EQUAL(std::string(""), Path("a").extension());
	CPPUNIT_ASSERT_EQUAL(std::string(""), Path("/a/b/cd").extension());
	CPPUNIT_ASSERT_EQUAL(std::string(".c"), Path("/a.x/b.c").extension());
	CPPUNIT_ASSERT_EQUAL(std::string("."), Path("a.").extension());
	CPPUNIT_ASSERT_EQUAL(std::string(".c"), Path("a....c").extension());
}

void PathUnit::testStem()
{
	CPPUNIT_ASSERT_EQUAL(std::string("abc"), Path("abc.c").stem());
	CPPUNIT_ASSERT_EQUAL(std::string(".abc"), Path("/a/b/.abc").stem());
	CPPUNIT_ASSERT_EQUAL(std::string(".abc"), Path("/a/.abc.xyz").stem());
	CPPUNIT_ASSERT_EQUAL(std::string("a"), Path("a.c").stem());
	CPPUNIT_ASSERT_EQUAL(std::string(""), Path("").stem());
}

void PathUnit::testAbs()
{
	CPPUNIT_ASSERT_EQUAL(Path("abc").abs(), false);
	CPPUNIT_ASSERT_EQUAL(Path("").abs(), false);
	CPPUNIT_ASSERT_EQUAL(Path("a/b/c/fas").abs(), false);
	CPPUNIT_ASSERT_EQUAL(Path("/a/bc").abs(), true);
	CPPUNIT_ASSERT_EQUAL(Path("/a").abs(), true);
	CPPUNIT_ASSERT_EQUAL(Path("/").abs(), true);

	Path	p1("abc");
	Path	p2(p1.makeAbs());
	CPPUNIT_ASSERT_EQUAL(p2.abs(), true);
	CPPUNIT_ASSERT_EQUAL(p1.abs(), false);
}

void PathUnit::testJoin()
{
	Path	p1("abc");
	Path	p2("def");

	CPPUNIT_ASSERT_EQUAL(Path("abc/def"), p1.join(p2));
	CPPUNIT_ASSERT_EQUAL(p1.join(p2).abs(), false);

	std::vector<std::string>	paths;
	CPPUNIT_ASSERT_EQUAL(p1, p1.join(paths));
	paths.push_back("a");
	paths.push_back("b");
	paths.push_back("c");
	CPPUNIT_ASSERT_EQUAL(Path("abc/a/b/c"), p1.join(paths));
	p1 = p1.makeAbs();
	CPPUNIT_ASSERT_EQUAL(Path("/abc/a/b/c"), p1.join(paths));
}

void PathUnit::testRules()
{
	PathRules *	rules = &UnixRules::rules;
	PathRules *	old;
	/*
	 * We don't know what pathrules is currently
	 * set to, so save the old ones which gets
	 * restored later.  Set the current rules to NULL
	 */
	old = Path::setDefaultPathRules(0);

	/*
	 * 
	 */
	Path		p1;
	CPPUNIT_ASSERT(Path::defaultPathRules() != 0);
	CPPUNIT_ASSERT(p1.rules() == Path::defaultPathRules());
	p1 = Path(rules);
	CPPUNIT_ASSERT(p1.rules() == rules);
	p1 = Path();
	CPPUNIT_ASSERT(p1.rules() == Path::defaultPathRules());

	old = Path::setDefaultPathRules(old);
}

void PathUnit::testGetcwd()
{
    Path    p = Path::getcwd();
    CPPUNIT_ASSERT(p.abs());
}