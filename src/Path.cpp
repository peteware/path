/**
 * @file Path.cpp
 *
 * Implementation of the Class Path
 *  Created on:      11-May-2007 5:09:31 PM
 *  Original author: Pete Ware
 */
#include "Path.h"


Path::~Path()
{
}

Path::Path(const std::string path)
{
}

/**
 * Initialize an empty Path
 */
Path::Path()
{
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
 * Returns the last component of the path.
 * 
 * For example, basename('/a/b/c') returns 'c'.  basename('/a/b/') returns an
 * empty Path.
 * 
 * This ia analogous to the Unix shell utility "basename"..
 */
Path Path::basename() const
{
	return Path();
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
	return Path();
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
	return  std::string();
}


/**
 * Return the current working directory as an absolute path.
 */
Path Path::getcwd()
{
	return Path();
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
 * Return the last component of the path.
 * 
 * For example, '/a/b/c' returns 'c'.  '/a' returns 'a'.  Finally, '/' returns '/'
 * (and it is absolute) and 'a' returns 'a'.
 */
Path Path::last() const
{
	return Path();
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
	return std::string();
}


Path & Path::operator=(const Path &op)
{
	return *this;
}


bool Path::operator==(const std::string & op2) const
{
	return  NULL;
}


/**
 * Return the path as a string.
 * 
 * All ~ expansions and environment variables (e.g. $HOME) occur.
 * 
 * See alsl normpath() which does the same but cleans things up a little more and
 * str() which returns the raw path being used.
 */
std::string Path::path() const
{
	return std::string();
}


/**
 * Return the PathRules used by the String.
 */
PathRules *Path::pathRules() const
{
	return  NULL;
}


/**
 * Return path with components quoted to escape shell expansion.  Note that
 * characters such as "$" are quoted since they are special to the shell.  In
 * other words, you may want to use normpath() to expand environment variables
 * before using this:
 * 
 * @code
 * Path p1("$HOME/file 2");
 * Path p2(p1.normpath());
 * p2 = p2.quote();
 * assert(p2.str() == "/home/ware/file\\ 2");
 * @endcode
 */
#ifdef notdef
std::string Path::quote(QuoteStyle style)
{
	return  NULL;
}


/**
 * Use list of directors to find name.
 */
Node Path::search(std::vector<Path> dirs, Path name)
{
	return  NULL;
}
#endif

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
 * Sets the default path rules to be used by any newly created Path objects.
 * 
 * This shold be done at compile time to match the operations on the system.
 */
void Path::setDefaultPathRules(PathRules * rules)
{

}


/**
 * Setting the path rules can change the path.  For example, '/a/b/c' might get
 * changed to '\a\b\c'
 */
void Path::setPathRules(PathRules *rules)
{
}


/**
 * Change the path.
 */
void Path::setString(const std::string & path)
{
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


std::vector<Path> Path::split(const std::string &dirs)
{	
	return std::vector<Path>();
}