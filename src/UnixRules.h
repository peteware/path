/**  
 * @file UnixRules.h
 *
 * Implementation of the Class UnixRules
 *
 * Created on:      11-May-2007 5:09:33 PM
 * Original author: Pete Ware
 */
#if !defined(_Path_UnixRules_h_)
#define _Path_UnixRules_h_

#include "PathRules.h"
// Forward declarations
class Path;
class Cannonical;

class UnixRules : public PathRules
{
public:
	UnixRules();
	virtual ~UnixRules();

	virtual Cannonical cannonical(const Path &path) const;
	virtual Path convert(const Cannonical &canonical) const;
	virtual std::string quote(const std::string & path) const;

	static UnixRules	rules;

};
#endif // !defined(_Path_UnixRules_h_)
