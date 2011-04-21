/**************************************************************
 *** RHmm version 1.4.9
 ***                                                         
 *** File: cOTError.cpp 
 ***                                                         
 *** Author: Ollivier TARAMASCO <Ollivier.Taramasco@imag.fr> 
 *** Author: Sebastian BAUER <sebastian.bauer@charite.de>
 *** Date: 2011/04/21                                     
 ***                                                         
 **************************************************************/

#include "cOTError.h"

cOTError::cOTError(const char *theMess)
{
        if (theMess != (char *)NULL) 
#ifndef _RDLL_
			std::cout << theMess << std::endl ;
			exit(0) ;
#else
			error(theMess) ;
#endif //_RDLL_

}
