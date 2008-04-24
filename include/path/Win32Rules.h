/**  
 * @file Win32Rules.h
 */
#if !defined(_PATH_WIN32RULES_H_)
#define _PATH_WIN32RULES_H_

#include <path/PathRules.h>
#include <string>

namespace path {
    // Forward declarations
    class Canonical;
    class Path;
    
    /**
     * @class Win32Rules path/Win32Rules.h
     * Implements the Windows path rules
     * (Not yet implemented)
     */
    class Win32Rules : public PathRules
    {
        
    public:
        Win32Rules();
        virtual ~Win32Rules();
        
        static Win32Rules    rules;
        
        virtual Canonical canonical(const std::string &path) const;
        virtual std::string quote(const std::string & path) const;
        //virtual std::string add(const Canonical &canonical) const;
    };
}
#endif // !defined(_PATH_WIN32RULES_H_)
