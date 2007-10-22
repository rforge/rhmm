#ifndef _MULTIVARIATENORMALUTIL_HPP_
#define _MULTIVARIATENORMALUTIL_HPP_
#include "OTMathUtil.hpp"
#ifdef _GSL_
	#include <gsl/gsl_math.h>
	#include <gsl/gsl_blas.h>
	#include <gsl/gsl_matrix.h>
	#include <gsl/gsl_eigen.h>
#endif // _GSL_

#ifndef _RDLL_
	#include "R_Equivalents.hpp"
#else
	#include <stdio.h>
	#include <stdlib.h>
	#include <R.h>
	#include <Rinternals.h>
	#include <Rmath.h>
#endif // _RDLL_


#ifndef SQRT_TWO_PI
	#define SQRT_TWO_PI	2.5066282746310002
#endif //SQRT_TWO_PI
#ifndef uint
	typedef unsigned int uint ;
#endif //int

void SymetricInverseAndDet	(	cOTMatrix&	theMat,
											double&		theDet,
											cOTMatrix&	theInvMat
										) ;
/*void dens_normale_multivariee	(	cOTVector&	thex,
									uint		theDimObs,	// dim de la loi multivariée
									cOTVector&	theMu,
									cOTMatrix&	theCov,
									double*		theDens
								) ;
*/

void MultivariateNormalDensity	(	cOTVector&	thex,
									cOTVector&	theMu,
									cOTMatrix&	theInvCov,
									double		theDet,
									double*		theDens
								) ;

#endif //_MULTIVARIATENORMALUTIL_HPP_

