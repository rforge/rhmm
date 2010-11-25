/**************************************************************
 *** RHmm version 1.4.1                                      
 ***                                                         
 *** File: cCyclicVector.h 
 ***                                                         
 *** Author: Ollivier TARAMASCO <Ollivier.Taramasco@imag.fr> 
 *** Author: Sebastian BAUER <sebastian.bauer@charite.de>
 *** Date: 2010/11/27                                      
 ***                                                         
 **************************************************************/

 #include <vector>

#include "Hmm.h"

template<class T>
class cCyclicVector : public std::vector<T>
{
public:
    typename std::vector<T>::reference operator[](int __n)
    {
        return std::vector<T>::at(__n % std::vector<T>::size());
    }

    cCyclicVector & operator=(const cCyclicVector &rhs)
    {
        if (this == &rhs)      // Same object?
                return *this;

        this->clear();
        for (int i=0;i<rhs.size();i++)
            this->push_back(rhs.at(i));

        return *this;
    }
};
