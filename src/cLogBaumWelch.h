/**************************************************************
 *** RHmm version 1.2.1                                      
 ***                                                         
 *** File: cLogBaumWelch.h 
 ***                                                         
 *** Author: Ollivier TARAMASCO <Ollivier.Taramasco@imag.fr> 
 ***                                                         
 *** Date: 2009/04/21                                        
 ***                                                         
 **************************************************************/

#ifndef _CLOGBAUMWELCH_H_
#define _CLOGBAUMWELCH_H_
#include "cInParam.h"
#include "cHmm.h"
#include "logprob.h"

class cLogBaumWelch
{	private :
			uint	mvNSample		;
			uint*	mvT				;
	public :						;
			cOTMatrix*	mLogAlpha	;
			cOTMatrix*	mLogBeta	;
			cOTVector*	mLogRho		;
			cOTMatrix*	mLogGamma	;
			cOTMatrix**	mLogXsi		;
			cOTMatrix*	mSumLogXsi	;
			cOTVector	mLogVrais	;
	public :
		cLogBaumWelch(uint theNSample, uint* theT, uint theNClass) ;
		cLogBaumWelch(const cInParam &theInParam) ;
		void LogForwardBackward(cOTMatrix* theCondProba, cHmm& theHMM) ;
		uint GetSampleSize(uint theN){ return mvT[theN] ;}
		virtual ~cLogBaumWelch() ;
} ;


#endif // _CLOGBAUMWELCH_H_
