/**  
 * @file UriRules.h
 *
 * Implementation of the Class UriRules
 *
 * Created on:      11-May-2007 5:09:33 PM
 * Original author: Pete Ware
 */
#if !defined(EA_BB1196E9_08C1_4050_AD5B_B14215CA5142__INCLUDED_)
#define EA_BB1196E9_08C1_4050_AD5B_B14215CA5142__INCLUDED_

#include "Cannonical.h"
#include "Path.h"
#include "PathRules.h"

class UriRules : public PathRules
{

public:
	UriRules();
	virtual ~UriRules();

	virtual Cannonical canonical(const Path &path) const;
	virtual Path convert(const Cannonical &canonical) const;
	virtual std::string quote(const std::string & path) const;

};
#endif // !defined(EA_BB1196E9_08C1_4050_AD5B_B14215CA5142__INCLUDED_)
