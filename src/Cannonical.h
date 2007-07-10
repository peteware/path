/**  
 * @file Cannonical.h
 *
 * Implementation of the Class Cannonical
 *
 * Created on:      11-May-2007 5:09:30 PM
 * Original author: Pete Ware
 */
#if !defined(EA_C5B97F3D_D2E2_40da_9D4A_6DF0CBF3AABE__INCLUDED_)
#define EA_C5B97F3D_D2E2_40da_9D4A_6DF0CBF3AABE__INCLUDED_

#include <vector>
#include <string>
/**
 * Represents a Path in a standard form.
 * 
 * This is used to convert from one PathRules type to another.
 */
class Cannonical
{

public:
	Cannonical();
	virtual ~Cannonical();
	/**
	 * Each individual path component.
	 * 
	 * The raw components (e.g. envrioment varables are not expaned) are stored.
	 * 
	 */
	std::vector<std::string> m_components;
	/**
	 * Extra information.
	 */
	std::string m_extra;
	/**
	 * Host name.  Maybe empty.
	 */
	std::string m_host;
	/**
	 * Gives the protocol (http, ftp, file, unc, etc).  May be empty.
	 */
	std::string m_protocol;

};
#endif // !defined(EA_C5B97F3D_D2E2_40da_9D4A_6DF0CBF3AABE__INCLUDED_)
