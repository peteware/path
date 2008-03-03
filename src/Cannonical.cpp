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
 * Sets everything to be empty
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
 * Better to get rid of this and just use some properties.
 */
Cannonical::Cannonical(const std::string &protocol, const std::string &host, const std::string &extra)
	: m_protocol(protocol),
	  m_host(host),	  
	  m_extra(extra),
      m_drive(),
	  m_abs(false),
	  m_components()
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
 * Empty destructor
 */
Cannonical::~Cannonical()
{
}

const std::string & Cannonical::protocol() const
{
	return m_protocol;
}

const std::string & Cannonical::host() const
{
	return m_host;
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
 */
void Cannonical::setDrive(const std::string &drive)
{
    m_drive = drive;
}

const std::string &Cannonical::drive() const
{
    return m_drive;
}

/**
 * This is a simplified way to append an item
 * See components() to get full access.
 */
void Cannonical::add(const std::string &dir)
{
	m_components.push_back(dir);
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
 * @return Previous value of abs().
 */
bool Cannonical::setAbs(bool abs)
{
	std::swap(abs, m_abs);
	return abs;
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
