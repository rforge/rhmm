/**************************************************************
 *** RHmm package
 ***                                                         
 *** File: cInParam.h 
 ***                                                         
 *** Author: Ollivier TARAMASCO <Ollivier.Taramasco@imag.fr> 
 *** Author: Sebastian BAUER <mail@sebastianbauer.info>
 ***                                                         
 **************************************************************/

#ifndef _CINPARAM_H_
#define _CINPARAM_H_
#pragma once

#include "Hmm.h"


class cInParam
{       public :
                distrDefinitionEnum mDistrType ; // Distribution probability type
                uint mNClass ; // Number of hidden states
                uint mDimObs ; // Dimension des observations
                uint mNMixt ; // Number of mixed distributions
                uint mNProba ; // Number of discrete emission symbols
                uint mNSample ; // Number of observed samples
                cDVector* mY ; // Tableau mNSample x mT[i] des observations
        public :
                cInParam(uint theNSample, uint theDimObs, cDVector* theY, distrDefinitionEnum theDistrType=eNormalDistr, uint theNClass=2, uint theNMixt=0, uint theNProba=0) ;
                virtual ~cInParam() ;
                cInParam & operator =(const cInParam &theSrc) ;
                void Print(void) ;
} ;
#endif //_CINPARAM_H_
