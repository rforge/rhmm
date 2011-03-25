/**************************************************************
 *** RHmm version 1.4.4                                     
 ***                                                         
 *** File: cDiscrete.cpp 
 ***                                                         
 *** Author: Ollivier TARAMASCO <Ollivier.Taramasco@imag.fr> 
 *** Author: Sebastian BAUER <sebastian.bauer@charite.de>
 *** Date: 2010/12/09                                     
 ***                                                         
 **************************************************************/

#include "cDiscrete.h"

cDiscrete::cDiscrete(uint theNClass, uint theNProba) 
{       MESS_CREAT("cDiscrete")
        if ( (theNClass > 0) && (theNProba > 0) )
        {       mvNClass = theNClass ;
                cOTMatrix *emissionMat = new cOTMatrix(theNClass,theNProba,0);
                mProbaMatVector.push_back(*emissionMat);
        }
        else
        {       mvNClass = 0 ; 
        }
}

cDiscrete::~cDiscrete()
{       MESS_DESTR("cDiscrete")
        if ( mvNClass > 0)
        {
        	fprintf(stderr,"***Implement me!\n");
        }
        mvNClass = 0 ;
}
uint cDiscrete::GetNProba(void)
{
        if (mvNClass > 0)
        		return mProbaMatVector[0].mNCol ;
        else
                return 0 ;
}

void cDiscrete::Print()
{
fprintf(stderr,"***Implement me!\n");
exit(0);
//        for (register uint i = 0 ; i < mvNClass ; i++)
//        {       Rprintf("State %d :\t", i) ;
//                for (register uint j = 0 ; j < GetNProba() ; j++)
//                        Rprintf("P[%d]=%lf\t", j, mProba[i][j]) ;
//                Rprintf("\n") ;
//        }
}

void cDiscrete::ComputeCondProba(cOTVector* theY, uint theNSample, cOTMatrix* theCondProba)
{
register uint   i,
                                n,
                                t       ;

        for (n = 0 ; n < theNSample ; n++)
        {
                for (i = 0 ; i < mvNClass ; i++)
                {
                	for (t = 0 ; t < theY[n].mSize ; t++)
                		theCondProba[n][i][t] = mProbaMatVector[t][i][(uint)theY[n][t]];
                }
        }
}

void cDiscrete::UpdateParameters(cInParam& theInParam, cBaumWelch& theBaumWelch, cOTMatrix* theCondProba)
{
fprintf(stderr,"***Implement me!\n");
exit(0);
//register uint   i       ;
//uint myNProba = GetNProba() ;
//        for (i = 0 ; i < mvNClass ; i++)
//        {       double myDenominateur = 0.0 ;
//                register uint   n,
//                                                t       ;
//                for (n = 0 ; n < theInParam.mNSample ; n++)
//                        for (t = 0 ; t < theInParam.mY[n].mSize  ; t++)
//                                myDenominateur += theBaumWelch.mGamma[n][i][t] ;
//
//                for (register uint k = 0 ; k < myNProba ; k++)
//                {       mProba[i][k] = 0.0 ;
//                        for (n = 0 ; n < theInParam.mNSample ; n++)
//                                for ( t = 0 ; t < theInParam.mY[n].mSize ; t++)
//                                        mProba[i][k] += theBaumWelch.mGamma[n][i][t]*(theInParam.mY[n][t]==k) ;
//                        if (myDenominateur > MIN_DBLE)
//                                mProba[i][k] /= myDenominateur ;
//                        else
//                                mProba[i][k] = 0.0L ;
//                }
//        }
}

void cDiscrete::InitParameters(cBaumWelchInParam& theInParam)
{
#ifdef _RDLL_
        GetRNGstate();
#endif //_RDLL_
fprintf(stderr,"***Implement me!\n");
exit(0);

//register uint   i                       ;
//uint myNProba = GetNProba() ;
//        for (i = 0 ; i < mvNClass ; i++)
//        {       register uint   j                       ;
//                double                  mySum = 0.0 ;
//                for(j = 0 ; j < myNProba ; j++)
//                {       mProba[i][j] =  unif_rand() ;
//                        mySum += mProba[i][j] ;
//                }
//                mProba[i] /= mySum ;
//        }

#ifdef _RDLL_
        PutRNGstate() ;
#endif //_RDLL_
}
void cDiscrete::CopyDistr(cDistribution* theSrc)
{
fprintf(stderr,"***Implement me!\n");
exit(0);
//        cDiscrete *mySrc = (cDiscrete *)theSrc ;
//
//        mvNClass = mySrc->mvNClass ;
//        for (register uint i=0 ; i < mvNClass ; i++)
//                mProba[i] = mySrc->mProba[i] ;
}


void cDiscrete::GetParam(uint theDeb, cOTVector& theParam)
{
fprintf(stderr,"***Implement me!\n");
exit(0);
//uint myNProba = this->GetNProba();
//register uint k = theDeb ;
//        for (register uint n = 0 ; n < mvNClass ; n++)
//                for (register uint p = 0 ; p < myNProba - 1 ; p++)
//                        theParam[k++] = mProba[n][p] ;
}
void cDiscrete::SetParam(uint theDeb, cOTVector& theParam)
{
fprintf(stderr,"***Implement me!\n");
exit(0);
//uint myNProba = GetNProba() ;
//register uint k = theDeb ;
//        for (register uint n = 0 ; n < mvNClass ; n++)
//        {       mProba[n][myNProba-1] = 1.0L ;
//                for (register uint p = 0 ; p < myNProba - 1 ; p++)
//                {       mProba[n][p]  = theParam[k++] ;
//                        mProba[n][myNProba-1] -= mProba[n][p] ;
//                }
//        }
}
