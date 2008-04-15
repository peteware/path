/**  
 * @file UnixRules.h
 *
 * Implementation of the Class UnixRules
 *
 * Created on:      11-May-2007 5:09:33 PM
 * Original author: Pete Ware
 */
#if !defined(_PATH_UNIXRULES_H_)
#define _PATH_UNIXRULES_H_

#include <path/PathRules.h>
namespace path {
    // Forward declarations
    class Path;
    class Canonical;
    
    class UnixRules : public PathRules
    {
    public:
        UnixRules();
        virtual ~UnixRules();
        
        virtual Canonical canonical(const std::string &path) const;
        virtual std::string quote(const std::string & path) const;
        
        static Canonical   canon(const std::string &path);
        static UnixRules	rules;
        
    };
}
#endif // !defined(_PATH_UNIXRULES_H_)
