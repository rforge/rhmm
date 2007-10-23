#ifndef _CMULTIVARIATENORMAL_HPP_
#define _CMULTIVARIATENORMAL_HPP_
#include "cDistribution.hpp"
#include "samplesUtil.hpp"

class cMultivariateNormal : public cDistribution
{	private :
		uint	mvNClass	;
	public :
		cOTVector*	mMean	;
		cOTMatrix*	mCov	;
	public :
		cMultivariateNormal(uint theNClass = 0, uint theDimObs = 1) ;
		virtual ~cMultivariateNormal() ;
		virtual void ComputeCondProba(cOTVector* theY, uint theNSample, cOTMatrix* theCondProba) ;
		virtual void UpdateParameters(cInParam& theInParam, cBaumWelch& theBaumWelch, cOTMatrix* theCondProba=NULL) ;
		virtual void InitParameters(cBaumWelchInParam &theInParam) ;
		virtual void Print() ;
		virtual void GetParam(uint theDeb, cOTVector& theParam) ;
		virtual void SetParam(uint theDeb, cOTVector& theParam) ;
		uint GetDimObs() ;
		void CopyDistr(cDistribution* theSrc) ;
		uint GetNParam(void){ return mMean[0].mSize + mMean[0].mSize * mMean[0].mSize ; }

} ;

#endif //_CMULTIVARIATENORMAL_HPP_