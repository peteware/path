/**  
 * @file BadPath.h
 *
 * Implementation of the Class BadPath
 *
 * Created on:      11-May-2007 5:09:29 PM
 * Original author: Pete Ware
 */
#if !defined(EA_6D72756D_0FF0_43bf_94F3_A0D179375104__INCLUDED_)
#define EA_6D72756D_0FF0_43bf_94F3_A0D179375104__INCLUDED_

#include "PathException.h"

class BadPath : public PathException
{

public:
	BadPath();
	virtual ~BadPath();

};
#endif // !defined(EA_6D72756D_0FF0_43bf_94F3_A0D179375104__INCLUDED_)
