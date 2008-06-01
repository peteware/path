/**
 *  @file Strings.cpp
 */
#include <path/Strings.h>

namespace path 
{
    /**
     * Expand any $VAR by looking up VAR in vars and using
     * the return value.  If VAR is not found, then the
     * empty string is used.  VAR can contain letters, digits, and
     * underscore ('_') (the usual).  To escape a dollar sign, use two
     * dollar signs ('$$').  If you include the variable name in parenthesis,
     * then any characters are ok: $(A $ %).  '[]' and '{}' work
     * if you need more characters.
     *
     * Variables are recursively expanded.  So if the expansion includes
     * a variable, that variable is also expanded.
     *
     * @param str The String to be expanded
     * @param vars A std::map from std::string to std::string
     * @param tilde True if expand ~ to $HOME (at start)
     * @return a string with all $VARs expanded.
     */
    std::string expand(const std::string &str, const StringMap &vars, bool tilde)
    {
        std::string     newstr;
        const char      intro = '$';
        const char      tilde_char = '~';
        
        for (std::string::const_iterator iter = str.begin(); iter != str.end();)
        {
            if (tilde)
            {
                tilde = false;  // only at the very start
                if (*iter == tilde_char)
                {
                    ++iter;
                    newstr += expand("$HOME", vars, false);
                    continue;
                }
            }
            // Search for a '$'
            if (*iter != intro) 
            {
                newstr += *iter++;
                continue;
            }
            
            // We have a '$'
            std::string var;
            ++iter;
            // Treat $$ as an escape for a single '$'
            if (*iter == intro) 
            {
                newstr += *iter++;
                continue;
            }
            
            // Get the actual variable
            bool start = true;
            bool domatch = false;
            char match; // for matching brace/parenthesis
            while (iter != str.end())
            {
                if (start)
                {
                    start = false;
                    switch (*iter)
                    {
                        case '(':
                            match = ')';
                            domatch = true;
                            ++iter;
                            continue;
                        case '{':
                            match = '}';
                            domatch = true;
                            ++iter;
                            continue;
                        case '[':
                            match = ']';
                            domatch = true;
                            ++iter;
                            continue;
                        default:
                            break;
                    }
                }
                if (domatch)
                {
                    if (*iter == match)
                    {
                        ++iter;
                        domatch = false;
                        break;
                    }
                    else
                    {
                        var += *iter++;
                    }
                }
                else if (isalnum(*iter) || *iter == '_')
                {
                    var += *iter++;
                }
                else
                {
                    break;
                }
                
            }
            if (!domatch)
            {
                StringMap::const_iterator variter = vars.find(var);
                // If we added an else, we could have non-matches expand
                if (variter != vars.end())
                    newstr += expand(variter->second, vars, false);
            }
        }
        return newstr;
    }

}
