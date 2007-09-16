/**  
 * @file Permission.h
 *
 * Implementation of the Class Permission
 *
 * Created on:      11-May-2007 5:09:32 PM
 * Original author: Pete Ware
 */
#if !defined(_PATH_PERMISSION_H_)
#define _PATH_PERMISSION_H_

#include "PathException.h"

/**
 * An operation failed because of permissions.
 */
class Permission : public PathException
{

public:
	Permission();
	virtual ~Permission() throw();

};
#endif // !defined(_PATH_PERMISSION_H_)
