/**  
 * @file Unimplemented.h
 */
#if !defined(_PATH_UNIMPLEMENTED_H_)
#define _PATH_UNIMPLEMENTED_H_

#include <path/Exception.h>
#include <string>

namespace path {
    /**
     * @class Unimplemented path/Unimplemented.h
     * The operation is not implemented.
     * 
     */
    class Unimplemented : public Exception
    {
    public:
        Unimplemented(const std::string &operation);
        virtual ~Unimplemented() throw();
    private:
    };
}
#endif // !defined(_PATH_UNIMPLEMENTED_H_)
