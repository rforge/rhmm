/***********************************************************
 * RHmm version 0.9.2                                      *
 *                                                         *
 *                                                         *
 * Author: Ollivier TARAMASCO <Ollivier.Taramasco@imag.fr> *
 *                                                         *
 * Date: 2007/10/25                                        *
 *                                                         *
 ***********************************************************/
#ifndef _KMEANS_HPP_
#define _KMEANS_HPP_
#ifndef _RDLL_

#include "OTMathUtil.hpp"
#include "R_Equivalents.hpp"
#ifndef uint
	typedef unsigned int uint ;
#endif //uint


extern void mkmeans(cOTVector& theYt, uint theNClass, int* theSeq) ;
extern void mkmeans(cOTVector& theYt, uint theNClass, uint theDimObs, int* theSeq) ;
#endif //_RDLL_
#endif // _KMEANS_HPP_


