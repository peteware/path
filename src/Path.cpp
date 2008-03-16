/**
 * @file Path.cpp
 *
 * Implementation of the Class Path
 *  Created on:      11-May-2007 5:09:31 PM
 *  Original author: Pete Ware
 */
#include <path/Path.h>
#include <path/Cannonical.h>
#include <path/UnixRules.h>

#include <path/SysCalls.h>

#include <iostream>

PathRules * Path::s_defaultPathRules;

/**
 * Initialize an empty Path
 */
Path::Path(const PathRules *rules)
	: m_path(),
	  m_rules(rules),
	  m_cannon(0),
      m_pathStr(0)
{
}

/**
 * Initialize path, set rules to NULL (i.e. default)
 */
Path::Path(const char *path)
    : m_path(),
      m_rules(0),
      m_cannon(new Cannonical(path)),
      m_pathStr(0)
{
    m_path = rules()->join(*m_cannon);
}

/**
 * Initialize path, set rules to NULL (i.e. default)
 */
Path::Path(const std::string &path)
    : m_path(),
      m_rules(0),
      m_cannon(new Cannonical(path)),
      m_pathStr(0)
{
    m_path = rules()->join(*m_cannon);
}

/**
 * Create a path from a Cannonical and a PathRules.
 *
 * Initialized m_path by converting from Canonical to a string
 * via the PathRules
 */
Path::Path(const Cannonical &cannon, const PathRules *param_rules)
    : m_path(),
      m_rules(param_rules),
      m_cannon(new Cannonical(cannon)),
      m_pathStr(0)
{
    m_path = rules()->join(cannon);
}

/**
 * Copy the m_path, make m_rules the same (pointer copy)
 * and duplicate the m_cannon.
 */
Path::Path(const Path &copy)
	: m_path(copy.m_path),
	  m_rules(copy.m_rules),
	  m_cannon(0),
      m_pathStr(0)
{
	if (copy.m_cannon)
		m_cannon = new Cannonical (*copy.m_cannon);
    if (copy.m_pathStr)
        m_pathStr = new std::string(*copy.m_pathStr);
}

/**
 * Delete m_cannon
 */
Path::~Path()
{
	delete m_cannon;
    delete m_pathStr;
}

/**
 * Do the assignment.
 */
Path & Path::operator=(const Path &op)
{
    if (this == &op)
        return *this;
    m_path = op.m_path;
    m_rules = op.m_rules;

    delete m_cannon;
    if (op.m_cannon)
        m_cannon = new Cannonical(*op.m_cannon);
    else
        m_cannon = 0;

    delete m_pathStr;
    if (op.m_pathStr)
        m_pathStr = new std::string(*op.m_pathStr);
    else
        m_pathStr = 0;
    
	return  *this;
}

/**
 * The raw, uninterpreted string is returned.
 * Use normpath() to get an expanded, clean path and
 * path() to get an expanded but without duplicate
 * directory seperators or ".." collapsed.
 */
const std::string &Path::str() const
{
	return m_path;
}

/**
 * Return the path as a string.
 * 
 * All ~ expansions and environment variables (e.g. $HOME) occur.
 * 
 * See also normpath() which does the same but cleans things up a little more and
 * str() which returns the raw path being used.
 */
const std::string& Path::path() const
{
    if (m_pathStr)
        return *m_pathStr;
    m_pathStr = new std::string(rules()->join(cannon()));
	return *m_pathStr;
}

/**
 * Normalized the path and returns it as a std::string.
 * 
 * This removes any duplicate path seperators, collapses parent directory
 * references, expands any ~ references and any environment variables (e.g. $HOME).
 * 
 * 
 * See also str() which returns the path in it's raw form and path() which does ~
 * and environment variable expansion but does not try to clean up the path.
 */
std::string Path::normpath() const
{
	return path();
}

/**
 * Returns the last component of the path.
 * 
 * For example, basename('/a/b/c') returns 'c'.  basename('/a/b/') returns 'b' 
 * This is analogous to the Unix shell utility "basename".
 */
std::string Path::basename() const
{
    const Strings &components = cannon().components();

    if (components.size() == 0)
    {
        return std::string();
    }
    else
    {
        return components[components.size() - 1];
    }
}

/**
 * Returns the directory component of Path.
 * 
 * dirname('/a/b/c') returns '/a/b'.  You just be able to do
 * 
 * @code
 * Path p1('/a/b/c');
 * Path p2;
 * 
 * p2 = p1.join(p1.basename()));
 * assert(p1 == p2);
 * @endcode
 */
Path Path::dirname() const
{
    Strings::const_iterator last;  // end elements
    last = cannon().components().end();
    if (cannon().components().size() > 0)
        --last;
    Strings com(cannon().components().begin(), last);

    Cannonical  c(cannon(), com);
    return Path(c, m_rules);
}


/**
 * Return the extension or suffix on a path.  For example:
 * 
 * @code
 * String path("/a/file.h")
 * std::string suffix = path.extension()
 * std::cout << suffix << std::endl;
 * @endcode
 * Would print out ".h"
 * 
 * If there is no extension (anything after the last '.'), then an empty string is
 * returned.
 * 
 */
std::string Path::extension() const
{
    Path    last = basename();
	std::string::size_type	index = last.m_path.find_last_of (".");
	if (index == std::string::npos)
		return "";
	else
		return last.m_path.substr (index, last.m_path.size() - index);
}

/**
 * Return basename() of path with the extension() removed
 * @code
 * Path	p("/a/b/name.ext");
 * p.basename() == "name"; 
 * @endcode
 * @code
 * Path p2("/a/b/.name");
 * p2.stem() == ".name";
 * @endcode
 */
std::string Path::stem() const
{
	Path	base = basename();
	std::string::size_type	index = base.m_path.find_last_of (".");
	if (index == std::string::npos)
		return base.m_path;
	else if (index == 0)
		return base.m_path;
	else
		return base.m_path.substr (0, index);
}

/**
 * Returns true if this String represents an absolute path.
 * 
 * This affects how join() works.
 */
bool Path::abs() const 
{
    return cannon().abs();
}

/**
 * Another alternative is to use Path::getcwd().join(path))
 * which might return something closer to what you expect.
 */
Path Path::makeAbs() const
{
    Cannonical  c (cannon());
    c.setAbs(true);
    return Path(c, m_rules);
}

/**
 * Return a Path by appending another path.  For example:
 * @code
 * Path	path1("/tmp");
 * Path path2("a/b/c");
 * Path path3 = path1.join(path2);
 * std::cout << path3 << std::endl;
 * @endcode
 * Would print out "/tmp/a/b/c"
 * @param path Append path to this and return a new copy
 * @return A new path.
 */
Path Path::join(const Path &path) const
{
	if (path.abs())
		return path;
    Cannonical c(cannon());
    std::copy(path.cannon().components().begin(),
              path.cannon().components().end(),
              std::back_inserter(c.components()));
    return Path (c, m_rules);
    //return rules()->convert(c);
}

/**
 * Return a Path by joining all the std::strings in the vector.
 * 
 * This is comparable to repeated calling join() with each component of the vector.
 *  Creating an empty String and then calling join() should do what you'd expect.
 * For example:
 * 
 * @code
 * std::string  str; // initialize this...
 * Path  path;
 * 
 * path = path.join(str.split());
 * @endcode
 * 
 */
Path Path::join(const Strings &strings) const
{
    
    Cannonical c(cannon());
    std::copy(strings.begin(), strings.end(),
              std::back_inserter(c.components()));
    return Path(c, m_rules);
}

Path Path::add(const std::string &p) const
{
    Cannonical c(cannon());
    c.add(p);
    return Path(c, m_rules);
}

/**
 * Returns each component of the path as an individual Path
 * 
 * If the path is abs(), then the first component is also abs().  Each component
 * shares the same PathRules.  String::join() should return an equivalent path.
 */
std::vector<Path> Path::split() const
{
    const Cannonical &      c = cannon();
    std::vector<Path>       paths;
    bool                    first = true;
    
    for (Strings::const_iterator iter = c.components().begin();
         iter != c.components().end(); ++iter)
    {
        Path    p (*iter, rules());
        if (first && abs())
        {
            p = p.makeAbs();
        }
        first = false;
        paths.push_back(p);
    }
	return paths;
}

/**
 * Return the PathRules used by the Path.  May
 * be NULL.  Do not delete the returned rules.
 */
const PathRules *Path::pathRules() const
{
	return m_rules;
}

/**
 * Returns a default set of rules.  If the rules
 * are not set, it uses the default rules.  If
 * the default rules have not been initialized,
 * it uses UnixRules::rules (as returned by
 * defaultPathRules()).
 *
 * Do not delete the returned rules!
 */
const PathRules *Path::rules() const
{
	if (m_rules)
		return m_rules;
	else
		return defaultPathRules();
}


/**
 * Sets the default path rules to be used by any newly created Path objects.
 * 
 * This should be done at compile time to match the operations on the system.
 */
PathRules * Path::setDefaultPathRules(PathRules * rules)
{
	std::swap(rules, s_defaultPathRules);
	return rules;
}

/**
 * Returns the default rules; never NULL.
 *
 * Uses UnixRules::rules as the default value.
 */
PathRules * Path::defaultPathRules()
{
	if (!s_defaultPathRules)
		s_defaultPathRules = &UnixRules::rules;
	return s_defaultPathRules;
}

/**
 * Return the current working directory as an absolute path.
 */
Path Path::getcwd()
{
    PathRules   *r = defaultPathRules();
	return Path(r->cannonical(SysCalls().getcwd()), r);
}

/**
 * Returns the cannonical representation of this path.
 *
 * If the result has not already been determined, it
 * is calculated.
 */
const Cannonical & Path::cannon() const
{
	if (!m_cannon)
	{
		m_cannon = new Cannonical(rules()->cannonical(m_path));
	}
	return *m_cannon;
}

/**
 * Compares the PathRules and Cannonical componenets
 * to see if they are the same.  So while two paths
 * might be logically the same, "a" and "/a/b/.." are logically
 * the same, they will not compare equally.  See
 * normpath() as a way to make them compare the same
 * 
 * @param op2 The second argument to ==
 * @return True if the same, false otherwise.
 */
bool operator==(const Path &op1, const Path & op2)
{
    bool r = (op1.rules() == op2.rules());
    bool c = (op1.cannon() == op2.cannon());
    return r && c;
}

/**
 * Inverse of operator==()
 */
bool operator!=(const Path &op1, const Path &op2)
{
	return !(op1 == op2);
}

/**
 * Print's the raw form of the Path.  See normpath() 
 * to get a cleaner version of the Path.  
 */
std::ostream &operator<<(std::ostream &out, const Path&path)
{
	return out << path.path();
}

/**
 * Add another directory to path and return a new one
 *
 * @param path The path to add to
 * @param dir The directory to add to path
 * @return A new Path
 */
Path operator+(const Path &path, const std::string &dir)
{
    return path.add(dir);
}
