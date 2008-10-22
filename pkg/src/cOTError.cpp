/**************************************************************
 *** RHmm version 1.1.0                                      
 ***                                                         
 *** File: cOTError.cpp 
 ***                                                         
 *** Author: Ollivier TARAMASCO <Ollivier.Taramasco@imag.fr> 
 ***                                                         
 *** Date: 2008/10/21                                        
 ***                                                         
 **************************************************************/

#include "cOTError.h"

cOTError::cOTError(char *theMess)
{
	if (theMess != (char *)NULL) 
#ifndef _RDLL_
		cout << theMess << std::endl ;
#else
		Rprintf("%s\n", theMess) ;
#endif // _RDLL_
		exit(0) ;
}

