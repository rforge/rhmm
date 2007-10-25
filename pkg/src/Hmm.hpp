/***********************************************************
 * RHmm version 0.9.2                                      *
 *                                                         *
 *                                                         *
 * Author: Ollivier TARAMASCO <Ollivier.Taramasco@imag.fr> *
 *                                                         *
 * Date: 2007/10/25                                        *
 *                                                         *
 ***********************************************************/
#ifndef _HMM_HPP_
#define _HMM_HPP_

#include "OTMathUtil.hpp"


#ifdef _RDLL_
	#include <R.h>
	#include <Rinternals.h>
	#include <Rmath.h>
#else
	#include "kmeans.hpp"
	#include "R_Equivalents.hpp"
	#include "cRandomGenerator.hpp"
#endif //_RDLL_


#ifndef SQRT_TWO_PI
	#define SQRT_TWO_PI	2.5066282746310002
#endif // SQRT_TWO_PI

#ifndef MAX
	#define	MAX(p,q) ((p) > (q) ? (p) : (q))
#endif //MAX

typedef unsigned int uint ;
typedef enum distrDefinitionEnum
{	eUnknownDistr = -1,
	eNormalDistr = 0,
	eMultiNormalDistr = 1,
	eMixtUniNormalDistr = 2,
	eMixtMultiNormalDistr = 3,
	eDiscreteDistr=4
} ;

typedef enum initEnum
{	eRandom = 0,
	eKMeans = 1,
	eUser = 2
} ;


#endif //_HMM_HPP_

