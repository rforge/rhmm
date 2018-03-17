/**************************************************************
 *** RHmm package
 ***                                                         
 *** File: cBaumWelchInParam.h 
 ***                                                         
 *** Author: Ollivier TARAMASCO <Ollivier.Taramasco@imag.fr> 
 *** Author: Sebastian BAUER <mail@sebastianbauer.info>
 ***                                                         
 **************************************************************/

#ifndef _CBAUMWELCHINPARAM_H_
#define _CBAUMWELCHINPARAM_H_
#pragma once

#include "cInParam.h"

class cBaumWelchInParam : public cInParam
{       public :
                initEnum        mInitType               ; // Initialization type
                uint            mNMaxIter               ; // Maximal number of iterations
                double          mTol                    ; // Tolerance for baum welch algorithm
                uint            mNInitIter              ; // Number of iterations for the initialization
                uint            mNMaxIterInit   ; // Maximal number of iterations for the initialization
                uint            mVerbose                ; // verbosity level, 0 quiet, 1 verbose
        public :
                cBaumWelchInParam & operator =(const cBaumWelchInParam &theSrc) ;
                cBaumWelchInParam(uint theNSample=0, uint theDimObs=0, cDVector *theY=NULL, distrDefinitionEnum theDistrType=eNormalDistr, uint theNClass=2, uint theNMixt=0, uint theNProba=0) ;
                void SetDefault(void) ;
                virtual ~cBaumWelchInParam() ;
                void Print(void) ;
} ;
#endif //_CBAUMWELCHINPARAM_H_
