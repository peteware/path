/**
 * @file Refcount.h
 * Implements the reference counted pointer
 *  path
 *
 *  Created by Peter Ware on 6/16/08.
 *  Copyright 2008 Pete Ware, Inc. All rights reserved.
 *
 */

namespace path {
    template<typename Type> class Refcount
    {
    public:
        /// Make this a NULL pointer
        Refcount();
        /// Initialize with first pointer to type Type
        Refcount(Type *ptr);
        /// Copy by incrementing reference count
        Refcount(const Refcount &ref);
        /// Destructor.  Decrement reference count
        ~Refcount();
        
        /// Assignment operator increases referecence count
        Refcount &operator=(const Refcount &op2);
        /// Dereference operator
        Type &operator*();
        /// Derference and access operator
        Type *operator->();
        /// Return how many references
        int count() const;
    private:
        /// Counts the total number of references
        int *   m_count;
        /// The underlying shared object
        Type *  m_data;
        /// Increase the number of references
        void IncReference();
        /// Decrease the number of references
        void DecReference();
    };

    /**
     * Default constructor sets data to NULL and count to 0
     */
    template<typename Type>
    Refcount<Type>::Refcount()
        : m_count(new int),
          m_data(0)
    {
        *m_count = 0;
    }
    
    template<typename Type>
    Refcount<Type>::Refcount(Type *ptr)
        : m_count (new int),
          m_data(ptr)
    {
        *m_count = 1;
    }
    
    template<typename Type>
    Refcount<Type>::Refcount(const Refcount &ref)
        : m_count(ref.m_count),
          m_data(ref.m_data)
    {
        IncReference();
    }
    
    template<typename Type>
    Refcount<Type>::~Refcount()
    {
        DecReference();
    }
    
    template<typename Type>
    Refcount<Type> & Refcount<Type>::operator=(const Refcount &op2)
    {
        DecReference();
        m_count = op2.m_count;
        m_data = op2.m_data;
        IncReference();
        return *this;
    }
    
    template<typename Type>
    inline Type & Refcount<Type>::operator*()
    {
        return *m_data;
    }
    
    template<typename Type>
    inline Type * Refcount<Type>::operator->()
    {
        return m_data;
    }

    template<typename Type>
    int Refcount<Type>::count() const
    {
        if (m_count)
            return *m_count;
        else
            return 0;
    }
    template<typename Type>
    void Refcount<Type>::DecReference()
    {        
        --*m_count;
        if (*m_count <= 0)
        {
            delete m_data;
            delete m_count;
            m_data = 0;
            m_count = 0;
        }
    }
    
    template<typename Type>
    void Refcount<Type>::IncReference()
    {
        if (m_count)
            ++*m_count;
    }
    
}
