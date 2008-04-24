/**
 * @file PathRulesUnit.cpp
 * @ingroup PathTest
 */
#include <path/PathRules.h>
#include <path/UnixRules.h>
#include <path/Canonical.h>
#include <path/Path.h>

#include "PathRulesUnit.h"
using namespace path;

CPPUNIT_TEST_SUITE_REGISTRATION(PathRulesUnit);
void PathRulesUnit::setUp()
{
	m_rules = new UnixRules;
}
void PathRulesUnit::tearDown()
{
    delete m_rules;
}

/// Set the rules and returns the previous one
PathRules * PathRulesUnit::setRules (PathRules *rules)
{
    std::swap(m_rules, rules);
    return rules;
}

/// Return the rules
PathRules *PathRulesUnit::rules() const
{
    return m_rules;
}

/**
 * Check basic initialization.
 */
void PathRulesUnit::init()
{
	UnixRules	unix_rules;
}

void PathRulesUnit::canonical()
{
	UnixRules	unix_rules;
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

void PathRulesUnit::convert()
{
	Canonical	canon;
	UnixRules	rules;
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
