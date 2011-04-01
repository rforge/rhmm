/**************************************************************
 *** RHmm version 1.4.5                                     
 ***                                                         
 *** File: Kmeans.h 
 ***                                                         
 *** Author: Ollivier TARAMASCO <Ollivier.Taramasco@imag.fr> 
 *** Author: Sebastian BAUER <sebastian.bauer@charite.de>
 *** Date: 2011/03/31                                     
 ***                                                         
 **************************************************************/

#ifndef _KMEANS_H_
#define _KMEANS_H_
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

#endif //_KMEANS_H_
