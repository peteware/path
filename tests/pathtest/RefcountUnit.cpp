/**
 * @file RefcountUnit.cpp
 * @ingroup PathTest
 */
#include <path/Refcount.h>

#include <cppunit/TestCase.h>
#include <cppunit/extensions/HelperMacros.h>

using namespace path;

class RefcountUnit: public CppUnit::TestCase
{
	CPPUNIT_TEST_SUITE(RefcountUnit);
    
	CPPUNIT_TEST(init);
    CPPUNIT_TEST(deref);
    
	CPPUNIT_TEST_SUITE_END();

    class TestCount
    {
    public:
        static int s_count;
        TestCount() {
            ++s_count;
        }
        ~TestCount()
        {
            --s_count;
        }
        
        int count()
        {
            return s_count;
        }
    };
    /// Make declaring Refcount pointer for testing easier
    typedef Refcount<TestCount> TPtr;
protected:
	/// Test basic initialization
	void init();
    /// Test dereferencing operations
    void deref();
};

int RefcountUnit::TestCount::s_count;

CPPUNIT_TEST_SUITE_REGISTRATION(RefcountUnit);

void RefcountUnit::init()
{
    
	Refcount<int>       a;
    CPPUNIT_ASSERT_EQUAL(0, a.count());
    {
        TPtr            ref(new TestCount);
        CPPUNIT_ASSERT_EQUAL(1, ref.count());
        CPPUNIT_ASSERT_EQUAL(1, TestCount::s_count);
        {
            TPtr ref2(ref);
            CPPUNIT_ASSERT_EQUAL(1, TestCount::s_count);
        }
        CPPUNIT_ASSERT_EQUAL(1, TestCount::s_count);
    }
    CPPUNIT_ASSERT_EQUAL(0, TestCount::s_count);
}

void RefcountUnit::deref()
{
    TPtr    ref(new TestCount);
    
    CPPUNIT_ASSERT_EQUAL(1, ref->count());
    TestCount &d = *ref;
    CPPUNIT_ASSERT_EQUAL(1, ref->count());
    CPPUNIT_ASSERT_EQUAL(1, d.count());
}
