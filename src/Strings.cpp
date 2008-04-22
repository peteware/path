/*
 *  Strings.cpp
 *  path
 *
 *  Created by Peter Ware on 3/12/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

#include <path/Strings.h>

namespace path 
{
    /**
     * Expand any $VAR by looking up VAR in vars and using
     * the return value.  If VAR is not found, then the
     * empty string is used.  VAR can contain letters, digits, and
     * underscore ('_') (the usual).  To escape a dollar sign, use two
     * dollar signs ('$$').
     *
     * Variables are recursively expanded.
     *
     * @param str The String to be expanded
     * @param vars A std::map from std::string to std::string
     * @return a string with all $VARs expanded.
     */
    std::string expand(const std::string &str, const StringMap &vars)
    {
        std::string     newstr;
        const char      intro = '$';
        
        for (std::string::const_iterator iter = str.begin(); iter != str.end();)
        {
            // Search for a '$'
            if (*iter != intro) 
            {
                newstr += *iter++;
                continue;
            }
            std::string var;
            
            ++iter;
            // Treat $$ as an escape for a single '$'
            if (*iter == intro) 
            {
                newstr += *iter++;
                continue;
            }
            
            // Get the actual variable
            while (iter != str.end() && isalnum(*iter) || *iter == '_')
                var += *iter++;
            StringMap::const_iterator variter = vars.find(var);
            if (variter != vars.end())
                newstr += expand(variter->second, vars);
        }
        return newstr;
    }

}
