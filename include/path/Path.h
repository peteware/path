/**  
 * @file Path.h
 *
 * Implementation of the Class Path
 *
 * Created on:      11-May-2007 5:09:31 PM
 * Original author: Pete Ware
 */
#if !defined(_PATH_PATH_H_)
#define _PATH_PATH_H_

#include <path/PathRules.h>
#include <path/Strings.h>

#include <vector>
#include <string>
#include <iosfwd>

/**
 * A Path is an arbitrary string used to represent a path to a file
 * or directory.  The operations on a Path make no attempt to validate
 * if the file or directory actually exists. 
 * 
 * You can operate on a Path with some common operations such as add(),
 * extension(), split(), dirname(), basename(), last().  All such operations 
 * happen without worrying about the result being a Path to a valid
 * file or directory.  See the Node class to handle actual files and
 * directories.
 *
 * The primary purpose of using a Path instead of a string is
 * to encourage operating system independence.   To support
 * the Node class (represnting actual files and directories), the
 * Path class is defined with value semantics.  This means to change
 * something a copy is created.  This what the
 * Node class can derive from Path and maintain it's
 * own semantics.  For example, it doesn't make sense
 * to change a Node's suffix().
 *
 * The choice made in this design is that a Path manipulates a Cannonical
 * representation of a path.  The unfortunate side affect is
 * it's difficult to just use a string to create a Path and you must
 * be explicit about the rules you want to use when initializing
 * a Path.  For example
 *
 * @code
 * Path     path1(UnixPath("/a/b/c"));
 * Path     path2(Win32Path("\\a\\b\\c"));
 * @endcode
 * 
 * Result in two identical paths.
 *
 * UnixPath() and Win32Path() take strings and return a Cannonical
 * object for that set of rules.
 *
 * To make things easier, the Cannonical class design has most
 * methods returning a reference to the Cannonical object so you can chain
 * several operations together (this is antithesis
 * of how the Path class works).  For example:
 *
 * @code
 * Path     path1(UnixPath("a").setAbs(true).setDrive("C"));
 * Path     path2(Win32Path("C:\\a"));
 * @endcode
 *
 * Result in two identical paths.
 *
 * @sa 
 * Cannonical, PathRules, UnixRules, Wn32Rules, UriRules, Win32Path, 
 * UnixPath.
 */
class Path
{
public:
	/// Default constructory
	Path(const PathRules *rules = 0);
	/// Constructor from std::string
    Path(const std::string &path);
    /// Use a Cannonical path and PathRules
    Path(const Cannonical &cannon, const PathRules *rules = 0);
    /// Construct from a NUL terminatd strin
    Path(const char *path);
	/// Copy constructor
	Path(const Path &copy);
	/// Destructor
	virtual ~Path();
	/// Assignment operator
	Path & operator=(const Path &op2);

	/// Return original string
	const std::string & str() const;
	/// Return original string
	const std::string & path() const;
	/// Return original string but cleaned up
	std::string normpath() const;


	/// Return the last component of Path
    std::string basename() const;
	/// Return the directory component of Path
	Path dirname() const;
	/// Return the filename extension
	std::string extension() const;
	/// Return without extension
	std::string stem() const;

	/// Return if this is an absolute path (not relative)
	bool abs() const;
	/// Return a new path by converting this one to an absolute path
	Path makeAbs() const;

    /// Return the drive letter (may be empty)
    const std::string &drive() const;
    /// Return the protocol (may be empty)
    const std::string &protocol() const;
    /// Return the host (may be empty)
    const std::string &host() const;
    /// Return the extra parameters
    const std::string &extra() const;
    
	/// Concatenate this and Path
	Path add(const Path &path) const;
	/// Concatenate vector of strings with each as a component.
	Path add(const Strings &strings) const;
    /// Concatenate a single string
    Path add(const std::string &p) const;
    /// Concatenate a NUL terminated string
    Path add(const char *p) const;
	/// Return each directory component as a Path.
	std::vector<Path> split() const;

	/// Return the Cannonical representation of the path
	const Cannonical &cannon() const;

	/// Return the rules (may be NULL)
	const PathRules *pathRules() const;
	/// Return PathRules, never null
	const PathRules *	rules() const;
	/// Set the default rules to be used by most paths
	static PathRules * setDefaultPathRules(PathRules * rules);
	/// Return the rules
	static PathRules * defaultPathRules();

	/// Return the current working directory
	static Path getcwd();

private:
	/// Use these rules if none are set.
	static PathRules *	s_defaultPathRules;
	/**
	 * The path as set.
	 * 
	 * This is the uninterpreted string and is the value returned by str().
	 */
	std::string		m_path;
	/// These are the rules we use for this path; may be NULL
	const PathRules *		m_rules;
	/// The path in cannonical form; may be NULL
	mutable Cannonical *m_cannon;
    /// Cached value path converted by path();
    mutable std::string *   m_pathStr;

};

/// Check if raw names are the same	
bool operator==(const Path &op1, const Path &op2);
/// Check if raw names are different.
bool operator!=(const Path &op1, const Path &op2);
/// Print out the path
std::ostream &operator<<(std::ostream &out, const Path&path);
/// Add a new directory
Path operator+(const Path &path, const std::string &dir);

// Shortcuts for handling different paths as strings
/// Convert a unix style path ("/a/b/c") to Cannonical
Cannonical UnixPath(const std::string &path);
/// Convert a Win32 style path ("C:\temp") to Cannonical
Cannonical Win32Path(const std::string &path);
/// Convert a URL style path ("http://www.peteware.com/a") to Cannonical
Cannonical URLPath(const std::string &path);
#endif // !defined(_PATH_PATH_H_)
