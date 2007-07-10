/**  
 * @file Win32Rules.h
 *
 * Implementation of the Class Win32Rules
 *
 * Created on:      11-May-2007 5:09:33 PM
 * Original author: Pete Ware
 */
#if !defined(EA_AB3F85DA_5097_4a8e_AA43_A723FE22CFEA__INCLUDED_)
#define EA_AB3F85DA_5097_4a8e_AA43_A723FE22CFEA__INCLUDED_

#include "Cannonical.h"
#include "Path.h"
#include "PathRules.h"

class Win32Rules : public PathRules
{

public:
	Win32Rules();
	virtual ~Win32Rules();

	virtual Cannonical canonical(const Path &path) const;
	virtual Path convert(const Cannonical &canonical) const;
	virtual std::string quote(const std::string & path) const;
};
#endif // !defined(EA_AB3F85DA_5097_4a8e_AA43_A723FE22CFEA__INCLUDED_)
