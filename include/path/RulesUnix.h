/**
 * @file RulesUnix.h
 */
#if !defined(_PATH_RULESUNIX_H_)
#define _PATH_RULESUNIX_H_

#include <path/RulesBase.h>

namespace path {
/**
 * @class RulesUnix path/RulesUnix.h
 * Implement RulesBase for Unix like pathnames.
 */
class RulesUnix : public RulesBase
{
public:
    RulesUnix();
    virtual ~RulesUnix();

    virtual Canonical   canonical(const std::string &path) const;
    virtual bool quote(const std::string &subdir, std::string *dest) const;
    virtual bool unquote(const std::string &subdir, std::string *dest) const;

    static RulesUnix        rules;

};
}
#endif // !defined(_PATH_RULESUNIX_H_)
