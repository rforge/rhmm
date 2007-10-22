#ifndef _KMEANS_HPP_
#define _KMEANS_HPP_

#include "OTMathUtil.hpp"
#ifndef uint
	typedef unsigned int uint ;
#endif //uint
#ifndef _RDLL_
	#include "R_Equivalents.hpp"
#else
	#include <R.h>
	#include <Rinternals.h>
	#include <Rmath.h>
#endif //_RDLL_


#if defined ( _GSL_ ) && ! defined( _RDLL_ )
	#define _GSL_NO_R_
#endif

#ifdef _GSL_NO_R_
	#include "cRandomGenerator.hpp"
#else
	#define gsl_rng_uniform(p) unif_rand()
	#define gsl_rng int 
#endif // _GSL_NO_R_
extern void mkmeans(cOTVector& theYt, uint theNClass, int* theSeq, gsl_rng* ther = NULL) ;
extern void mkmeans(cOTVector& theYt, uint theNClass, uint theDimObs, int* theSeq, gsl_rng* ther = NULL) ;

#endif // _KMEANS_HPP_


