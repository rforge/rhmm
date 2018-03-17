/**************************************************************
 *** RHmm package
 ***                                                         
 *** File: cOTError.cpp 
 ***                                                         
 *** Author: Ollivier TARAMASCO <Ollivier.Taramasco@imag.fr> 
 *** Author: Sebastian BAUER <mail@sebastianbauer.info>
 ***                                                         
 **************************************************************/

#include "cOTError.h"

cOTError::cOTError(const char *theMess)
{
        if (!theMess)
        {
                theMess = "Unknown error";
        }

#ifndef _RDLL_
        std::cerr << theMess << std::endl;
        exit(0);
#else
        error(theMess);
#endif //_RDLL_
}
