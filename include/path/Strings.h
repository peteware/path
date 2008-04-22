/*
 *  Strings.h
 *  path
 *
 *  Created by Peter Ware on 3/12/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef _PATH_STRINGS_H_
#define _PATH_STRINGS_H_

#include <vector>
#include <string>
#include <map>
namespace path {
    /// A vector of strings
    typedef std::vector<std::string> Strings;
    /// Mapping from one string to another.
    typedef std::map<std::string, std::string> StringMap;
}
#endif /* _PATH_STRINGS_H_ */
