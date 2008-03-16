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

#include <path/Strings.h>
#include <vector>
#include <string>
#include <iosfwd>

/**
 * Represents a Path in a standard form.
 * 
 * Each component added represents a new element
 * in the path.  When convereted via a PathRules
 * a directory seperator is placed between
 * each component.
 *
 * This is used to convert from one PathRules type to another.
 */
class Cannonical
{

public:
	/// Default constructor
	Cannonical();
	/// Copy constructor
	Cannonical(const Cannonical &copy);
	/// Construct with basics but no path
	//Cannonical(const std::string &protocol, const std::string &host, const std::string &extra);
	/// Copy but with new path
	Cannonical(const Cannonical &copy, const Strings &components);

    /// Create with a single componenent
	Cannonical(const std::string &p1);
    /// Create with two componenents
	Cannonical(const std::string &p1, const std::string &p2);
    /// Create with three componenents
	Cannonical(const std::string &p1, const std::string &p2, const std::string &p3);
    /// Create with four componenents
	Cannonical(const std::string &p1, const std::string &p2, const std::string &p3, const std::string &p4);

	/// Destructor
	virtual ~Cannonical();

    /// Set the protocol, host, and extra without changing drive or components
    Cannonical & copyInfo(const Cannonical &cannon);
    /// Set the protocol (e.g. "http")
    Cannonical &  setProtocol(const std::string &proto);
	/// Return the protocol string (may be empty)
	const std::string &	protocol() const;

    /// Set the hostname (e.g. "www.peteware.com")
    Cannonical & setHost(const std::string &host);
	/// Return the host string (may be empty)
	const std::string &	host() const;

    /// Set the extra part (e.g. "8080")
    Cannonical &  setExtra(const std::string &extra);
	/// Return the extra string (may be empty)
	const std::string &	extra() const;

    /// Set the drive letter (e.g. "C")
    Cannonical &  setDrive(const std::string &drive);
    /// Return the drive letter (may be empty)
    const std::string & drive() const;

	/// Add another component to the end
	Cannonical & add(const std::string &dir);
	/// Add another two components to the end
    Cannonical & add(const std::string &dir1, const std::string &dir2);
	/// Add another three components to the end
    Cannonical & add(const std::string &dir1, const std::string &dir2, const std::string &dir3);
    /// Add another four components to the end
    Cannonical & add(const std::string &dir1, const std::string &dir2, const std::string &dir3, const std::string &dir4);
    
	/// Return reference; you can change this.
	Strings &components();
	/// Return const reference for const object
	const Strings &components() const;

	/// Set if this is an absolute path
	Cannonical & setAbs(bool abs);
	/// Return if this is an absolute path
	bool	abs() const;

protected:
	/**
	 * Gives the protocol (http, ftp, file, unc, etc).  May be empty.
	 */
	std::string m_protocol;
	std::string m_host;     ///< Host (e.g. peteware.com); May be empty
	std::string m_extra;	///< Extra (e.g. 8080); may be empty
    std::string m_drive;    ///< Drive letter (e.g. C); may be empty
	bool		m_abs;      ///< Is path absolute?
	/**
	 * Each individual path component.
	 * 
	 * The raw components (e.g. environment varables are not expaned) are stored.
	 */
	Strings m_components;

};
/// Print this out for debugging purposes!
std::ostream& operator<<(std::ostream &out, const Cannonical &cannon);
/// Return true if these two Cannoical objects are the same values
bool operator==(const Cannonical &op1, const Cannonical &op2);
/// Return true if these tow Cannonical objects are different values
bool operator!=(const Cannonical &op1, const Cannonical &op2);

#endif // !defined(_PATH_CANNONICAL_H_)
