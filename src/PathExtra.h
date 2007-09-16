#ifndef _PATH_PATHEXTRA_H_
#define _PATH_PATHEXTRA_H_
#include <string>

// Forward declarations
class Path;
class PathRules;

/**
 * This exists entirely to make a Path be smaller and simpler
to 
 * insure binaryu compatibility.  The typical Path
 * class is just a string.  But we can cache some
 * extra information such as the normalized path
 * or if it is an absolute path.  We create the
 * extra info on the fly as it is needed.
 */
class PathExtra
{
private:
	friend class Path;

	/// Default constructor
	PathExtra();
	/// Destructor
	~PathExtra();

	/// Normalized version of this path
	std::string		m_normpath;
	/// Is this an absolute path name
	bool			m_abs;
	/// If other then the default rules are used.
	PathRules *		m_rules;
};
#endif /* _PATH_PATHEXTRA_H_ */
