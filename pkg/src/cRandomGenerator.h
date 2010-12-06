/**************************************************************
 *** RHmm version 1.4.3                                     
 ***                                                         
 *** File: cRandomGenerator.h 
 ***                                                         
 *** Author: Ollivier TARAMASCO <Ollivier.Taramasco@imag.fr> 
 *** Author: Sebastian BAUER <sebastian.bauer@charite.de>
 *** Date: 2010/12/01                                     
 ***                                                         
 **************************************************************/

#pragma once

#ifdef _GSL_
#include <gsl/gsl_rng.h>
        class cRandomGenerator
        {       public :
                        const gsl_rng_type      *mT     ;
                        gsl_rng                         *mr     ;
                public :
                        cRandomGenerator() ;
                        ~cRandomGenerator() ;
        } ;
#endif // _GSL_

