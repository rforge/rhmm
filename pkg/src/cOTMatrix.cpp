/**************************************************************
 *** RHmm version 1.4.7                                     
 ***                                                         
 *** File: cOTMatrix.cpp 
 ***                                                         
 *** Author: Ollivier TARAMASCO <Ollivier.Taramasco@imag.fr> 
 *** Author: Sebastian BAUER <sebastian.bauer@charite.de>
 *** Date: 2011/04/07                                     
 ***                                                         
 **************************************************************/

#include "cOTMatrix.h"

cOTVector ourTempVector ;
cOTMatrix ourTempMatrix  ;

cOTVector& cOTVector::operator=(const cOTMatrix& theMatrix)
{
        if (theMatrix.mNCol == 1)
        {	ourTempVector.ReAlloc(theMatrix.mNRow) ;
            for (register uint i = 0 ; i < mSize ; i++)
				ourTempVector.mVect[i] = theMatrix.mMat[i][0] ;
        }
        return ourTempVector ;
}

cOTMatrix& Transpose(cOTVector &theVect)
{
        ourTempMatrix.ReAlloc(1, theVect.mSize) ;
        for (register uint i=0 ; i < theVect.mSize ; i++)
                        ourTempMatrix.mMat[0][i] = theVect[i] ;
        return ourTempMatrix ;
}

cOTMatrix::cOTMatrix(const cOTMatrix &theSrcMatrix)
{
        int i,j;

        mNRow = mNCol = 0 ;
        mMat = (double **)NULL;

        ReAlloc(theSrcMatrix.mNRow, theSrcMatrix.mNCol, 0);

        for (i = 0 ; i < (int)mNRow ; i++)
                for (j = 0 ; j < (int)mNCol ; j++)
                        mMat[i][j] = theSrcMatrix.mMat[i][j] ;
}

cOTMatrix::cOTMatrix(uint theNRow, uint theNCol, double theVal)
{
        if ( (theNRow == 0) && (theNCol == 0) )
        {       mNRow = mNCol = 0 ;
                mMat = (double **)NULL ;
        }
        else
        {       if (theNRow > 0) 
                {       if ( (mMat = new double*[theNRow]) == NULL )
                                throw cOTError("memory allocation problem") ;
                        for (register uint i = 0 ; i < theNRow ; i++)
                        {       if (theNCol > 0)
                                {       if ( (mMat[i] = new double[theNCol]) == NULL )
                                                throw cOTError("memory allocation problem") ;
                                        for (register uint j = 0 ; j < theNCol ; j++)
                                                mMat[i][j] = theVal ;
                                }
                                else
                                        mMat[i] = (double *)NULL ;
                        }
                        mNRow = theNRow ;
                        mNCol = theNCol ;
                }
                else
                        throw cOTError("NRow must be strictly positive") ;
        }
}

cOTMatrix::~cOTMatrix()
{
        if (mNRow > 0)
        {       for (register uint i = 0 ; i < mNRow ; i++)
                        delete [] mMat[i] ;
                delete [] mMat ;
                mMat = (double **)NULL ;
        }
        mNRow = mNCol = 0 ;
}

void cOTMatrix::Delete(void)
{
        for (register uint i = 0 ; i < mNRow ; i++)
                delete [] mMat[i] ;
        if (mMat != NULL)
                delete [] mMat ;
        mMat = (double **)NULL ;
        mNRow = mNCol = 0 ;
}

void cOTMatrix::ReAlloc(uint theNRow, uint theNCol, double theVal)
{
uint    i       ;
        Delete() ;

        if ( (theNRow > 0) && (theNCol > 0) )
        {       if ( (mMat = new double*[theNRow]) == NULL)
                        throw cOTError("memory allocation problem");
                mNRow = theNRow ;
                for (i = 0 ; i < mNRow ; i++)
                        if ( (mMat[i] = new double[theNCol]) == NULL)
                                throw cOTError("memory allocation problem") ;
                        else
                                for (register uint j = 0 ; j < theNCol ; j++)
                                        mMat[i][j] = theVal ;
                mNCol = theNCol ;
        }
}

double* & cOTMatrix::operator [](uint theNRow)
{
        if (theNRow < mNRow)
                return mMat[theNRow] ;
        else
                throw cOTError("bad index") ;
}

cOTMatrix& cOTMatrix::operator =(const cOTMatrix& theSrcMatrix)
{
register uint   i,
                                j       ;

        if (mNRow == 0)
        {       if ( (mMat = new double*[theSrcMatrix.mNRow]) == NULL)
                        throw cOTError("memory allocation problem") ;
                mNRow = theSrcMatrix.mNRow ;
                for (i = 0 ; i < mNRow ; i++)
                        if ( (mMat[i] = new double[theSrcMatrix.mNCol]) == NULL)
                                throw cOTError("memory allocation problem") ;
                mNCol = theSrcMatrix.mNCol ;
        }
        else
        {       if ( (mNRow != theSrcMatrix.mNRow) || (mNCol != theSrcMatrix.mNCol) )
                {       for (i = 0 ; i < mNRow ; i++)
                                delete [] mMat[i]  ;
                        delete [] mMat ;
                        mNRow = theSrcMatrix.mNRow ;
                        mNCol = theSrcMatrix.mNCol ;
                        if ( (mMat = new double*[theSrcMatrix.mNRow]) == NULL)
                                throw cOTError("memory allocation problem") ;
                        for (i = 0 ; i < mNRow ; i++)
                                if ( (mMat[i] = new double[theSrcMatrix.mNCol]) == NULL)
                                        throw cOTError("memory allocation problem") ;
                }
        }
        for (i = 0 ; i < mNRow ; i++)
                for (j = 0 ; j < mNCol ; j++)
                        mMat[i][j] = theSrcMatrix.mMat[i][j] ;
        return *this ;
}

cOTMatrix& cOTMatrix::operator =(cOTVector& theVect)
{
register uint   i       ;
        
        if (mNRow == 0)
        {       if ( (mMat = new double*[theVect.mSize]) == NULL)
                        throw cOTError("memory allocation problem") ;
                mNRow = theVect.mSize ;
                for (i = 0 ; i < mNRow ; i++)
                        if ( (mMat[i] = new double[1]) == NULL)
                                throw cOTError("memory allocation problem") ;
                mNCol = 1 ;
        }
        else
        {       if ( (mNRow != theVect.mSize) || (mNCol != 1) )
                {       for (i = 0 ; i < mNRow ; i++)
                                delete [] mMat[i]  ;
                        delete [] mMat ;
                        mNRow = theVect.mSize;
                        mNCol = 1 ;
                        if ( (mMat = new double*[mNRow]) == NULL)
                                throw cOTError("memory allocation problem") ;
                        for (i = 0 ; i < mNRow ; i++)
                                if ( (mMat[i] = new double[1]) == NULL)
                                        throw cOTError("memory allocation problem") ;
                }
        }
        for (i = 0 ; i < mNRow ; i++)
                mMat[i][0] = theVect[i] ;
        return *this ;
}

cOTMatrix& cOTMatrix::operator =(double theVal)
{
        if ( (mNRow > 0) && (mNCol > 0) )
        {       for (register uint i = 0 ; i < mNRow ; i++)
                        for (register uint j = 0 ; j < mNCol ; j++)
                                mMat[i][j] = theVal ;
        }
        return *this ;
}

cOTMatrix& cOTMatrix::operator +(cOTMatrix& theMatrix)
{	ourTempMatrix = *this ;
	ourTempMatrix += theMatrix ;
	return ourTempMatrix ;
}

cOTMatrix& cOTMatrix::operator +=(cOTMatrix& theMatrix)
{       if ( (theMatrix.mNCol == mNCol) && (theMatrix.mNRow == mNRow) )
        {       for (register uint i = 0 ; i < mNRow ; i++)
                        for (register uint j = 0 ; j < mNCol ; j++)
                                mMat[i][j] += theMatrix.mMat[i][j] ;
                return *this ;
        }
        else
                throw cOTError("wrong matrices size") ;
}

cOTMatrix& cOTMatrix::operator -(cOTMatrix& theMatrix)
{	ourTempMatrix = *this ;
	ourTempMatrix -= theMatrix ;
	return ourTempMatrix ;
}

cOTMatrix& cOTMatrix::operator -=(cOTMatrix& theMatrix)
{       if ( (theMatrix.mNCol == mNCol) && (theMatrix.mNRow == mNRow) )
        {       for (register uint i = 0 ; i < mNRow ; i++)
                        for (register uint j = 0 ; j < mNCol ; j++)
                                mMat[i][j] -= theMatrix.mMat[i][j] ;
                return *this ;
        }
        else
                throw cOTError("wrong matrices size") ;
}

cOTMatrix& operator *(cOTMatrix& theLeft, cOTMatrix &theRight)
{       
	ourTempMatrix.ReAlloc(theLeft.mNRow, theRight.mNCol) ;
	if ( (theLeft.mNCol == theRight.mNRow) )
    {	for (register uint i = 0 ; i < theLeft.mNRow ; i++)
			for (register uint j = 0 ; j < theRight.mNCol ; j++)
				for (register uint k = 0 ; k < theLeft.mNCol ; k++)
					ourTempMatrix.mMat[i][j] += theLeft[i][k] * theRight[k][j] ;
		return ourTempMatrix ;
	}
    else
		throw cOTError("wrong matrices size") ;
}

cOTMatrix& cOTMatrix::operator *=(cOTMatrix& theMatrix)
{       
	*this = *this * theMatrix ;
	return *this ;
}

std::ostream& operator <<(std::ostream& theStream, cOTMatrix& theMat)
{
register uint   i,
                                j       ;
        for (i = 0 ; i < theMat.mNRow ; i++)
        {       for (j = 0 ; j < theMat.mNCol-1 ; j++)
                        theStream << theMat[i][j] << "\t" ;
                theStream << theMat[i][j] << std::endl ;
        }
        return theStream ;
}

cOTVector& operator *(cOTMatrix& theLeft, cOTVector& theVect)
{
        if (theLeft.mNCol == theVect.mSize)
        {       ourTempVector.ReAlloc(theLeft.mNRow) ;
                for (register uint i = 0 ; i < theLeft.mNRow ; i++)
                        for (register uint k= 0 ; k < theLeft.mNCol ; k++)
                                ourTempVector.mVect[i] += theLeft[i][k] * theVect[k] ;
                return ourTempVector ;
        }
        else
                throw cOTError("wrong matrix or vector size") ;
}

cOTMatrix& operator *(cOTVector& theVect, cOTMatrix& theRight)
{
        if (theRight.mNRow == 1)
        {       ourTempMatrix.ReAlloc(theVect.mSize, theRight.mNCol) ;
                for (register uint i = 0 ; i < theVect.mSize ; i++)
                        for (register uint j = 0 ; j < theRight.mNCol ; j++)
                                ourTempMatrix.mMat[i][j] += theVect[i]*theRight[0][j] ;
                return ourTempMatrix ;
        }
        else
                throw cOTError("wrong matrix or vector size") ; 
}

cOTMatrix& operator *(cOTMatrix& theMatrix, double theLambda)
{       
	 ourTempMatrix = theMatrix ;
	 ourTempMatrix *= theLambda ;
     return ourTempMatrix ;
}

cOTMatrix& operator *(double theLambda, cOTMatrix& theMatrix)
{
	 ourTempMatrix = theMatrix ;
	 ourTempMatrix *= theLambda ;
     return ourTempMatrix ;
}

cOTMatrix& cOTMatrix::operator *=(double theLambda)
{       
        for (register uint i = 0 ; i < mNRow ; i++)
                        for (register uint j = 0 ; j < mNCol ; j++)
                                        mMat[i][j] *= theLambda ;       
        return *this ;
}

cOTMatrix& cOTMatrix::operator /(double theLambda)
{       
 	 ourTempMatrix = *this ;
	 ourTempMatrix /= theLambda ;
     return ourTempMatrix ;
}

cOTMatrix& cOTMatrix::operator /=(double theLambda)
{       
        for (register uint i = 0 ; i < mNRow ; i++)
                        for (register uint j = 0 ; j < mNCol ; j++)
                                        mMat[i][j] /= theLambda ;       
        return *this ;
}

cOTMatrix& Transpose(cOTMatrix &theMatrix)
{

        ourTempMatrix.ReAlloc(theMatrix.mNCol, theMatrix.mNRow) ;
        for (register uint i=0 ; i < theMatrix.mNRow ; i++)
                for (register uint j = 0 ; j < theMatrix.mNCol ; j++)
                        ourTempMatrix.mMat[j][i] = theMatrix.mMat[i][j] ;
        return ourTempMatrix ;
}

cOTMatrix& Zeros(uint theN, uint theP)
{
	ourTempMatrix.ReAlloc(theN, theP) ;
	return ourTempMatrix ;
}

cOTMatrix& Identity(uint theN)
{
	ourTempMatrix.ReAlloc(theN, theN) ;
        for (register uint i=0 ; i < theN ; i++)
                ourTempMatrix.mMat[i][i] = 1.0L ;
        return ourTempMatrix ;
}

cOTMatrix& Diag(cOTVector &theVect)
{
	ourTempMatrix.ReAlloc(theVect.mSize, theVect.mSize) ;
        for (register uint i = 0 ; i < theVect.mSize ; i++)
                ourTempMatrix.mMat[i][i] = theVect.mVect[i] ;

        return ourTempMatrix ;
}

cOTMatrix& Inv(cOTMatrix &theMatrix)
{
        ourTempMatrix.ReAlloc(theMatrix.mNRow, theMatrix.mNCol) ;
double myDet ;

        LapackInvAndDet(theMatrix, ourTempMatrix, myDet) ;
        if (std::fabs(myDet) < MIN_DBLE)
                        throw cOTError("Non inversible matrix") ;
        return ourTempMatrix ;
}

void LapackInvAndDet(cOTMatrix& theMatrix, cOTMatrix& theInvMatrix, double& theDet)
{
double *myAP = new double[theMatrix.mNCol*(theMatrix.mNCol + 1)/2],
                *myW = new double[theMatrix.mNCol],
                *myZ = new double[theMatrix.mNCol*theMatrix.mNCol],
                *myWork = new double[theMatrix.mNCol * 3] ;
int myInfo,
        myN = (int)(theMatrix.mNCol),
        myldz = (int)(theMatrix.mNCol) ;

        for (register int i = 0 ; i < myN ; i++)
                for (register int j = i ; j < myldz ; j++)
                        myAP[i+(j+1)*j/2]  = theMatrix[i][j] ;

        F77_NAME(dspev)("V", "U", &myN, myAP, myW, myZ, &myldz, myWork, &myInfo) ;

        if (myInfo != 0)
                throw cOTError("Non inversible matrix") ;
        theDet = 1.0L ;
cOTVector myInvEigenValue = cOTVector(theMatrix.mNCol) ;

cOTMatrix myEigenVector(theMatrix.mNCol, theMatrix.mNCol) ;
        for (register uint i = 0 ; i < theMatrix.mNCol ; i++)
        {       theDet *= myW[i] ;
                myInvEigenValue[i] = 1.0 /myW[i] ;
                for (register int j = 0 ; j < myN ; j++)
                        myEigenVector[i][j] = myZ[i + j*myN] ;
        }
        theInvMatrix =  myEigenVector * Diag(myInvEigenValue) * Transpose(myEigenVector);
        
        delete [] myAP ;
        delete [] myW ;
        delete [] myZ ;
        delete [] myWork ;

}

