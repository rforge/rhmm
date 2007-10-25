/***********************************************************
 * RHmm version 0.9.2                                      *
 *                                                         *
 *                                                         *
 * Author: Ollivier TARAMASCO <Ollivier.Taramasco@imag.fr> *
 *                                                         *
 * Date: 2007/10/25                                        *
 *                                                         *
 ***********************************************************/
#ifndef _CRANDOMGENERATOR_HPP_
#define _CRANDOMGENERATOR_HPP_
#ifdef _GSL_
#include <gsl/gsl_rng.h>
	class cRandomGenerator
	{	public :
			const gsl_rng_type	*mT	;
			gsl_rng				*mr	;
		public :
			cRandomGenerator() ;
			~cRandomGenerator() ;
	} ;
#endif // _GSL_
#endif //_CRANDOMGENERATOR_HPP_
