#ifndef _CDISTRIBUTION_HPP_
#define _CDISTRIBUTION_HPP_
#include "cBaumWelchInParam.hpp"
#include "cBaumWelch.hpp"


class cDistribution  
#ifdef _GSL_NO_R_ 
	: public cRandomGenerator 
#endif // _GSL_NO_R_
{	public :
		virtual void ComputeCondProba(cOTVector* theY, uint theNSample, cOTMatrix* theCondProba)=0 ;
		virtual void UpdateParameters(cInParam& theInParam, cBaumWelch& theBaumWelch, cOTMatrix* theCondProba=NULL)=0 ;
		virtual void InitParameters(cBaumWelchInParam& theInParam)=0 ;
		virtual void Print() = 0 ;
		virtual void CopyDistr(cDistribution* theSrc)=0 ;
		virtual uint GetNParam(void)=0;
		virtual void GetParam(uint theDeb, cOTVector& theParam)=0 ;
		virtual void SetParam(uint theDeb, cOTVector& theParam)=0 ;
#ifndef _RDLL_
		void KMeans(cOTVector& theYt, uint theNClass, int* theSeq) {
			#ifdef _GSL_NO_R_
				mkmeans(theYt, theNClass, theSeq, mr) ;
			#else
				mkmeans(theYt, theNClass, theSeq) ;
			#endif // _GSL_NO_R_
		} ;
		void KMeans(cOTVector& theYt, uint theNClass, uint theDimObs, int* theSeq) {
			#ifdef _GSL_NO_R_
				mkmeans(theYt, theNClass, theDimObs, theSeq, mr) ;
			#else
				mkmeans(theYt, theNClass, theDimObs, theSeq) ;
			#endif //_GSL_NO_R_ 
		} ;
#endif // _RDLL_

} ;

#endif //_CDISTRIBUTION_HPP_