/***********************************************************
 * RHmm version 0.9.2                                      *
 *                                                         *
 *                                                         *
 * Author: Ollivier TARAMASCO <Ollivier.Taramasco@imag.fr> *
 *                                                         *
 * Date: 2007/10/25                                        *
 *                                                         *
 ***********************************************************/
#ifndef _COTVECTOR_HPP_
#define _COTVECTOR_HPP_
#include <iostream>
#include "cOTError.hpp"

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
		friend std::ostream& operator <<(std::ostream& theStream, cOTVector &theVect) ;
		friend cOTMatrix& transpose(cOTVector &theVect) ;
		friend cOTVector& zeros(uint theN) ;
		friend cOTVector& copy_double(double* theVect, uint theSize) ;
} ;

#endif //  _COTVECTOR_HPP_
