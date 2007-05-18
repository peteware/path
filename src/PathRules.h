/**  
 * @file PathRules.h
 *
 * Implementation of the Class PathRules
 *
 * Created on:      11-May-2007 5:09:32 PM
 * Original author: Pete Ware
 */
#if !defined(EA_B8816B68_5736_4a45_816E_63C08B05D598__INCLUDED_)
#define EA_B8816B68_5736_4a45_816E_63C08B05D598__INCLUDED_

#include <string>
// Forward declarations
class Path;
class Cannonical;

/**
 * Defines an interface for mainpulating Path components.  For example, the
 * difference between using a forward slash between directories (Unix) for
 * backward slash (Win32) is encapsulating here.  Characters that are special can
 * be quoted by the implementation.  Finally, an implementation provides a way to
 * convert between path rules.
 */
class PathRules
{
public:
	PathRules();
	virtual ~PathRules();

	virtual Cannonical canonical(const Path &path) const;
	virtual Path convert(const Cannonical &canonical) const;
	virtual std::string quote(const std::string & path) const;

};
#endif // !defined(EA_B8816B68_5736_4a45_816E_63C08B05D598__INCLUDED_)
