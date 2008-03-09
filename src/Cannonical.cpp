/**
 * @file Cannonical.cpp
 *
 * Implementation of the Class Cannonical
 *  Created on:      11-May-2007 5:09:30 PM
 *  Original author: Pete Ware
 */
#include <path/Cannonical.h>
#include <iostream>
#include <algorithm>
#include <iterator>


/**
 * Sets everything to be empty and this to be a relative path.
 */
Cannonical::Cannonical()
	: m_protocol(),
	  m_host(),	  
	  m_extra(),
      m_drive(),
	  m_abs(false),
	  m_components()

{
}

/**
 * @param copy Provides the protocol, host, and component info
 */
Cannonical::Cannonical(const Cannonical &copy)
	: m_protocol(copy.m_protocol),
	  m_host(copy.m_host),
	  m_extra(copy.m_extra),
      m_drive(copy.m_drive),
	  m_abs(copy.m_abs),
	  m_components(copy.m_components)
{
}

/**
 * Easy way to copy basic info but with a new path
 *
 * @param copy Provides the protocol, host and extra info
 * @param components Replaces that path from copy
 */
Cannonical::Cannonical(const Cannonical &copy, const std::vector<std::string> &components)
	: m_protocol(copy.m_protocol),
	  m_host(copy.m_host),
	  m_extra(copy.m_extra),
      m_drive(copy.m_drive),
	  m_abs(copy.m_abs),
	  m_components(components)
{
}

/**
 * Initialized info (see copyInfo()) to empty and makes this a relative path.
 *
 * @param dir1 First directory
 */
Cannonical::Cannonical(const std::string &dir1)
	: m_protocol(),
	  m_host(),	  
	  m_extra(),
      m_drive(),
	  m_abs(false),
	  m_components()

{
    add(dir1);
}

/**
 * Initialized info (see copyInfo()) to empty and makes this a relative path.
 *
 * @param dir1 First directory
 * @param dir2 First directory
 */
Cannonical::Cannonical(const std::string &dir1, const std::string &dir2)
	: m_protocol(),
	  m_host(),	  
	  m_extra(),
      m_drive(),
	  m_abs(false),
	  m_components()

{
    add(dir1, dir2);
}

/**
 * Initialized info (see copyInfo()) to empty and makes this a relative path.
 *
 * @param dir1 First directory
 * @param dir2 Second directory
 * @param dir3 Third directory
 */
Cannonical::Cannonical(const std::string &dir1, const std::string &dir2, const std::string &dir3)
	: m_protocol(),
	  m_host(),	  
	  m_extra(),
      m_drive(),
	  m_abs(false),
	  m_components()

{
    add(dir1, dir2, dir3);
}
/**
 * Initialized info (see copyInfo()) to empty and makes this a relative path.
 *
 * @param dir1 First directory
 * @param dir2 Second directory
 * @param dir3 Third directory
 * @param dir4 Third directory
 */
Cannonical::Cannonical(const std::string &dir1, const std::string &dir2, const std::string &dir3, const std::string &dir4)
	: m_protocol(),
	  m_host(),	  
	  m_extra(),
      m_drive(),
	  m_abs(false),
	  m_components()

{
    add(dir1, dir2, dir3, dir4);
}


/**
 * Empty destructor
 */
Cannonical::~Cannonical()
{
}

/**
 * The protocol is something like "http", "ftp", "file" and
 * is meaningful only for a specific type of PathRule.  For example,
 * UnixRules ignore protocol.
 *
 * @param proto The new protocol
 * @return A reference to this object
 */
Cannonical &  Cannonical::setProtocol(const std::string &proto)
{
    m_protocol = proto;
    return *this;
}

const std::string & Cannonical::protocol() const
{
	return m_protocol;
}

/**
 * The host is something like "www.peteware.com" and is meaningful
 * only for a specific type of PathRule (such as UriRules).
 *
 * @param host The new hostname to use
 * @return A reference to this object
 */
Cannonical &  Cannonical::setHost(const std::string &host)
{
    m_host = host;
    return *this;
}

const std::string & Cannonical::host() const
{
	return m_host;
}

/**
 * For example, in http, you can specify the port number
 * such as 8080 in the example: "http://www.peteware.com:8080/index.html"
 *
 * @param extra The additional value for the protocol
 * @return A reference to this object
 */
Cannonical &  Cannonical::setExtra(const std::string &extra)
{
    m_extra = extra;
    return *this;
}

const std::string & Cannonical::extra() const
{
	return m_extra;
}

/**
 * This helps with win32/DOS compatibility by allowing
 * a drive to be specified.  For example: 
 * @code
 * C:\temp
 * @endcode
 * The "C" is the drive.  Do not include the ":" as
 * other protocols use something different.  For example,
 * UNC uses a "$" to specify a drive:
 * @code
 * \\somehostname\C$\temp
 * @endcode
 * @param drive The drive letter
 * @return A reference to this object
 */
Cannonical &  Cannonical::setDrive(const std::string &drive)
{
    m_drive = drive;
    return *this;
}

const std::string &Cannonical::drive() const
{
    return m_drive;
}

/**
 * This is a simplified way to append an item
 * See components() to get full access.
 *
 * @param dir The component to append
 * @return A reference to this object
 */
Cannonical & Cannonical::add(const std::string &dir)
{
    if (!dir.empty())
        m_components.push_back(dir);
    return *this;
}

/**
 * This is a simplified way to append an item
 * See components() to get full access.
 *
 * @param dir1 The component to append
 * @param dir2 The component to append
 * @return A reference to this object
 */
Cannonical & Cannonical::add(const std::string &dir1, const std::string &dir2)
{
	add(dir1);
	add(dir2);
    return *this;
}

/**
 * This is a simplified way to append an item
 * See components() to get full access.
 *
 * @param dir1 The component to append
 * @param dir2 The component to append
 * @param dir3 The component to append
 * @return A reference to this object
 */
Cannonical & Cannonical::add(const std::string &dir1, const std::string &dir2, const std::string &dir3)
{
    add(dir1);
    add(dir2);
    add(dir3);
    return *this;
}

/**
 * This is a simplified way to append an item
 * See components() to get full access.
 *
 * @param dir1 The component to append
 * @param dir2 The component to append
 * @param dir3 The component to append
 * @param dir4 The component to append
 * @return A reference to this object
 */
Cannonical & Cannonical::add(const std::string &dir1, const std::string &dir2, const std::string &dir3, const std::string &dir4)
{
    add(dir1);
    add(dir2);
    add(dir3);
    add(dir4);
    return *this;
}

/**
 * Rather then anticipate every possible operation
 * on the list of components, this just
 * exposes the list as a reference.
 *
 * @return Componenets in a path
 */
std::vector<std::string> &Cannonical::components()
{
	return m_components;
}

/**
 * @return Components in a path
 */
const std::vector<std::string> &Cannonical::components() const
{
	return m_components;
}

/**
 * Some PathRules really only understand absolute
 * paths.  For example, URLs are really always absolute
 * with relative ones being expressed only relative
 * to an existing path.
 *
 * Technically, even filesystem pathnames are 
 * relative to the current working directory.
 *
 * @param abs	If this path starts at root
 * @return A reference to this object
 */
Cannonical & Cannonical::setAbs(bool abs)
{
	std::swap(abs, m_abs);
	return *this;
}

/**
 * @return If this is an absolute path
 */
bool Cannonical::abs() const
{
	return m_abs;
}

/**
 * Don't use this to print out as a regular path.
 * Use an appropriate PathRules to do so.
 *
 * This prints out the path to look like
 * a URI:
 * @code
 *	http://www.pete.ware/a/b/c
 * @endcode
 * or more generally:
 * @code
 * protocol://host:extra/components
 * @endcode
 *
 * If protocol, host, and extra are empty it'll
 * look like a regular path with "/" seperating
 * components.
 */

std::ostream &
operator<<(std::ostream &out, const Cannonical &cannon)
{
    bool    seperator = true;
	if (!cannon.protocol().empty())
		out << cannon.protocol() << ':';
	if (!cannon.host().empty())
    {
		out << "//" << cannon.host();
        seperator = false;
    }
	if (!cannon.extra().empty())
    {
		out << ":" << cannon.extra();
        seperator = false;
    }
    if (!seperator)
        out << '/';

    if (!cannon.drive().empty())
    {
        out << cannon.drive() << ':';
    }
    if (cannon.abs())
        out << '/';
	std::copy(cannon.components().begin(),
		cannon.components().end(),
		std::ostream_iterator<std::string>(out, "/"));
	return out;
}

/**
 * Return true if all the values in the Cannonical objects op1 and op2 
 * are identical; false otherwise
 *
 * @param op1 The left hand side
 * @param op2 The right hand side
 * @return true if identical, false otherwise.
 */
bool operator==(const Cannonical &op1, const Cannonical &op2)
{
    if (op1.abs() != op2.abs())
        return false;
    if (op1.protocol() != op2.protocol())
        return false;
    if (op1.host() != op2.host())
        return false;
    if (op1.extra() != op2.extra())
        return false;
    if (op1.drive() != op2.drive())
        return false;
    if (op1.components() != op2.components())
        return false;
    return true;
}

/**
 * Return true if any of the values in the Cannonical objects op1 and op2 
 * are diffrent; false otherwise
 *
 * @param op1 The left hand side
 * @param op2 The right hand side
 * @return true if different, false otherwise.
 */
bool operator!=(const Cannonical &op1, const Cannonical &op2)
{
    return !(op1 == op2);
}
