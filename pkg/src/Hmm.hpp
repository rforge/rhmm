#ifndef _HMM_HPP_
#define _HMM_HPP_

#include "OTMathUtil.hpp"


#ifdef _RDLL_
	#include <R.h>
	#include <Rinternals.h>
	#include <Rmath.h>
#else
	#include "kMeans.hpp"
	#include "R_Equivalents.hpp"
#endif //_RDLL_

#if defined ( _GSL_ ) && ! defined( _RDLL_ )
	#define _GSL_NO_R_
#endif

#ifdef _GSL_NO_R_
	#include "cRandomGenerator.hpp"
#else
	#define gsl_rng_uniform(p) unif_rand()
#endif // _GSL_NO_R_

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

