/**  
 * @file Win32Rules.h
 *
 * Implementation of the Class Win32Rules
 *
 * Created on:      11-May-2007 5:09:33 PM
 * Original author: Pete Ware
 */
#if !defined(_PATH_WIN32RULES_H_)
#define _PATH_WIN32RULES_H_

#include <path/PathRules.h>
#include <string>

// Forward declarations
class Cannonical;
class Path;

class Win32Rules : public PathRules
{

public:
	Win32Rules();
	virtual ~Win32Rules();
    
    static Win32Rules    rules;

	virtual Cannonical cannonical(const std::string &path) const;
	virtual std::string quote(const std::string & path) const;
    //virtual std::string add(const Cannonical &canonical) const;
};
#endif // !defined(_PATH_WIN32RULES_H_)
