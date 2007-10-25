/***********************************************************
 * RHmm version 0.9.2                                      *
 *                                                         *
 *                                                         *
 * Author: Ollivier TARAMASCO <Ollivier.Taramasco@imag.fr> *
 *                                                         *
 * Date: 2007/10/25                                        *
 *                                                         *
 ***********************************************************/
#include "cOTError.hpp"

cOTError::cOTError(char *theMess)
{
	if (theMess != (char *)NULL) 
		std::cout << theMess << std::endl ;
	exit(0) ;
}

