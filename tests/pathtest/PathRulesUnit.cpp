#include <path/PathRules.h>
#include <path/UnixRules.h>
#include <path/Cannonical.h>
#include <path/Path.h>

#include "PathRulesUnit.h"

CPPUNIT_TEST_SUITE_REGISTRATION(PathRulesUnit);
void PathRulesUnit::setUp()
{
    if (!m_rules)
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

void PathRulesUnit::cannonical()
{
	UnixRules	unix_rules;
	Cannonical	cannon = unix_rules.cannonical("/a/b/c");

	CPPUNIT_ASSERT(cannon.protocol().empty());
	CPPUNIT_ASSERT(cannon.host().empty());
	CPPUNIT_ASSERT(cannon.extra().empty());
	CPPUNIT_ASSERT_EQUAL(std::string("a"), cannon.components()[0]);
	CPPUNIT_ASSERT_EQUAL(std::string("b"), cannon.components()[1]);
	CPPUNIT_ASSERT_EQUAL(std::string("c"), cannon.components()[2]);
	CPPUNIT_ASSERT_EQUAL(3UL, cannon.components().size());
	CPPUNIT_ASSERT_EQUAL(true, cannon.abs());
	
	cannon = unix_rules.cannonical("");
	CPPUNIT_ASSERT_EQUAL(0UL, cannon.components().size());
	CPPUNIT_ASSERT_EQUAL(false, cannon.abs());

	cannon = unix_rules.cannonical("///");
	CPPUNIT_ASSERT_EQUAL(0UL, cannon.components().size());
	CPPUNIT_ASSERT_EQUAL(true, cannon.abs());
	
	cannon = unix_rules.cannonical("a");
	CPPUNIT_ASSERT_EQUAL(std::string("a"), cannon.components()[0]);
	CPPUNIT_ASSERT_EQUAL(1UL, cannon.components().size());
	CPPUNIT_ASSERT_EQUAL(false, cannon.abs());

	cannon = unix_rules.cannonical("ab/cd/");
	CPPUNIT_ASSERT_EQUAL(std::string("ab"), cannon.components()[0]);
	CPPUNIT_ASSERT_EQUAL(std::string("cd"), cannon.components()[1]);
	CPPUNIT_ASSERT_EQUAL(2UL, cannon.components().size());
	CPPUNIT_ASSERT_EQUAL(false, cannon.abs());
}

void PathRulesUnit::convert()
{
	Cannonical	cannon;
	UnixRules	rules;
	Path		path = rules.convert(cannon);

	CPPUNIT_ASSERT_EQUAL(std::string(""), path.str());
	CPPUNIT_ASSERT(!path.abs());
	
	cannon.add("a");
	cannon.add("b");

	path = rules.convert(cannon);

	CPPUNIT_ASSERT_EQUAL(std::string("a/b"), path.str());
	CPPUNIT_ASSERT(!path.abs());

	cannon.setAbs(true);
	path = rules.convert(cannon);
	CPPUNIT_ASSERT_EQUAL(std::string("/a/b"), path.str());
	CPPUNIT_ASSERT(path.abs());
}
