/**
 * @file Path.cpp
 */
#include <path/Path.h>
#include <path/Canonical.h>
#include <path/SysCalls.h>
#include <path/Strings.h>
#include <path/Unimplemented.h>
#include <path/NodeInfo.h>
#include <path/PathIter.h>
#include <path/PathExtra.h>

#include <algorithm>
#include <iostream>

namespace path {
/**
 * Default set of rules if none are specified.  Also
 * see System::rules();
 */
PathRules * Path::s_defaultPathRules;

/**
 * Initialize an empty Path
 *
 * @param rules Rules to initialize.  May be NULL.
 */
Path::Path(const PathRules *rules)
    : m_meta(new PathExtra)
{
    m_meta->m_rules = rules;
}

/**
 * Initialize path, set rules to NULL (i.e. default)
 *
 * @param path The directory
 */
Path::Path(const char *path)
    : m_meta(new PathExtra)
{
    m_meta->m_canon = new Canonical(path);
}

/**
 * Initialize path, set rules to NULL (i.e. default)
 *
 * @param path The directory
 */
Path::Path(const std::string &path)
    : m_meta(new PathExtra)
{
    m_meta->m_canon = new Canonical(path);
}

/**
 * Create a path from a Canonical and a PathRules.
 *
 * Initialized m_path by converting from Canonical to a string
 * via the PathRules
 *
 * @param canon Canonical version of path
 * @param param_rules Rules to use
 */
Path::Path(const Canonical &canon, const PathRules *param_rules)
    : m_meta(new PathExtra)
{
    m_meta->m_rules = param_rules;
    m_meta->m_canon = new Canonical(canon);
}

/**
 * Copy the m_path, make m_rules the same (pointer copy)
 * and duplicate the m_canon.
 *
 * @param copy Path to be copied
 */
Path::Path(const Path &copy)
    : m_meta(copy.m_meta)
{
}

/**
 * Delete m_canon
 */
Path::~Path()
{
}

/**
 * Do the assignment.
 *
 * @param op The right hand side
 * @return A reference to this path
 */
Path & Path::operator=(const Path &op)
{
    if (this == &op)
        return *this;
    m_meta = op.m_meta;
    return  *this;
}

/**
 * The unexpanded string is returned (no $VAR) expansion)
 *
 * Use path() to get a string with environment
 * variables and ~ expanded. Use normpath() to get an expanded clean path
 * (".." collapsed).
 *
 * This is typically the path you want to display to a person.  Since
 * it includes $VAR it may be a little more natural and conveniant
 * for a person to see.  On the hand, you always want to
 * use path() to get a pathname that is usable to the operating system.
 * You should also you path() to report errors, etc.
 *
 * @return A string of the path.
 */
const std::string &Path::str() const
{
    if (!m_meta->m_path)
        m_meta->m_path = new std::string(rules()->str(canon()));
    return *m_meta->m_path;
}

/**
 * Same as str() but a NUL terminated string
 */
const char * Path::c_str() const
{
    return str().c_str();
}

/**
 * Return the path as a string.
 *
 * All ~ expansions and environment variables (e.g. $HOME) occur.
 *
 * See also normpath() which does the same but cleans things up a little more and
 * str() which returns the raw path being used.
 *
 * @return String with the actual path.
 */
const std::string& Path::path() const
{
    if (m_meta->m_pathStr)
        return *m_meta->m_pathStr;
    m_meta->m_pathStr = new std::string(path::expand(rules()->str(canon()), System.env(), true));
    return *m_meta->m_pathStr;
}

/**
 * @return A NUL terminated string same as path()
 */
const char * Path::path_c() const
{
    return path().c_str();
}

/**
 * Return a new Path witl all the environment
 * variables expanded based on System.env()
 *
 * @return A path with all $VAR expanded
 */
Path Path::expand() const
{
    return expand(System.env());
}

/**
 * Return a new Path with all the environment
 * variables expanded into individual
 * components.
 *
 * @param vars Map from $VAR to value
 * @return A Path
 */
Path Path::expand(const StringMap &vars) const
{
    Strings     entries;    // Saves each directory component
    const Strings &   comp = canon().components();
    bool        tilde = true;

    for (Strings::const_iterator iter = comp.begin(); iter != comp.end(); ++iter)
    {
        std::string p = path::expand(*iter, vars, tilde);
        tilde = false;
        if (p == *iter)
        {
            // Nothing changed; just add it
            entries.push_back(p);
        }
        else
        {
            // Convert the expanded variable into list of componenets
            // using the rules()
            Canonical   c(rules()->canonical(p));
            Strings &   s = c.components();
            std::copy(s.begin(), s.end(),
                      std::back_insert_iterator<Strings>(entries));
        }
    }
    // Take the meta info from cannon(), the built up list
    // of components and our set of rules and return a path.
    return Path(Canonical(canon(), entries), m_meta->m_rules);
}

/**
 * Normalized the path and returns it as a std::string.
 *
 * This removes any duplicate path seperators, collapses parent directory
 * references, expands any ~ references and any environment variables (e.g. $HOME).
 *
 *
 * See also str() which returns the path in it's raw form and path() which does ~
 * and environment variable expansion but does not try to clean up the path.
 */
std::string Path::normpath() const
{
    return path();
}

/**
 * Returns the last component of the path.
 *
 * For example, basename('/a/b/c') returns 'c'.  basename('/a/b/') returns 'b'
 * This is analogous to the Unix shell utility "basename".
 */
std::string Path::basename() const
{
    const Strings &components = canon().components();

    if (components.size() == 0)
    {
        return std::string();
    }
    else
    {
        return components[components.size() - 1];
    }
}

/**
 * Returns the directory component of Path.
 *
 * dirname('/a/b/c') returns '/a/b'.
 *
 * @code
 * Path p1(UnixRules("/a/b/c"));
 * Path p2;
 *
 * p2 = p1.add(p1.basename()));
 * assert(p1 == p2);
 * @endcode
 */
Path Path::dirname() const
{
    Strings::const_iterator last;  // end elements
    last = canon().components().end();
    if (canon().components().size() > 0)
        --last;
    Strings com(canon().components().begin(), last);

    Canonical  c(canon(), com);
    return Path(c, m_meta->m_rules);
}


/**
 * Return the extension (eg. suffix) of a Path.  For example:
 *
 * @code
 * String path("/a/file.h")
 * std::string suffix = path.extension()
 * std::cout << suffix << std::endl;
 * @endcode
 * Would print out ".h"
 *
 * If there is no extension (anything after the last '.'), then an empty string is
 * returned.
 *
 */
std::string Path::extension() const
{
    Path    last = basename();
    std::string::size_type  index = last.str().find_last_of (".");
    if (index == std::string::npos)
        return "";
    else
        return last.str().substr (index, last.str().size() - index);
}

/**
 * Return basename() of path with the extension() removed
 * @code
 * Path     p("/a/b/name.ext");
 * p.basename() == "name";
 * @endcode
 * @code
 * Path p2("/a/b/.name");
 * p2.stem() == ".name";
 * @endcode
 * This works on the unexpanded version (i.e. no $VAR).
 */
std::string Path::stem() const
{
    Path    base = basename();
    std::string::size_type  index = base.str().find_last_of (".");
    if (index == std::string::npos)
        return base.str();
    else if (index == 0)
        return base.str();
    else
        return base.str().substr (0, index);
}

/**
 * Returns true if this String represents an absolute path.
 *
 * This affects how add() works.
 */
bool Path::abs() const
{
    return canon().abs();
}

/**
 * Another alternative is to use Path::getcwd().add(path))
 * which might return something closer to what you expect.
 */
Path Path::makeAbs() const
{
    Canonical  c (canon());
    c.setAbs(true);
    return Path(c, m_meta->m_rules);
}

/**
 * @return The Canonical representation's drive().  May be empty.
 */
const std::string & Path::drive() const
{
    return canon().drive();
}

/**
 * @return The Canonical representation's protocol().  May be empty.
 */
const std::string & Path::protocol() const
{
    return canon().protocol();

}

/**
 * @return The Canonical representation's host().  May be empty.
 */
const std::string & Path::host() const
{
    return canon().host();
}

/**
 * @return The Canonical representation's extra().  May be empty.
 */
const std::string & Path::extra() const
{
    return canon().extra();
}

/**
 * Return a Path by appending another path.  For example:
 * @code
 * Path     path1("/tmp");
 * Path path2("a/b/c");
 * Path path3 = path1.add(path2);
 * std::cout << path3 << std::endl;
 * @endcode
 * Would print out "/tmp/a/b/c"
 *
 * @param path Append path to this and return a new copy
 * @return A new path.
 */
Path Path::add(const Path &path) const
{
    if (path.abs())
        return path;
    Canonical c(canon());
    std::copy(path.canon().components().begin(),
              path.canon().components().end(),
              std::back_inserter(c.components()));
    return Path (c, m_meta->m_rules);
}

/**
 * Return a Path by adding all the std::strings in the vector.
 *
 * This is comparable to repeated calling add() with each component of the vector.
 * Creating an empty Path and then calling add() should do what you'd expect.
 * For example:
 *
 * @code
 * std::string  str; // initialize this...
 * Path  path;
 *
 * path = path.add(str.split());
 * @endcode
 *
 * @param strings List of strings to be added
 * @return A new path with the same canonical and the strings added.
 */
Path Path::add(const Strings &strings) const
{

    Canonical c(canon());
    std::copy(strings.begin(), strings.end(),
              std::back_inserter(c.components()));
    return Path(c, m_meta->m_rules);
}

/**
 * Add a single directory element to the end of the path components
 *
 * @param p Extra component to be added
 * @return A new path with the same Canonical but one more element to components.
 */
Path Path::add(const std::string &p) const
{
    Canonical c(canon());
    c.add(p);
    return Path(c, m_meta->m_rules);
}

/**
 * @param p Extra component to be added
 * @return A new path with the same Canonical but one more element to components.
 */
Path Path::add(const char *p) const
{
    return add(std::string(p));
}

/**
 * Returns a vector of components to reach this path.
 *
 * If the path is abs(), then each component is also abs().  Each component
 * shares the same PathRules.
 *
 * Using Unix style paths as a shorthand, the following path "/a/b/c"
 * would return the vector of Path's: ["/a", "/a/b", "/a/b/c"]
 */
std::vector<Path> Path::split() const
{
    const Canonical &      c = canon();
    Canonical              newcanon;
    std::vector<Path>       paths;

    newcanon.setInfo(c).setAbs(c.abs());
    for (Strings::const_iterator iter = c.components().begin();
         iter != c.components().end(); ++iter)
    {
        newcanon.add(*iter);
        Path    p (newcanon, m_meta->m_rules);
        paths.push_back(p);
    }
    return paths;
}

/**
 * Returns the canonical representation of this path.
 *
 * If the result has not already been determined, it
 * is calculated.
 */
const Canonical & Path::canon() const
{
    if (!m_meta->m_canon)
        m_meta->m_canon = new Canonical();
    return *m_meta->m_canon;
}

/**
 * Return the PathRules used by the Path.  May
 * be NULL.  Do not delete the returned rules.
 */
const PathRules *Path::pathRules() const
{
    return m_meta->m_rules;
}

/**
 * If the rules
 * are not set, this uses defaultPathRules().  defaultPathRules()
 * in turn either use the value from setDefaultPathRules() or
 * if those are not set uses System.rules().
 *
 * Do not delete the returned rules!
 */
const PathRules *Path::rules() const
{
    if (m_meta->m_rules)
        return m_meta->m_rules;
    else
        return defaultPathRules();
}


/**
 * Sets the default path rules to be used by any newly created Path objects.
 *
 * This should be done at compile time to match the operations on the system.
 *
 * @param rules Set the rules to be used by default
 * @return Previous value of ruls
 */
PathRules * Path::setDefaultPathRules(PathRules * rules)
{
    std::swap(rules, s_defaultPathRules);
    return rules;
}

/**
 * Returns the default rules; never NULL.
 *
 * Typical
 * behaviour is to create a Path with the PathRules set to NULL.
 * All such paths will use whatever the defaultPathRules()
 * returns.
 *
 * Uses System.rules() if s_defaultPathRules is NULL.  System
 * is initialized at compile time to refer to the
 * SysCalls used by this particular machine.
 */
const PathRules * Path::defaultPathRules()
{
    if (s_defaultPathRules)
        return s_defaultPathRules;
    else
        return System.rules();
}

/**
 * @return An iterator to step through directory contents
 */
Path::iterator Path::begin()
{
    return  PathIter(*this);
}

/**
 * @return A const iterator to step through directory contents
 */
Path::const_iterator Path::begin() const
{
    return  PathIter(*this);
}

/**
 * @return an iterator to the end of Nodes
 */
Path::iterator Path::end()
{
    return  PathIter();
}

/**
 * @return an iterator to the end of Nodes
 */
Path::const_iterator Path::end() const
{
    return  PathIter();
}

/**
 * Use shell pattern expansion to list
 * contents of a directory.  Returns an
 * iterator to the list.  Note that this
 * only works within the specied directory
 * that this Path already represents.
 *
 * Not yet implemented
 * ;;; TODO: Implement glob()
 *
 * @param pattern A shell pattern ("*.C", "*", *.[Cho]")
 */
Path::iterator Path::glob(const std::string & pattern)
{
    throw Unimplemented("Path::glob");
    return  PathIter();
}

/**
 * @param pattern A shell pattern ("*.C", "*", *.[Cho]")
 */
Path::const_iterator Path::glob(const std::string & pattern) const
{
    throw Unimplemented("Path::glob");
    return  PathIter();
}


/**
 * Gets the System.stat() on this path.  Caches
 * the result so multiple calls avoid
 * doing more work.
 * @throws PathException
 * @return NodeInfo about this path
 */
const NodeInfo & Path::info() const
{
    if (!m_meta->m_cache)
        m_meta->m_cache = System.stat(path());
    return *m_meta->m_cache;
}

bool Path::exists() const
{
    return System.exists(path());
}

/**
 * This is a shorthand for Node:info().size().
 * Throws PathException if not able to access path.
 * @return bytes used by file
 */
off_t Path::size() const
{
    return info().size();
}

/**
 * Returns if path represents a directory.
 * Throws PathException if not able to access path.
 */
bool Path::isDir() const
{
    return info().isDir();
}

/**
 * Return the current working directory as an absolute path.
 */
Path Path::getcwd()
{
    return Path(System.rules()->canonical(System.getcwd()));
}

/**
 * Create all the directories along the path.
 * Throws a PathException if unable to create
 * one of the directories because you don't
 * have permission or a component exists
 * and is a file,  not a directory (plus
 * lots of other reasons).
 *
 * @param path The path to create
 * @return Number of directories creaeted (may be 0).
 */
int Path::mkdirs(const Path &path, int mode)
{
    int count = 0;      // How many directories created
    std::vector<Path> hier = path.expand().split();
    for (std::vector<Path>::iterator iter = hier.begin();
         iter != hier.end(); ++iter)
    {
        if (System.exists(iter->path()) && iter->isDir())
            continue;
        System.mkdir(iter->path(), mode);
        ++count;
    }
    return count;
}

/**
 * Create any directories along the path and
 * create the file.  If you don't want to
 * create the directories, just use
 * @code
 * System.touch(path.path())
 * @endcode
 *
 * @param path The file to make sure it exists.
 * @param dirmode The mode for creating the direcotry (passed to System.mkdir()) (default is 0777)
 * @param filemode THe mdoe for the actual file (passed to System.touch()) (default is (0666)
 */
void Path::mkfile(const Path &path, int dirmode, int filemode)
{
    mkdirs(path.dirname(), dirmode);
    System.touch(path.path(), filemode);
}

/**
 * This is useful for things like adding a version
 * number or a backup of a file.  For example:
 *
 * @code
 * Path     header(UnixPath("/a/b/file.h"));
 * // src becomes "/a/b/file.C"
 * Path     src = header.dirname() / header.stem() + ".C";
 * // backup becomes "/a/b/file.h.bak"
 * Path     backup = header + ".bak";
 * // backup2 becomes "/a/b/file.bak.h" (using string addition)
 * Path     backup2 = header.dirname() / (header.stem() + ".bak" + header.extension());
 * // backup3 becomes "/a/b/file.bak.h" (using Path append)
 * Path     backup3 = header.dirname() / header.stem() + ".bak" + header.extension());
 * @endcode
 *
 * @param append String to be added
 * @return A new Path with the same rules.
 */
Path Path::operator+(const std::string &append) const
{
    Canonical c(canon());

    if (c.components().size() > 0)
        c.components()[c.components().size() - 1] += append;
    else
        c.components().push_back(append);
    return Path(c, m_meta->m_rules);
}

struct ConvertToPath : public std::unary_function<std::string, Path>
{
    const PathRules *m_rules;
    ConvertToPath(const PathRules *rules)
        : m_rules(rules)
    {
    }

    Path operator()(const std::string &arg)
    {
        const PathRules *r;
        if (m_rules != NULL)
            r = m_rules;
        else
            r = Path::defaultPathRules();
        return Path(r->canonical(arg), m_rules);
    }
};

/**
 * Takes the vector of strings and converts them to a vector
 * of Path's.  If rules is NULL, then the Path::defaultPathRules()
 * are used.
 *
 * @sa PathLookup for a complete interface to maintaining a
 * list of Path's to search for a file.
 *
 * @param strings The vector of strings
 * @param rules The PathRules to use to convert each element of strings
 * @return A vector (possibly empty) of strings.
 */
Paths strings2Paths(const Strings &strings, const PathRules *rules)
{
    Paths paths;
    std::transform(strings.begin(), strings.end(),
                   std::back_insert_iterator<Paths>(paths),
                   ConvertToPath(rules));
    return paths;
}

}

/**
 * Compares the PathRules and Canonical componenets
 * to see if they are the same.  So while two paths
 * might be logically the same, "a" and "/a/b/.." are logically
 * the same, they will not compare equally.  See
 * normpath() as a way to make them compare the same
 *
 * @param op1 The first argument to ==
 * @param op2 The second argument to ==
 * @return True if the same, false otherwise.
 */
bool operator==(const path::Path &op1, const path::Path & op2)
{
    bool r = (op1.rules() == op2.rules());
    bool c = (op1.canon() == op2.canon());
    return r && c;
}

/**
 * Inverse of operator==()
 *
 * @param op1 Left hand side
 * @param op2 Right hand side
 * @return True if different, false otherwise
 */
bool operator!=(const path::Path &op1, const path::Path &op2)
{
    return !(op1 == op2);
}

/**
 * Print's the raw form of the Path.  See normpath()
 * to get a cleaner version of the Path.
 *
 * @param out Stream to print to
 * @param path Path to be printed
 * @return Returns out
 */
std::ostream &operator<<(std::ostream &out, const path::Path&path)
{
    return out << path.str();
}

/**
 * Add another component to path and return a new Path
 *
 * @param path The path to add to
 * @param dir The directory to add to path
 * @return A new Path
 */
path::Path operator/(const path::Path &path, const char *dir)
{
    return path.add(std::string(dir));

}

/**
 * Add another component to path and return a new Path
 *
 * @param path The path to add to
 * @param dir The directory to add to path
 * @return A new Path
 */
path::Path operator/(const path::Path &path, const std::string &dir)
{
    return path.add(dir);

}

/**
 * Add another component to path and return a new Path
 *
 * @param path The path to add to
 * @param op2 The directory to add to path
 * @return A new path
 */
path::Path operator/(const path::Path &path, const path::Path &op2)
{
    return path.add(op2);
}
