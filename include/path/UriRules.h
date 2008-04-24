/**  
 * @file UriRules.h
 */
#if !defined(_PATH_URIRULES_H_)
#define _PATH_URIRULES_H_

#include <path/PathRules.h>
#include <string>

namespace path {
    // Forward declarations
    class Canonical;
    class Path;
    
    class UriRules : public PathRules
    {
        
    public:
        UriRules();
        virtual ~UriRules();
        
        virtual Canonical canonical(const std::string &path) const;
        virtual std::string quote(const std::string & subdirs) const;
        
    };
}
#endif // !defined(_PATH_URIRULES_H_)
