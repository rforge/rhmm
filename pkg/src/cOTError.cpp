#include "cOTError.hpp"

cOTError::cOTError(char *theMess)
{
	if (theMess != (char *)NULL) 
		std::cout << theMess << std::endl ;
	exit(0) ;
}

