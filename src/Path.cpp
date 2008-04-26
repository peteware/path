/**
 * @file Path.cpp
 */
#include <path/Path.h>
#include <path/Canonical.h>
#include <path/SysCalls.h>
#include <path/Strings.h>

#include <iostream>

namespace path {
    PathRules * Path::s_defaultPathRules;
    
    /**
     * Initialize an empty Path
     */
    Path::Path(const PathRules *rules)
	: m_path(0),
    m_rules(rules),
    m_canon(0),
    m_pathStr(0)
    {
    }
    
    /**
     * Initialize path, set rules to NULL (i.e. default)
     */
    Path::Path(const char *path)
    : m_path(0),
    m_rules(0),
    m_canon(new Canonical(path)),
    m_pathStr(0)
    {
    }
    
    /**
     * Initialize path, set rules to NULL (i.e. default)
     */
    Path::Path(const std::string &path)
    : m_path(0),
    m_rules(0),
    m_canon(new Canonical(path)),
    m_pathStr(0)
    {
    }
    
    /**
     * Create a path from a Canonical and a PathRules.
     *
     * Initialized m_path by converting from Canonical to a string
     * via the PathRules
     */
    Path::Path(const Canonical &canon, const PathRules *param_rules)
    : m_path(0),
    m_rules(param_rules),
    m_canon(new Canonical(canon)),
    m_pathStr(0)
    {
    }
    
    /**
     * Copy the m_path, make m_rules the same (pointer copy)
     * and duplicate the m_canon.
     */
    Path::Path(const Path &copy)
	:m_path(0),
    m_rules(copy.m_rules),
    m_canon(0),
    m_pathStr(0)
    {
        if (copy.m_path)
            m_path = new std::string(*copy.m_path);
        if (copy.m_canon)
            m_canon = new Canonical (*copy.m_canon);
        if (copy.m_pathStr)
            m_pathStr = new std::string(*copy.m_pathStr);
    }
    
    /**
     * Delete m_canon
     */
    Path::~Path()
    {
        delete m_path;
        delete m_canon;
        delete m_pathStr;
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
        m_rules = op.m_rules;
        
        delete m_canon;
        if (op.m_canon)
            m_canon = new Canonical(*op.m_canon);
        else
            m_canon = 0;
        
        delete m_path;
        if (op.m_path)
            m_path = new std::string(*op.m_path);
        else
            m_path = 0;

        delete m_pathStr;
        if (op.m_pathStr)
            m_pathStr = new std::string(*op.m_pathStr);
        else
            m_pathStr = 0;
        
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
        if (!m_path)
            m_path = new std::string(rules()->str(canon()));
        return *m_path;
    }
    
    /**
     * Same as str() but a NUL terminated string
     */
    const char * Path::str_c() const
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
        if (m_pathStr)
            return *m_pathStr;
        m_pathStr = new std::string(path::expand(rules()->str(canon()), System.env(), true));
        return *m_pathStr;
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
        return Path(Canonical(canon(), entries), m_rules);
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
     * dirname('/a/b/c') returns '/a/b'.  You just be able to do
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
        return Path(c, m_rules);
    }
    
    
    /**
     * Return the extension or suffix on a path.  For example:
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
        std::string::size_type	index = last.str().find_last_of (".");
        if (index == std::string::npos)
            return "";
        else
            return last.str().substr (index, last.str().size() - index);
    }
    
    /**
     * Return basename() of path with the extension() removed
     * @code
     * Path	p("/a/b/name.ext");
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
        Path	base = basename();
        std::string::size_type	index = base.str().find_last_of (".");
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
        return Path(c, m_rules);
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
     * Path	path1("/tmp");
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
        return Path (c, m_rules);
        //return rules()->convert(c);
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
     * @param List of strings to be added
     * @return A new path with the same canonical and the strings added.
     */
    Path Path::add(const Strings &strings) const
    {
        
        Canonical c(canon());
        std::copy(strings.begin(), strings.end(),
                  std::back_inserter(c.components()));
        return Path(c, m_rules);
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
        return Path(c, m_rules);
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
     * would return three vectors: ["/a", "/a/b", "/a/b/c"]
     */
    std::vector<Path> Path::split() const
    {
        const Canonical &      c = canon();
        Canonical              newcanon(c);
        std::vector<Path>       paths;
        
        newcanon.components().clear();
        for (Strings::const_iterator iter = c.components().begin();
             iter != c.components().end(); ++iter)
        {
            newcanon.add(*iter);
            Path    p (newcanon, m_rules);
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
        if (!m_canon)
            m_canon = new Canonical();
        return *m_canon;
    }
    
    /**
     * Return the PathRules used by the Path.  May
     * be NULL.  Do not delete the returned rules.
     */
    const PathRules *Path::pathRules() const
    {
        return m_rules;
    }
    
    /**
     * Returns a default set of rules.  If the rules
     * are not set, it uses the default rules.  If
     * the default rules have not been initialized,
     * it uses UnixRules::rules (as returned by
     * defaultPathRules()).
     *
     * Do not delete the returned rules!
     */
    const PathRules *Path::rules() const
    {
        if (m_rules)
            return m_rules;
        else
            return defaultPathRules();
    }
    
    
    /**
     * Sets the default path rules to be used by any newly created Path objects.
     * 
     * This should be done at compile time to match the operations on the system.
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
     * is usually initialized at compile time to refer to the
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
     * Return the current working directory as an absolute path.
     */
    Path Path::getcwd()
    {
        return Path(System.rules()->canonical(System.getcwd()));
    }
    
    /**
     * Create all the directories along the path.
     *
     * @param path The path to create
     */
    void Path::mkdirs(const Path &path)
    {
        std::vector<Path> hier = path.expand().split();
        for (std::vector<Path>::iterator iter = hier.begin();
             iter != hier.end(); ++iter)
        {
            if (System.exists(iter->path()))
                continue;
            System.mkdir(iter->path(), 0777);
        }
    }

    /**
     * Create any directories along the path and make
     * create the file.
     *
     * @param path The file to make sure it exists.
     */
    void Path::mkfile(const Path &path)
    {
        mkdirs(path.dirname());
        System.touch(path.path());
    }
    
    /**
     * This is useful for things like adding a version
     * number or changing the extension of a file.  For example:
     *
     * @code
     * Path     header(UnixPath("/a/b/file.h"));
     * Path     src = header.dirname() + header.stem() & ".C";
     * Path     backup = src & ".bak";
     * @endcode
     *
     * @param append String to be added
     * @return A new Path with the same rules.
     */
    Path Path::operator&(const std::string &append) const
    {
        Canonical c(canon());
        
        if (c.components().size() > 0)
            c.components()[c.components().size() - 1] += append;
        else
            c.components().push_back(append);
        return Path(c, m_rules);
    }
}
/**
 * Compares the PathRules and Canonical componenets
 * to see if they are the same.  So while two paths
 * might be logically the same, "a" and "/a/b/.." are logically
 * the same, they will not compare equally.  See
 * normpath() as a way to make them compare the same
 * 
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
 */
bool operator!=(const path::Path &op1, const path::Path &op2)
{
	return !(op1 == op2);
}

/**
 * Print's the raw form of the Path.  See normpath() 
 * to get a cleaner version of the Path.  
 */
std::ostream &operator<<(std::ostream &out, const path::Path&path)
{
	return out << path.path();
}

/**
 * Add another component to path and return a new one
 *
 * @param path The path to add to
 * @param dir The directory to add to path
 * @return A new Path
 */
path::Path operator+(const path::Path &path, const std::string &dir)
{
    return path.add(dir);
    
}
/**
 * Add another component to path and return a new one
 *
 * @param path The path to add to
 * @param dir The directory to add to path
 * @return A new Path
 */
path::Path operator+(const path::Path &path, const char *dir)
{
    return path.add(std::string(dir));
    
}

/**
 * Add another component to path and return a new path
 *
 * @param path The path to add to
 * @param op2 The directory to add to path
 * @return A new path
 */
path::Path operator+(const path::Path &path, const path::Path &op2)
{
    return path.add(op2);
}
