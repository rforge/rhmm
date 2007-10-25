/***********************************************************
 * RHmm version 0.9.2                                      *
 *                                                         *
 *                                                         *
 * Author: Ollivier TARAMASCO <Ollivier.Taramasco@imag.fr> *
 *                                                         *
 * Date: 2007/10/25                                        *
 *                                                         *
 ***********************************************************/
#ifndef _CINPARAM_HPP_
#define _CINPARAM_HPP_
#include "Hmm.hpp"


class cInParam
{	public :
		distrDefinitionEnum	mDistrType		; // Type de loi de proba
		uint				mNClass			; // Nombre de classes
		uint				mDimObs			; // Dimension des observations
		uint				mNMixt			; // Nombre de lois mélangées
		uint				mNProba			; // Nombre de proba discrètes
		uint				mNSample		; // Nombre d'échantillons
		cOTVector*			mY				; // Tableau mNSample x mT[i] des observations
	public :
		cInParam(uint theNSample, uint theDimObs, cOTVector* theY, distrDefinitionEnum theDistrType=eNormalDistr, uint theNClass=2, uint theNMixt=0, uint theNProba=0) ;
		virtual ~cInParam() ;
		cInParam & operator =(const cInParam &theSrc) ;
		virtual void Print(void) ;
} ;


#endif //_CINPARAM_HPP_
