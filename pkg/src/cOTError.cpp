/**************************************************************
 *** RHmm version 1.2.1                                      
 ***                                                         
 *** File: cOTError.cpp 
 ***                                                         
 *** Author: Ollivier TARAMASCO <Ollivier.Taramasco@imag.fr> 
 ***                                                         
 *** Date: 2009/04/21                                        
 ***                                                         
 **************************************************************/

#include "cOTError.h"

cOTError::cOTError(char *theMess)
{
	if (theMess != (char *)NULL) 
		std::cout << theMess << std::endl ;
	exit(0) ;
}

