/***********************************************************
 * RHmm version 0.9.2                                      *
 *                                                         *
 *                                                         *
 * Author: Ollivier TARAMASCO <Ollivier.Taramasco@imag.fr> *
 *                                                         *
 * Date: 2007/10/25                                        *
 *                                                         *
 ***********************************************************/
#ifndef _CHMM_HPP_
#define _CHMM_HPP_
#include "Hmm.hpp"
#include "cInParam.hpp"

class cDistribution ;
class cHmm
{	public :
		distrDefinitionEnum	mDistrType	;
		cOTVector			mInitProba	;
		cOTMatrix			mTransMat	;	
		cDistribution*		mDistrParam	;
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



#endif _CHMM_HPP_//