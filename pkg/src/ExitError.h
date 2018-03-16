/**************************************************************
 *** RHmm package
 ***                                                         
 *** File: ExitError.h 
 ***                                                         
 *** Author: Ollivier TARAMASCO <Ollivier.Taramasco@imag.fr> 
 *** Author: Sebastian BAUER <mail@sebastianbauer.info>
 ***                                                         
 **************************************************************/

#ifndef _EXITERROR_H_
#define _EXITERROR_H_

#include "cOTError.h"

inline void myAssert(bool theTest, const char* theMess) {if (!theTest) throw cOTError(theMess) ; }

#endif //_EXITERROR_H_
