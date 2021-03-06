/**
 * @file Path.h
 *
 * Implementation of the class Path
 */
#if !defined(_PATH_PATH_H_)
#define _PATH_PATH_H_

#include <path/RulesBase.h>
#include <path/Strings.h>
#include <path/Refcount.h>

#include <string>
#include <iosfwd>

namespace path {
// Forward declarations
class NodeInfo;
class PathIter;
class PathExtra;
class Path;

/// A list of Path
typedef std::vector<Path> Paths;

/**
 * @class Path path/Path.h
 *
 * A Path is a string representing a filename
 * or directory.  The primary purpose of using a Path instead of a string is
 * to encourage operating system independence.  A secondary purpose
 * is to make typical filename operators easier.  The operations on a Path
 * make no attempt to validate if the file or directory actually exists.
 *
 * All the following operations leave the original Path object unchanged and
 * return a copy.  In technical terms, a Path is an immutable object.
 * You can operate on a Path with:
 * - add() to apend a component or a vector of components
 * - extension() to return the suffix (.e.g ".cpp") for a file
 * - split() to return a vector with each element adding one
 *   more componenent to the path.
 * - dirname() returns the directory or all but last component
 * - basename() returns the last component
 * - stem() returns the filename without any suffix
 * - / as a shorthand for add()
 * - + adds to the last component
 *
 * To interact with the rest of the system 
 * - path() returns a fully expanded string (path_c()) for NUL terminated)
 * - str() returns a string with ~ and $VAR still present(c_str())
 * - normpath() 
 * normpath() to return a std::string or path_c(), c_str(), normpath_c()
 * to return C-style, NUL terminated strings.  path() and normpath()
 * also expand environment variables (e.g. $HOME) and "~".
 *
 * The choice made in this design is that a Path manipulates a Canonical
 * representation of a path.  The unfortunate side affect is
 * it's difficult to just use a string to create a Path and you must
 * be explicit about the rules you want to use when initializing
 * a Path.  For example
 *
 * @code
 * Path     path1(UnixPath("/a/b/c"));
 * Path     path2(Win32Path("\\a\\b\\c"));
 * @endcode
 *
 * Result in two identical paths.
 *
 * UnixPath() and Win32Path() take strings and return a Canonical
 * object for that set of rules.
 *
 * To make things easier, the Canonical class design has most
 * methods returning a reference to the Canonical object so you can chain
 * several operations together (this is the antithesis
 * of how the Path class works).  For example:
 *
 * @code
 * Path     path1(UnixPath("a").setAbs(true).setDrive("C"));
 * Path     path2(Win32Path("C:\\a"));
 * @endcode
 *
 * Result in two identical paths.
 *
 * To list the contents of a directory, you can use the
 * iterator returned by begin(), glob(), and end() so you
 * can use Standard Template Library algorithms.  This
 * returns a Forward Iterator in STL terminology.  An
 * iterator can also be told to traverse a directory
 * hierachy by using setRecursive():
 *
 * @code
 * Path  path(UnixPath("/tmp"));
 *
 * for (Path::iterator iter = path.begin().setRecursive(); iter != path.end(); ++iter)
 * {...}
 * @endcode
 *
 * There are methods to interact with the underlying file system.
 * These are intended to handle a few common situations rather
 * then all possible filesystem interactions.  These rely
 * on the System global variable to provide an interaction
 * with the underlying file system.
 *
 * - exists() returns true if the path exists
 * - size() returns the size in bytes
 * - isDir() returns true if the path exists and is a directory
 * - getcwd() is a static method that returns the current working 
 *   directory as a Path
 * - mkdirs() is static method that creates a directroy and any 
 *   needed directories along the path
 * - mkfile() is a static method that creates file and any
 *   needed directories along the path
 * - info() returns complete info about a path via a NodeInfo
 *   
 *
 * 
 * @sa
 * Canonical, RulesBase, RulesUnix, Wn32Rules, RulesUri, Win32Path,
 * UnixPath.
 */
class Path
{
public:
    /// Default constructor
    Path(const RulesBase *rules = 0);
    /// Constructor from std::string
    Path(const std::string &path);
    /// Use a Canonical path and RulesBase
    Path(const Canonical &canon, const RulesBase *rules = 0);
    /// Construct from a NUL terminated string
    Path(const char *path);
    /// Copy constructor
    Path(const Path &copy);
    /// Destructor
    virtual ~Path();
    /// Assignment operator
    Path & operator=(const Path &op2);

    /// Return original path
    const std::string & str() const;
    /// Return orignal path as C-style, NUL terminated string
    const char * c_str() const;
    /// Return path with ~ and environment variables expanded
    const std::string & path() const;
    /// Same as path() but a C-style, NUL terminated string
    const char * path_c() const;
    /// Return original string but cleaned up
    std::string normpath() const;
    /// Expand any environment variables
    Path expand() const;
    /// Expand any environment variables
    Path expand(const StringMap &vars) const;
    /// Return the last component of Path
    std::string basename() const;
    /// Return the directory component of Path
    Path dirname() const;
    /// Return the filename extension
    std::string extension() const;
    /// Return basename() without extension
    std::string stem() const;

    /// Return if this is an absolute path (not relative)
    bool abs() const;
    /// Return a new path by converting this one to an absolute path
    Path makeAbs() const;

    /// Return the drive letter (may be empty)
    const std::string &drive() const;
    /// Return the protocol (may be empty)
    const std::string &protocol() const;
    /// Return the host (may be empty)
    const std::string &host() const;
    /// Return the extra parameters
    const std::string &extra() const;

    /// Concatenate this and Path
    Path add(const Path &path) const;
    /// Concatenate vector of strings with each as a component.
    Path add(const Strings &strings) const;
    /// Concatenate a single string
    Path add(const std::string &p) const;
    /// Concatenate a NUL terminated string
    Path add(const char *p) const;
    /// Return each directory component as a Path.
    Paths split() const;

    /// Return the Canonical representation of the path
    const Canonical &canon() const;

    /// Append a string to last element.
    Path operator+(const std::string &append) const;

    /// Return the rules (may be NULL)
    const RulesBase *pathRules() const;
    /// Return RulesBase, never null
    const RulesBase *       rules() const;
    /// Set the default rules to be used by most paths
    static RulesBase * setDefaultRulesBase(RulesBase * rules);
    /// Return the rules
    static const RulesBase * defaultRulesBase();

    /// How to iterate through directory
    typedef PathIter        iterator;
    /// And the const version of iterator
    typedef const PathIter  const_iterator;
    /// Return iterator for examining files in this directory
    iterator begin();
    /// Return iterator for examining files in this directory, const version
    const_iterator begin() const;
    /// And return the end of the list
    iterator end();
    /// And return the end of the list, const version
    const_iterator end() const;
    /// Shorthand to only match a specific file in this directory
    iterator glob(const std::string &pattern);
    /// Shorthand to only match a specific file, const version
    const_iterator glob(const std::string &pattern) const;

    /// Return meta info about the underlying file.
    const NodeInfo &info() const;
    /// Return the size in bytes of this file
    off_t size() const;
    /// Check if this Node exists
    bool exists() const;
    /// Return if this is a directory
    bool isDir() const;
    /// Return the current working directory
    static Path getcwd();
    /// Create all directories in Path
    static int mkdirs(const Path &path, int mode = 0777);
    /// Create all directories and the file in Path
    static void mkfile(const Path &path, int dirmode = 0777, int filemode = 0666);

private:
    /// Use these rules if none are set.
    static RulesBase *      s_defaultRulesBase;
    mutable Refcount<PathExtra> m_meta;

};
/// Convert an array of strings into an array of Paths
Paths strings2Paths(const Strings &strings, const RulesBase *rules = 0);
// Shortcuts for handling different paths as strings
/// Convert a unix style path ("/a/b/c") to Canonical
path::Canonical UnixPath(const std::string &path);
/// Convert a Win32 style path ("C:\temp") to Canonical
path::Canonical Win32Path(const std::string &path);
/// Convert a URL style path ("http://www.peteware.com/a") to Canonical
path::Canonical URLPath(const std::string &path);
}
/// Check if Cannonical names are the same
bool operator==(const path::Path &op1, const path::Path &op2);
/// Check if Cannonical names are different.
bool operator!=(const path::Path &op1, const path::Path &op2);
/// Print out the path
std::ostream &operator<<(std::ostream &out, const path::Path&path);
/// Add a new directory
path::Path operator/(const path::Path &path, const char *dir);
/// Add a new directory
path::Path operator/(const path::Path &path, const std::string &dir);
/// Concatenate two paths
path::Path operator/(const path::Path &path, const path::Path &op2);
#endif // !defined(_PATH_PATH_H_)
