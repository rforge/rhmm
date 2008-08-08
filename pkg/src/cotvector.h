/***********************************************************
 * RHmm version 1.0.4                                      *
 *                                                         *
 *                                                         *
 * Author: Ollivier TARAMASCO <Ollivier.Taramasco@imag.fr> *
 *                                                         *
 * Date: 2008/08/08                                        *
 *                                                         *
 ***********************************************************/
#ifndef _COTVECTOR_H_
#define _COTVECTOR_H_
#ifndef _RDLL_
	#include <iostream>
#endif //_RDLL_
#include "coterror.h"

class cOTMatrix ;

class cOTVector
{
	public :	
		uint	mSize	 ;
		double*	mVect	 ;
	public :
		cOTVector() ;
		cOTVector(uint theSize, double theVal=0.0L) ;
		cOTVector(uint theSize, double* theVect) ;
		virtual ~cOTVector();
		void Delete(void) ;
		void ReAlloc(uint theSize) ;
		void ReAlloc(uint theSize, double theVal) ;
		void ReAlloc(uint theSize, double* theVect) ;
		double& operator[](int theIndex) ;
		cOTVector& operator =(cOTVector& theSrcVect) ;
		cOTVector& operator =(cOTMatrix &theMatrix) ;
		cOTVector& operator =(double theVal) ;
		cOTVector& operator =(double* theVect) ;
		cOTVector& operator +(cOTVector& theVect) ;
		cOTVector& operator +(double theVal) ;
		cOTVector& operator +=(cOTVector& theSrcVect) ;
		cOTVector& operator +=(double theVal) ;
		cOTVector& operator -(cOTVector& theVect) ;
		cOTVector& operator -(double theVal) ;
		cOTVector& operator -=(cOTVector& theSrcVect) ;
		cOTVector& operator -=(double theVal) ;
		cOTVector& operator *(double theLambda) ;
		cOTVector& operator *=(double theLambda) ;
		cOTVector& operator /(double theLambda) ;
		cOTVector& operator /=(double theLambda) ;
		friend bool operator ==(cOTVector& theVect1, cOTVector& theVect2) ;
		friend bool operator <(cOTVector& theVect1, cOTVector& theVect2) ;
		friend bool operator <=(cOTVector& theVect1, cOTVector& theVect2) ;
		friend bool operator >(cOTVector& theVect1, cOTVector& theVect2) ;
		friend bool operator >=(cOTVector& theVect1, cOTVector& theVect2) ;
#ifndef _RDLL_
		friend std::ostream& operator <<(std::ostream& theStream, cOTVector &theVect) ;
#endif // -RDLL_
		friend cOTMatrix& transpose(cOTVector &theVect) ;
		friend cOTVector& zeros(uint theN) ;
		friend cOTVector& copy_double(double* theVect, uint theSize) ;
} ;

#endif //  _COTVECTOR_H_
