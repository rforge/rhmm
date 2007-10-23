#ifndef _CHMMFIT_HPP_
#define _CHMMFIT_HPP_
#include "cBaumWelchInParam.hpp"
#include "cBaumWelch.hpp"
#include "cDistribution.hpp"
#include "cHmm.hpp"

class cHmmFit : public cBaumWelch, public cHmm
{	public :	
		double	mBic	;
		uint	mNIter	;
		double	mTol	;
		double	mLLH	;
	public :
		cHmmFit(distrDefinitionEnum theDistrType, uint theNClass, uint theDimObs=1, uint theNMixt=0, uint theNProba=0, uint theNSample=1, uint* myT=NULL) ;
		cHmmFit(cInParam& theInParam) ;
		virtual ~cHmmFit() ;
		void BaumWelchAlgo(cBaumWelchInParam& theInParam) ;
		void BaumWelchAlgoInit(cBaumWelchInParam& theInParam) ;
		cHmmFit & operator = (cHmmFit& theSrc) ;
		double ComputeLLH(cBaumWelchInParam& theInParam, cOTMatrix* theProbaCond) ;
		void ComputeFunction(cBaumWelchInParam& theInParam, cOTVector& theValFunct, cOTVector& theh, cOTMatrix* theProbaCond, double theDelta=1e-3) ;
		void ComputeFunction(cBaumWelchInParam& theInParam, cOTMatrix& theValFunct, cOTVector& theh, cOTMatrix* theProbaCond, double theDelta=1e-3) ;
		void ComputeGradient(cBaumWelchInParam& theInParam, cOTVector& theGrad, double theDelta=1e-3) ;
		void ComputeHessian(cBaumWelchInParam& theInPram, cOTMatrix& theHess, double theDelta=1e-3) ;
} ;

#endif // _CHMMFIT_HPP_
