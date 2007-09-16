/**
 * @file Path.cpp
 *
 * Implementation of the Class Path
 *  Created on:      11-May-2007 5:09:31 PM
 *  Original author: Pete Ware
 */
#include "Path.h"
#include "PathExtra.h"
#include "UnixRules.h"

#include <iostream>

PathRules * Path::s_defaultPathRules;

/**
 * Initialize an empty Path
 */
Path::Path(PathRules *rules)
	: m_path(),
	  m_rules(rules),
	  m_extra(0)
{
}

/**
 * Set path to a raw string.
 * This may contain environment variables, "~",
 * multiple directory seperators, etc.  Use
 * str() to get this raw version back.  Use
 * path() to get it back as usable filename 
 * and finally use normpath() to get it back
 * in a cleaned up form.
 */
Path::Path(const std::string &path, PathRules *rules)
	: m_path(path),
	  m_rules(rules),
	  m_extra(0)
{
}

/**
 * Copy the m_path, make m_rules the same (pointer copy)
 * and duplicate the m_extra.
 */
Path::Path(const Path &copy)
	: m_path(copy.m_path),
	  m_rules(copy.m_rules),
	  m_extra(0)
{
	if (copy.m_extra)
	{
		m_extra = new PathExtra (*copy.m_extra);
	}
}

/**
 * Delete m_extra
 */
Path::~Path()
{
	delete m_extra;
}

/**
 * Do the assignment.
 */
Path & Path::operator=(const Path &op)
{
	if (this != &op) 
	{
		m_path = op.m_path;
		m_rules = op.m_rules;
		delete m_extra;
		if (op.m_extra)
		{
			m_extra = new PathExtra(*op.m_extra);
		}
		else
		{
			m_extra = 0;
		}
	}
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
	return m_path;
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
	return m_path;
}

/**
 * Returns the last component of the path.
 * 
 * For example, basename('/a/b/c') returns 'c'.  basename('/a/b/') returns an
 * empty Path.
 * 
 * This ia analogous to the Unix shell utility "basename"..
 */
Path Path::basename() const
{
	std::string::size_type start, index;
	std::string::size_type count;
	std::string::size_type end = std::string::npos;
	
	start = std::string::npos;
	for (index = 0, count = m_path.size(); index < count; ++index)
	{
		if (m_path[index] == '/')
			continue;
		start = index;
		for (end = index + 1; end < count; ++end)
		{
			if (m_path[end] == '/')
			{
				break;
			}
		}
		index = end;
	}
	if (start == std::string::npos) 
	{	// It's all "///"
		start = 0;
		end = 1;
	}
	std::string base = m_path.substr(start, end - start);
	return Path(base, m_rules);
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
	//std::string::size_type	index;
	int						index;
	std::string::size_type	end = std::string::npos;
	int						state = 0;

	std::cout << "START: " << m_path << std::endl;
	index = static_cast<int>(m_path.size()) - 1;
	while (index >= 0 && state != 3) 
	{
		std::cout << "\tstate = " << state
			<< " index = " << index
			<< " ch = " << m_path[index]
			<< std::endl;
		switch (state) 
		{
		case 0:
			/*
			 * Searching for the end with the '/' on end
			 */
			if (m_path[index] != '/') 
			{
				state = 1;
			}
			else 
			{
				--index;
			}
			break;
		case 1:
			/*
			 * We are at the end, past any terminating '/'
			 * and now we are searching the '/' that is for
			 * the directory
			 */
			if (m_path[index] == '/') 
			{
				state = 2;
			}
			else 
			{
				--index;
			}
			break;
		case 2:
			/**
			 * We've found the '/' for the directory and now
			 * need to remove any repeating /'s
			 */
			if (m_path[index] != '/') 
			{
				state = 3;
			}
			else 
			{
				--index;
			}
			end = index + 1;
			break;
		}
	}

	index = std::max (0, index);
	std::cout << "DONE: end = " << end;
	std::cout << "\tstate = " << state
		<< " index = " << index
		<< " ch = " << m_path[index]
		<< std::endl;
	if (state == 2)
	{
		return Path(m_path.substr(0, end));
	}
	else if (state == 3)
	{
		return Path (m_path.substr (0, end));
	}
	else
	{
		return Path(".");
	}
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
	std::string::size_type	index = m_path.find_last_of (".");
	if (index == std::string::npos)
		return "";
	else
		return m_path.substr (index, m_path.size() - index);
}

/**
 * Return basename() of path with the extension() removed
 * @code
 * Path	p("somepath.ext");
 * p.basename() == Path(p.stem() + p.extension());
 * @endcode
 */
std::string Path::stem() const
{
	return "";
}

/**
 * Returns true if this String represents an absolute path.
 * 
 * This affects how join() works.
 */
bool Path::abs() const 
{
	return false;
}

/**
 * Set if this is an absolute path or not.
 * 
 * An empty String is initially not an absolute path.  However, if you initialize
 * it with a path, then the PathRules is used to determine if that string makes it
 * an absolute path.
 * 
 * The return value is the previous value.
 */
bool Path::setAbs(bool absolute)
{
	return absolute;
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
	return  Path();
}


/**
 * Return a String by joining all the Strings in the vector.  All Strings must use
 * the same PathRules.
 * 
 * This is comparable to repeated calling join() with each component of the vector.
 *  Creating an empty String and then calling join() should do what you'd expect.
 * For example:
 * 
 * @code
 * String  path; // initialize this...
 * String  newPath;
 * 
 * newpath = String().join(path.split());
 * @endcode
 * 
 */
Path Path::join(const std::vector<std::string> &strings) const
{
	return Path();
}


/**
 * Returns each component of the path as an individual Path
 * 
 * If the path is abs(), then the first component is also abs().  Each component
 * shares the same PathRules.  String::join() should return an equivalent path.
 */
std::vector<Path> Path::split()
{
	return std::vector<Path>();
}
/**
 * Does a simple string comparison between two paths
 * to see if they are the same.  So while two paths
 * might be logically the same, "/a/b/.." is logically
 * the same, they will not compare equally.  See
 * normpath() as a way to make them compare the same
 * 
 * @param op2 The second argument to ==
 * @return True if the same, false otherwise.
 */
bool Path::operator==(const Path & op2) const
{
	return m_path == op2.m_path;
}

/**
 * Inverse of operator==()
 */
bool Path::operator!=(const Path &op2) const
{
	return m_path != op2.m_path;
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
 * it uses UnixRules::rules.
 *
 * Do not delete the returned rules!
 */
const PathRules *Path::rules() const
{
		if (m_rules)
			return m_rules;
		if (!s_defaultPathRules)
			s_defaultPathRules = &UnixRules::rules;
		return s_defaultPathRules;
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
 * Returns the default rules; maybe NULL.
 */
PathRules * Path::defaultPathRules()
{
	return s_defaultPathRules;
}

/**
 * Return the current working directory as an absolute path.
 */
Path Path::getcwd()
{
	return Path();
}

/**
 * Print's the raw form of the Path.  See normpath() 
 * to get a cleaner version of the Path.  
 */
std::ostream &operator<<(std::ostream &out, const Path&path)
{
	return out << path.path();
}
