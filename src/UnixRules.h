/**  
 * @file UnixRules.h
 *
 * Implementation of the Class UnixRules
 *
 * Created on:      11-May-2007 5:09:33 PM
 * Original author: Pete Ware
 */
#if !defined(EA_2002AF95_B2BA_45e1_B318_155B550DBE61__INCLUDED_)
#define EA_2002AF95_B2BA_45e1_B318_155B550DBE61__INCLUDED_

#include "Cannonical.h"
#include "Path.h"
#include "PathRules.h"

class UnixRules : public PathRules
{
public:
	UnixRules();
	virtual ~UnixRules();

	virtual Cannonical canonical(const Path &path) const;
	virtual Path convert(const Cannonical &canonical) const;
	virtual std::string quote(const std::string & path) const;

};
#endif // !defined(EA_2002AF95_B2BA_45e1_B318_155B550DBE61__INCLUDED_)
