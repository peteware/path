/**
 * @file RulesBaseUnit.cpp
 * @ingroup PathTest
 */
#include <path/RulesBase.h>
#include <path/RulesUnix.h>
#include <path/Canonical.h>
#include <path/Path.h>

#include "RulesBaseUnit.h"
using namespace path;

CPPUNIT_TEST_SUITE_REGISTRATION(RulesBaseUnit);
void RulesBaseUnit::setUp()
{
	m_rules = new RulesUnix;
}
void RulesBaseUnit::tearDown()
{
    delete m_rules;
}

/// Set the rules and returns the previous one
RulesBase * RulesBaseUnit::setRules (RulesBase *rules)
{
    std::swap(m_rules, rules);
    return rules;
}

/// Return the rules
RulesBase *RulesBaseUnit::rules() const
{
    return m_rules;
}

/**
 * Check basic initialization.
 */
void RulesBaseUnit::init()
{
	RulesUnix	unix_rules;
}

void RulesBaseUnit::canonical()
{
	RulesUnix	unix_rules;
	Canonical	canon = unix_rules.canonical("/a/b/c");

	CPPUNIT_ASSERT(canon.protocol().empty());
	CPPUNIT_ASSERT(canon.host().empty());
	CPPUNIT_ASSERT(canon.extra().empty());
	CPPUNIT_ASSERT_EQUAL(std::string("a"), canon.components()[0]);
	CPPUNIT_ASSERT_EQUAL(std::string("b"), canon.components()[1]);
	CPPUNIT_ASSERT_EQUAL(std::string("c"), canon.components()[2]);
	CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(3), canon.components().size());
	CPPUNIT_ASSERT_EQUAL(true, canon.abs());
	
	canon = unix_rules.canonical("");
	CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(0), canon.components().size());
	CPPUNIT_ASSERT_EQUAL(false, canon.abs());

	canon = unix_rules.canonical("///");
	CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(0), canon.components().size());
	CPPUNIT_ASSERT_EQUAL(true, canon.abs());
	
	canon = unix_rules.canonical("a");
	CPPUNIT_ASSERT_EQUAL(std::string("a"), canon.components()[0]);
	CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(1), canon.components().size());
	CPPUNIT_ASSERT_EQUAL(false, canon.abs());

	canon = unix_rules.canonical("ab/cd/");
	CPPUNIT_ASSERT_EQUAL(std::string("ab"), canon.components()[0]);
	CPPUNIT_ASSERT_EQUAL(std::string("cd"), canon.components()[1]);
	CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(2), canon.components().size());
	CPPUNIT_ASSERT_EQUAL(false, canon.abs());
}

void RulesBaseUnit::convert()
{
	Canonical	canon;
	RulesUnix	rules;
	Path		path (canon, &rules);

	CPPUNIT_ASSERT_EQUAL(std::string(""), path.str());
	CPPUNIT_ASSERT(!path.abs());
	
	canon.add("a");
	canon.add("b");

	path = Path(canon, &rules);

	CPPUNIT_ASSERT_EQUAL(std::string("a/b"), path.str());
	CPPUNIT_ASSERT(!path.abs());

	canon.setAbs(true);
	path = Path(canon, &rules);
	CPPUNIT_ASSERT_EQUAL(std::string("/a/b"), path.str());
	CPPUNIT_ASSERT(path.abs());
}
