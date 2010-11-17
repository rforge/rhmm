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
};
