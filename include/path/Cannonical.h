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
	Cannonical(const std::string &protocol, const std::string &host, const std::string &extra);
	/// Copy but with new path
	Cannonical(const Cannonical &copy, const std::vector<std::string> &components);

	/// Destructor
	virtual ~Cannonical();
	/// Return the protocol string (may be empty)
	const std::string &	protocol() const;
	/// Return the host string (may be empty)
	const std::string &	host() const;
	/// Return the extra string (may be empty)
	const std::string &	extra() const;
    /// Set the drive letter
    void setDrive(const std::string &drive);
    /// Return the drive letter (may be empty)
    const std::string & drive() const;
	/// Add another component to the end
	void add(const std::string &dir);

	/// Return reference; you can change this.
	std::vector<std::string> &components();
	/// Return const reference for const object
	const std::vector<std::string> &components() const;

	/// Set if this is an absolute path
	bool	setAbs(bool abs);
	/// Return if this is an absolute path
	bool		abs() const;

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
	std::vector<std::string> m_components;

};
/// Print this out for debugging purposes!
std::ostream& operator<<(std::ostream &out, const Cannonical &cannon);
#endif // !defined(_PATH_CANNONICAL_H_)
