#ifndef _COTERROR_HPP_
#define _COTERROR_HPP_
#include <iostream>

#ifndef NULL
	#define NULL 0
#endif // NULL

#ifndef uint
	typedef unsigned int uint ;
#endif // uint

class cOTError
{
	public :
		cOTError(char *theMess) ;
} ;

#endif //_COTERROR_HPP_
