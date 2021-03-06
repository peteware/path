/**
 * @file RulesBase.h
 */
#if !defined(_PATH_RULESBASE_H_)
#define _PATH_RULESBASE_H_

#include <path/Strings.h>
#include <string>

namespace path {
// Forward declarations
class Canonical;

/**
 * @class RulesBase path/RulesBase.h
 * Defines an interface for manipulating Path components.
 *
 * For example, the difference between using a forward slash between
 * directories (Unix) for backward slash (Win32) is encapsulating
 * here.  Characters that are special can be quoted by the
 * implementation.
 *
 * Mostly, this is about converting between a std::string
 * and Canonical objects.
 */
class RulesBase
{
public:
    RulesBase(char sep);
    virtual ~RulesBase();

    /// Convert Canonical into a string
    virtual std::string str(const Canonical &canononical) const;
    /// Convert a raw path (aka a string) into Canonical
    virtual Canonical canonical(const std::string &path) const = 0;
    /// Quote an element of path
    virtual bool quote(const std::string &subdir, std::string *dest) const = 0;
    /// Unquote (dequote?) an element of path
    virtual bool unquote(const std::string &subdir, std::string *dest) const = 0;
protected:
    char            m_sep;                                                  ///< Seperator
};
}
#endif // !defined(_PATH_RULESBASE_H_)
