/**
 * @file Strings.h
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
/// Return a string with all $VAR replaced
std::string expand(const std::string &str, const StringMap & vars, bool tilde);
/// Split a string with a sperator character
void split(const std::string &str, char sep, Strings &strings);
}
#endif /* _PATH_STRINGS_H_ */
