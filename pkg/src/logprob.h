/**************************************************************
 *** RHmm version 1.4.9
 ***                                                         
 *** File: logprob.h 
 ***                                                         
 *** Author: Ollivier TARAMASCO <Ollivier.Taramasco@imag.fr> 
 *** Author: Sebastian BAUER <sebastian.bauer@charite.de>
 *** Date: 2011/04/21                                     
 ***                                                         
 **************************************************************/

#ifndef _LOGPROB_H_
#define _LOGPROB_H_
#include <cfloat>
#include <cmath>
#include "math.h"
        #define LOGZERO -DBL_MAX
#ifndef MIN
        #define MIN(p,q) ((p) < (q) ? (p) : (q))
#endif //MIN
#ifndef MAX
        #define MAX(p,q) ((p) > (q) ? (p) : (q))
#endif //MAX
extern double eexp(double theX) ;
extern double eln(double theX) ;
extern double elnsum(double theX, double theY) ;
extern double elnproduct(double theX, double theY) ;

#endif // _LOGPROB_H_


