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

#include <vector>
#include <string>
#include <iosfwd>

// Forward dclaration defined in Path.cpp
class PathExtra;

/**
 * A Path is an arbitrary string used to represent a path to a file
 * or directory.  The operations on a Path make no attempt to validate
 * if the file or directory actually exists. 
 * 
 * You can operate on a Path with some common operations such as join(),
 * extension(), split(), dirname(), basename(), last().  All such operations 
 * happen without worrying about the result being a Path to a valid
 * file or directory.  See the Node class to handle actual files and
 * directories.
 * 
 */
class Path
{
public:
	/// Default constructory
	Path(const PathRules *rules = 0);
	/// Constructor from std::string
    Path(const std::string &path);
    /// Constructor from std::string with non-default PathRules
	Path(const std::string &path, const PathRules *rules);
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
	Path basename() const;
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

	/// Concatenate this and Path
	Path join(const Path &path) const;
	/// Concatenate vector of strings with each as a component.
	Path join(const std::vector<std::string> &strings) const;
	/// Return each directory component as a Path.
	std::vector<Path> split();

	/// Check if raw names are the same	
	bool operator==(const Path &op2) const;
	/// Check if raw names are different.
	bool operator!=(const Path &op2) const;


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
	/// Convert m_path into Cannonical or using existing one
	const Cannonical &cannon() const;
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

};

/// Print out the path
std::ostream &operator<<(std::ostream &out, const Path&path);
#endif // !defined(_PATH_PATH_H_)
