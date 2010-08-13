/**
 * @file PathBadException.h
 */
#if !defined(_PATH_PATHBADEXCEPTION_H_)
#define _PATH_PATHBADEXCEPTION_H_

#include <path/PathException.h>

namespace path
{
/**
 * @class PathBadException path/PathBadException.h
 * Handle faults related to PathBadException's.
 */
class PathBadException : public PathException
{
public:
    PathBadException();
    PathBadException(const std::string &path, int err);
    virtual ~PathBadException() throw();

};
}
#endif // !defined(_PATH_PATHBADEXCEPTION_H_)
