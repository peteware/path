/**  
 * @file Path.h
 *
 * Implementation of the Class Path
 *
 * Created on:      11-May-2007 5:09:31 PM
 * Original author: Pete Ware
 */
#if !defined(EA_83FDBD0B_6FF5_4f92_B5DD_FE67283EDD84__INCLUDED_)
#define EA_83FDBD0B_6FF5_4f92_B5DD_FE67283EDD84__INCLUDED_

#include "PathRules.h"
#include <vector>
#include <string>

/**
 * A Path has no system component.  Essentially, it's an arbitrary string with the
 * only constraint is that it is valid whithn the constraints of it's pathRules().
 * 
 * 
 * You can operate on a Path with some common operations such as join(),
 * extension(), split().  All such operations happen without reference to actual
 * filenames.
 * 
 * The str() returns a std::string that is the current representation as
 * constrained by pathRules().
 * 
 * 
 */
class Path
{

public:
	virtual ~Path();

	Path(const std::string path);
	Path();
	bool abs() const;
	Path basename() const;
	Path dirname() const;
	std::string extension() const;
	static Path getcwd();
	Path join(const Path &path) const;
	Path join(const std::vector<std::string> &strings) const;
	Path last() const;
	std::string normpath() const;
	Path & operator=(const Path &op2);
	bool operator==(const std::string & op2) const;
	std::string path() const;
	PathRules *pathRules() const;
	//std::string quote(QuoteStyle style);
	//Node search(std::vector<Path> dirs, Path name);
	bool setAbs(bool absolute);
	void setDefaultPathRules(PathRules * rules);
	void setPathRules(PathRules *rules);
	void setString(const std::string & path);
	std::vector<Path> split();
	static std::vector<Path> split(const std::string &dirs);

private:
	/**
	 * The path as set.
	 * 
	 * This is the uninterpreted string and is the value returned by str().
	 */
	std::string m_path;
	/**
	 * Rules used for path manipulation
	 */
	PathRules *m_pathRules;

};
#endif // !defined(EA_83FDBD0B_6FF5_4f92_B5DD_FE67283EDD84__INCLUDED_)
