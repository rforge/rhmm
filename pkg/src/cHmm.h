/**************************************************************
 *** RHmm version 1.4.3                                     
 ***                                                         
 *** File: cHmm.h 
 ***                                                         
 *** Author: Ollivier TARAMASCO <Ollivier.Taramasco@imag.fr> 
 *** Author: Sebastian BAUER <sebastian.bauer@charite.de>
 *** Date: 2010/12/01                                     
 ***                                                         
 **************************************************************/

#pragma once

#include "Hmm.h"
#include "cInParam.h"
#include "cCyclicVector.h"

class cDistribution ;
class cHmm
{       public :
                distrDefinitionEnum                     mDistrType                      ;
                cOTVector                                       mInitProba                      ;
                cCyclicVector<cOTMatrix>        mTransMatVector         ;
                cDistribution*                          mDistrParam                     ;
        public :
                cHmm(distrDefinitionEnum theDistrType, uint theNClass , uint theDimObs=1 , uint theNMixt=0, uint theNProba=0) ;
                cHmm(const cInParam &theInParam) ;
                virtual ~cHmm() ;
                cHmm & operator =(cHmm& theSrc) ;
                void CopyHmm(cHmm& theSrc) { *this = theSrc ; } ;
                void Print() ;
                uint GetNParam(void) ;
                void SetParam(cOTVector& theParam) ;
                void GetParam(cOTVector& theParam) ;            
} ;
