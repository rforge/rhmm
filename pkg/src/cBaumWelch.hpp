#ifndef _CBAUMWELCH_HPP_
#define _CBAUMWELCH_HPP_
#include "cInParam.hpp"
#include "cHmm.hpp"

class cBaumWelch
{	private :
			uint	mvNSample		;
			uint*	mvT				;
	public :						;
			cOTMatrix*	mAlpha		;
			cOTMatrix*	mBeta		;
			cOTVector*	mRho		;
			cOTMatrix*	mGamma		;
			cOTMatrix*	mXsi		;
			cOTVector	mLogVrais	;
	public :
		cBaumWelch(uint theNSample, uint* theT, uint theNClass) ;
		cBaumWelch(const cInParam &theInParam) ;
		void ForwardBackward(cOTMatrix* theCondProba, cHmm& theHMM) ;
		uint GetSampleSize(uint theN){ return mvT[theN] ;}
		virtual ~cBaumWelch() ;
} ;

#endif // _CBAUMWELCH_HPP_
