/**  
 * @file UnixRules.h
 */
#if !defined(_PATH_UNIXRULES_H_)
#define _PATH_UNIXRULES_H_

#include <path/PathRules.h>

namespace path {
    /**
     * @class UnixRules path/UnixRules.h
     * Implement PathRules for Unix like pathnames.
     */
    class UnixRules : public PathRules
    {
    public:
        UnixRules();
        virtual ~UnixRules();
        
        virtual Canonical   canonical(const std::string &path) const;
        virtual std::string quote(const std::string & path) const;
        virtual std::string unquote(const std::string &subdir) const;
        
        static UnixRules	rules;
        
    };
}
#endif // !defined(_PATH_UNIXRULES_H_)
