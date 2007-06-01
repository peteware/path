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

#include "PathRules.h"
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
	Path(PathRules *rules = 0);
	/// Constructor from std::string
	Path(const std::string &path, PathRules *rules = 0);
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

	/// Return if this is an absolute path (not relative)
	bool abs() const;
	/// Indicate if this should be an absolute path
	bool setAbs(bool absolute);
	Path join(const Path &path) const;
	Path join(const std::vector<std::string> &strings) const;
	Path last() const;
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
	/// Use the rules if none are set.
	static PathRules *	s_defaultPathRules;
	/**
	 * The path as set.
	 * 
	 * This is the uninterpreted string and is the value returned by str().
	 */
	std::string		m_path;
	/// These are the rules we use for this path.
	PathRules *		m_rules;
	PathExtra *		m_extra;

};

/// Print out the path
std::ostream &operator<<(std::ostream &out, const Path&path);
#endif // !defined(_PATH_PATH_H_)
