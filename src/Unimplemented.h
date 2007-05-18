/**  
 * @file Unimplemented.h
 *
 * Implementation of the Class Unimplemented
 *
 * Created on:      11-May-2007 5:09:33 PM
 * Original author: Pete Ware
 */
#if !defined(EA_D9412DB2_4117_4f74_8101_82DEBE0899D4__INCLUDED_)
#define EA_D9412DB2_4117_4f74_8101_82DEBE0899D4__INCLUDED_

#include "PathException.h"

/**
 * The operation is not implemented.
 * 
 */
class Unimplemented : public PathException
{

public:
	Unimplemented();
	virtual ~Unimplemented();

};
#endif // !defined(EA_D9412DB2_4117_4f74_8101_82DEBE0899D4__INCLUDED_)
