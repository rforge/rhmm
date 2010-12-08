/**************************************************************
 *** RHmm version 1.4.4                                     
 ***                                                         
 *** File: cRandomGenerator.h 
 ***                                                         
 *** Author: Ollivier TARAMASCO <Ollivier.Taramasco@imag.fr> 
 *** Author: Sebastian BAUER <sebastian.bauer@charite.de>
 *** Date: 2010/12/08                                     
 ***                                                         
 **************************************************************/

#ifndef _ CRANDOMGENERATOR_H_ 
#define _CRANDOMGENERATOR_H_ 
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

#endif //_CRANDOMGENERATOR_H_ 
