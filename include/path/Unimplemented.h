/**  
 * @file Unimplemented.h
 *
 * Implementation of the Class Unimplemented
 *
 * Created on:      11-May-2007 5:09:33 PM
 * Original author: Pete Ware
 */
#if !defined(_PATH_UNIMPLEMENTED_H_)
#define _PATH_UNIMPLEMENTED_H_

#include <exception>
#include <string>

namespace path {
    /**
     * The operation is not implemented.
     * 
     */
    class Unimplemented : public std::exception
    {
        
    public:
        Unimplemented(const std::string &operation);
        virtual ~Unimplemented() throw();
        virtual const char* what() const throw();    
    private:
        std::string     m_what;
    };
}
#endif // !defined(_PATH_UNIMPLEMENTED_H_)
