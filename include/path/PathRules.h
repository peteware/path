#if !defined(_PATH_PATHRULES_H_)
#define _PATH_PATHRULES_H_

#include <path/Strings.h>
#include <string>
#include <vector>

// Forward declarations
class Path;
class Cannonical;

/**
 * Defines an interface for manipulating Path components.
 *
 * For example, the difference between using a forward slash between
 * directories (Unix) for backward slash (Win32) is encapsulating
 * here.  Characters that are special can be quoted by the
 * implementation.  Finally, an implementation provides a way to
 * convert between path rules.
 *
 */
class PathRules
{
public:
	PathRules(char sep);
	virtual ~PathRules();

	/// Convert a raw path (aka a string) into Cannonical
	virtual Cannonical cannonical(const std::string &path) const = 0;
	/// Convert Cannonical into a Path
	virtual Path convert(const Cannonical &canonical) const;
	/// Quote an element of path
	virtual std::string quote(const std::string & subdir) const = 0;
    /// Convert Cannonical into a string
    virtual std::string add(const Cannonical &canononical) const;
protected:
	/// Split a string into it's components
	static void split(const std::string &path, char sep, Strings &subdirs);
protected:
	char		m_sep;							///< Seperator
};
#endif // !defined(_PATH_PATHRULES_H_)
