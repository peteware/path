/**  
 * @file NodeInfo.h
 */
#if !defined(_PATH_NODEINFO_H_)
#define _PATH_NODEINFO_H_

#include <sys/types.h>  // Needed for off_t; workaround?

namespace path 
{
    /**
     * Provides basic information about a Node: size, modified time, owner, etc.
     */
    class NodeInfo
    {
    public:
        /**
         * Indicate the type of a file
         */
        enum Type {
            DIRECTORY,  ///< This is a directory
            SYMLINK,    ///< This is a symbolic link
            FILE,       ///< This is a regular file
            DEVICE,     ///< This is a device 
            OTHER,      ///< Not one of the above
        };
        /// Default constructor
        NodeInfo();
        /// Destructor
        virtual ~NodeInfo();
        
        /// Set the size in bytes
        NodeInfo &  setSize(off_t size);
        /// Return the size in bytes
        off_t       size() const;
        /// Set the type of the file
        NodeInfo &  setType(Type type);
        /// Return the actual type of the file
        Type        type() const;
        /// Check if this is a file (FILE, SYMLINK)
        bool        isFile() const;
        /// Check if this is a directory (DIRECTORY)
        bool        isDir() const;
    private:
        off_t       m_size;         ///< Size in bytes
        Type        m_type;         ///< What type of file
        
    };
}
#endif // !defined(_PATH_NODEINFO_H_)
