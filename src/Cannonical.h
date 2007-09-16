/**  
 * @file Cannonical.h
 *
 * Implementation of the Class Cannonical
 *
 * Created on:      11-May-2007 5:09:30 PM
 * Original author: Pete Ware
 */
#if !defined(_PATH_CANNONICAL_H_)
#define _PATH_CANNONICAL_H_

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
#endif // !defined(_PATH_CANNONICAL_H_)
