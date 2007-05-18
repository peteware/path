/**  
 * @file Permission.h
 *
 * Implementation of the Class Permission
 *
 * Created on:      11-May-2007 5:09:32 PM
 * Original author: Pete Ware
 */
#if !defined(EA_90B2B1B4_DF1D_4caf_95A6_76B88139D79B__INCLUDED_)
#define EA_90B2B1B4_DF1D_4caf_95A6_76B88139D79B__INCLUDED_

#include "PathException.h"

/**
 * An operation failed because of permissions.
 */
class Permission : public PathException
{

public:
	Permission();
	virtual ~Permission();

};
#endif // !defined(EA_90B2B1B4_DF1D_4caf_95A6_76B88139D79B__INCLUDED_)
