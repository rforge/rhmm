/***********************************************************
 * RHmm version 1.1.0                                      *
 *                                                         *
 *                                                         *
 * Author: Ollivier TARAMASCO <Ollivier.Taramasco@imag.fr> *
 *                                                         *
 * Date: 2008/10/17                                        *
 *                                                         *
 ***********************************************************/
#include "coterror.h"

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

