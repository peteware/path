/**
 * @file Canonical.h
 */
#if !defined(_PATH_CANNONICAL_H_)
#define _PATH_CANNONICAL_H_

#include <path/Strings.h>
#include <string>
#include <iosfwd>

namespace path
{
/**
 * @class Canonical path/Canonical.h
 * Represents a Path in a standard form.
 *
 * Each component added represents a new element
 * in the path.  When convereted via a RulesBase
 * a directory seperator is placed between
 * each component.
 *
 * This is used to convert from one RulesBase type to another.
 */
class Canonical
{
public:
    /// Default constructor
    Canonical();
    /// Copy constructor
    Canonical(const Canonical &copy);
    /// Construct with basics but no path
    //Canonical(const std::string &protocol, const std::string &host, const std::string &extra);
    /// Copy but with new path
    Canonical(const Canonical &copy, const Strings &components);

    /// Create with a single componenent
    Canonical(const std::string &p1);
    /// Create with two componenents
    Canonical(const std::string &p1, const std::string &p2);
    /// Create with three componenents
    Canonical(const std::string &p1, const std::string &p2, const std::string &p3);
    /// Create with four componenents
    Canonical(const std::string &p1, const std::string &p2, const std::string &p3, const std::string &p4);

    /// Destructor
    virtual ~Canonical();

    /// Assignment operator
    Canonical &operator=(const Canonical & op2);

    /// Copy the protocol, host, and extra without changing drive or components
    Canonical & setInfo(const Canonical &canon);
    /// Set the protocol (e.g. "http")
    Canonical &  setProtocol(const std::string &proto);
    /// Return the protocol string (may be empty)
    const std::string &     protocol() const;

    /// Set the hostname (e.g. "www.peteware.com")
    Canonical & setHost(const std::string &host);
    /// Return the host string (may be empty)
    const std::string &     host() const;

    /// Set the extra part (e.g. "8080")
    Canonical &  setExtra(const std::string &extra);
    /// Return the extra string (may be empty)
    const std::string &     extra() const;

    /// Set the drive letter (e.g. "C")
    Canonical &  setDrive(const std::string &drive);
    /// Return the drive letter (may be empty)
    const std::string & drive() const;

    /// Add another component to the end
    Canonical & add(const std::string &dir);

    /// Return reference; you can change this.
    Strings &components();
    /// Return const reference for const object
    const Strings &components() const;

    /// Set if this is an absolute path
    Canonical & setAbs(bool abs);
    /// Return if this is an absolute path
    bool    abs() const;

protected:
    /**
     * Gives the protocol (http, ftp, file, unc, etc).  May be empty.
     */
    std::string m_protocol;
    std::string m_host;     ///< Host (e.g. peteware.com); May be empty
    std::string m_extra;    ///< Extra (e.g. 8080); may be empty
    std::string m_drive;    ///< Drive letter (e.g. C); may be empty
    bool            m_abs;      ///< Is path absolute?
    /**
     * Each individual path component.
     *
     * The raw components (e.g. environment varables are not expaned) are stored.
     */
    Strings m_components;

};
}
/// Print this out for debugging purposes!
std::ostream& operator<<(std::ostream &out, const path::Canonical &canon);
/// Return true if these two Cannoical objects are the same values
bool operator==(const path::Canonical &op1, const path::Canonical &op2);
/// Return true if these tow Canonical objects are different values
bool operator!=(const path::Canonical &op1, const path::Canonical &op2);

#endif // !defined(_PATH_CANNONICAL_H_)
