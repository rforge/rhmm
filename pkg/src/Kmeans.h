/**************************************************************
 *** RHmm version 1.4.3                                     
 ***                                                         
 *** File: Kmeans.h 
 ***                                                         
 *** Author: Ollivier TARAMASCO <Ollivier.Taramasco@imag.fr> 
 *** Author: Sebastian BAUER <sebastian.bauer@charite.de>
 *** Date: 2010/12/01                                     
 ***                                                         
 **************************************************************/

#pragma once

#ifndef _RDLL_

#include "OTMathUtil.h"
#include "REquivalents.h"
#ifndef uint
        typedef unsigned int uint ;
#endif //uint


void mkmeans(cOTVector& theYt, uint theNClass, int* theSeq) ;
void mkmeans(cOTVector& theYt, uint theNClass, uint theDimObs, int* theSeq) ;

#endif //_RDLL_

