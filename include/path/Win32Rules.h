/**  
 * @file Win32Rules.h
 */
#if !defined(_PATH_WIN32RULES_H_)
#define _PATH_WIN32RULES_H_

#include <path/PathRules.h>

namespace path {
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
        virtual bool quote(const std::string & path, std::string *dest) const;
        virtual bool unquote(const std::string &subdir, std::string *dest) const;
    };
}
#endif // !defined(_PATH_WIN32RULES_H_)
