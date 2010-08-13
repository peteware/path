/**
 * @file RulesUri.h
 */
#if !defined(_PATH_RULESURI_H_)
#define _PATH_RULESURI_H_

#include <path/RulesBase.h>

namespace path {

/**
 * @class RulesUri path/RulesUri.h
 * Handle URI's rules.
 */
class RulesUri : public RulesBase
{

public:
    RulesUri();
    virtual ~RulesUri();

    virtual Canonical canonical(const std::string &path) const;
    virtual bool quote(const std::string & subdirs, std::string *dest) const;

};
}
#endif // !defined(_PATH_RULESURI_H_)
