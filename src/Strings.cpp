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
        if (iter == str.end())
            break;

        // Search for a '$'
        if (*iter != intro)
        {
            newstr += *iter++;
            continue;
        }

        // We have a '$'
        std::string var;
        std::string fullname;				// used to avoid recursion

        fullname += *iter; // Includes the '$'
        ++iter;
        // Treat $$ as an escape for a single '$'
        if (iter != str.end() && *iter == intro)
        {
            newstr += *iter++;
            continue;
        }

        // Get the actual variable
        bool start = true;
        bool domatch = false;
        char match = ')'; // for matching brace/parenthesis
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
                    fullname += *iter++;
                    continue;
                case '{':
                    match = '}';
                    domatch = true;
                    fullname += *iter++;
                    continue;
                case '[':
                    match = ']';
                    domatch = true;
                    fullname += *iter++;
                    continue;
                default:
                    break;
                }
            }
            if (domatch)
            {
                // We've found the terminating parenthesis
                if (*iter == match)
                {
                    fullname += *iter++;
                    domatch = false;
                    break;
                }
                fullname += *iter;
                var += *iter++;
            }
            else if (isalnum(*iter) || *iter == '_')
            {
                fullname += *iter;
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
            {
                // Avoid expanding $VAR=$VAR
                if (variter->second != fullname)
                    newstr += expand(variter->second, vars, false);
            }
        }
    }
    return newstr;
}

/**
 * Calling this with "//abc/d/e//" returns a vector of
 * "", "", "abc", "d", "e", "", ""
 *
 * @param word The string to split
 * @param sep The character to use to split the path
 * @param strings vector of strings that each component is push_back()'d on
 */
void split(const std::string &word, char sep, Strings &strings)
{
    std::string::size_type  start = 0;
    std::string::size_type  end = 0;

    while (start < word.size() && end != std::string::npos)
    {
        end = word.find_first_of(sep, start);
        strings.push_back(word.substr(start, end - start));
        if (end == word.size() - 1)
            strings.push_back(std::string(""));
        start = end + 1;
    }
}
}
