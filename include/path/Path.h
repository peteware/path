/**  
 * @file Path.h
 *
 * Implementation of the class Path
 */
#if !defined(_PATH_PATH_H_)
#define _PATH_PATH_H_

#include <path/PathRules.h>
#include <path/Strings.h>

#include <vector>
#include <string>
#include <iosfwd>

namespace path {
    /**
     * A Path is an arbitrary string used to represent a path to a file
     * or directory.  The primary purpose of using a Path instead of a string is
     * to encourage operating system independence.  A secondary purpose
     * is to make typical filename operators easier.  The operations on a Path 
     * make no attempt to validate if the file or directory actually exists. 
     * 
     * You can operate on a Path with some common operations such as add(),
     * extension(), split(), dirname(), basename(), stem(), + and &.  All
     * such operations leave the original Path object unchanged and
     * return a copy.
     *
     * To interact with the rest of the system, you can use path(), str(), and 
     * normpath() to return a std::string or path_c(), str_c(), normpath_c() 
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
     * To support the Node class (represnting actual files and directories),
     * the Path class is defined with value semantics.  This means to change
     * something a copy is created.  This what the
     * Node class can derive from Path and maintain it's
     * own semantics.  For example, it doesn't make sense
     * to change a Node's suffix().
     *
     * @sa 
     * Canonical, PathRules, UnixRules, Wn32Rules, UriRules, Win32Path, 
     * UnixPath.
     */
    class Path
        {
        public:
            /// Default constructor
            Path(const PathRules *rules = 0);
            /// Constructor from std::string
            Path(const std::string &path);
            /// Use a Canonical path and PathRules
            Path(const Canonical &canon, const PathRules *rules = 0);
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
            const char * str_c() const;
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
            std::vector<Path> split() const;
            
            /// Return the Canonical representation of the path
            const Canonical &canon() const;
            
            /// Append a string to last element.
            Path operator&(const std::string &append) const;
            
            /// Return the rules (may be NULL)
            const PathRules *pathRules() const;
            /// Return PathRules, never null
            const PathRules *	rules() const;
            /// Set the default rules to be used by most paths
            static PathRules * setDefaultPathRules(PathRules * rules);
            /// Return the rules
            static const PathRules * defaultPathRules();
            
            /// Return the current working directory
            static Path getcwd();
            
        private:
            /// Use these rules if none are set.
            static PathRules *	s_defaultPathRules;
            /**
             * The path as set.
             * 
             * This is the uninterpreted string and is the value returned by str().
             */
            std::string		m_path;
            /// These are the rules we use for this path; may be NULL
            const PathRules *		m_rules;
            /// The path in canonical form; may be NULL
            mutable Canonical *m_canon;
            /// Cached value path converted by path();
            mutable std::string *   m_pathStr;
            
        };
    
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
path::Path operator+(const path::Path &path, const char *dir);
/// Add a new directory
path::Path operator+(const path::Path &path, const std::string &dir);
/// Concatenate two paths
path::Path operator+(const path::Path &path, const path::Path &op2);
/// Append a string to last component in path
path::Path operator&(const std::string &append);
#endif // !defined(_PATH_PATH_H_)
