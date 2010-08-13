/**
 * @file UriRules.h
 */
#if !defined(_PATH_URIRULES_H_)
#define _PATH_URIRULES_H_

#include <path/PathRules.h>

namespace path {

/**
 * @class UriRules path/UriRules.h
 * Handle URI's rules.
 */
class UriRules : public PathRules
{

public:
    UriRules();
    virtual ~UriRules();

    virtual Canonical canonical(const std::string &path) const;
    virtual bool quote(const std::string & subdirs, std::string *dest) const;

};
}
#endif // !defined(_PATH_URIRULES_H_)
