/**
 * @file RulesWin32.h
 */
#if !defined(_PATH_RULESWIN32_H_)
#define _PATH_RULESWIN32_H_

#include <path/RulesBase.h>

namespace path {
/**
 * @class RulesWin32 path/RulesWin32.h
 * Implements the Windows path rules
 * (Not yet implemented)
 */
class RulesWin32 : public RulesBase
{

public:
    RulesWin32();
    virtual ~RulesWin32();

    static RulesWin32    rules;

    virtual Canonical canonical(const std::string &path) const;
    virtual bool quote(const std::string & path, std::string *dest) const;
    virtual bool unquote(const std::string &subdir, std::string *dest) const;
};
}
#endif // !defined(_PATH_RULESWIN32_H_)
