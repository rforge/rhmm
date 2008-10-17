/***********************************************************
 * RHmm version 1.1.0                                      *
 *                                                         *
 *                                                         *
 * Author: Ollivier TARAMASCO <Ollivier.Taramasco@imag.fr> *
 *                                                         *
 * Date: 2008/10/17                                        *
 *                                                         *
 ***********************************************************/
#ifndef _CMIXTUNIVARIATENORMAL_H_
#define _CMIXTUNIVARIATENORMAL_H_
#include "cdistribution.h"

class cMixtUnivariateNormal : public cDistribution
{	private :
		uint	mvNClass	;
		uint	mvNMixt		;
	public :
		cOTVector*	mMean	;
		cOTVector*	mVar	;
		cOTVector*	mp		;
	public :
		cMixtUnivariateNormal(uint theNClass = 0, uint theNMixt = 1) ;
		virtual ~cMixtUnivariateNormal() ;
		virtual void ComputeCondProba(cOTVector* theY, uint theNSample, cOTMatrix* theCondProba)  ;
		virtual void UpdateParameters(cInParam& theInParam, cBaumWelch& theBaumWelch, cOTMatrix* theCondProba=NULL)  ;
		virtual void InitParameters(cBaumWelchInParam &theInParam) ;
		virtual void Print() ;
		virtual void CopyDistr(cDistribution *theSrc) ;
		virtual void GetParam(uint theDeb, cOTVector& theParam) ;
		virtual void SetParam(uint theDeb, cOTVector& theParam) ;
		uint GetNParam(void){ return mvNMixt * 3 - 1  ; }
} ;

#endif //_CMIXTUNIVARIATENORMAL_H_
