/**  
 * @file FileStream.h
 *
 * Implementation of the Class FileStream
 *
 * Created on:      11-May-2007 5:09:30 PM
 * Original author: Pete Ware
 */
#if !defined(EA_5CBCB30A_4013_4658_96A5_DBDA978238E9__INCLUDED_)
#define EA_5CBCB30A_4013_4658_96A5_DBDA978238E9__INCLUDED_

#include "Node.h"
#include <fstream>

class FileStream : public Node, public std::fstream
{

public:
	FileStream();
	virtual ~FileStream();

};
#endif // !defined(EA_5CBCB30A_4013_4658_96A5_DBDA978238E9__INCLUDED_)
