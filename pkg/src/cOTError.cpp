/**************************************************************
 *** RHmm version 1.4.1                                      
 ***                                                         
 *** File: cOTError.cpp 
 ***                                                         
 *** Author: Ollivier TARAMASCO <Ollivier.Taramasco@imag.fr> 
 *** Author: Sebastian BAUER <sebastian.bauer@charite.de>
 *** Date: 2010/11/27                                      
 ***                                                         
 **************************************************************/

#include "cOTError.h"

cOTError::cOTError(char *theMess)
{
	if (theMess != (char *)NULL) 
		std::cout << theMess << std::endl ;
	exit(0) ;
}

