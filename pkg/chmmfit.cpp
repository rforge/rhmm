/***********************************************************
 * RHmm version 1.0.4                                      *
 *                                                         *
 *                                                         *
 * Author: Ollivier TARAMASCO <Ollivier.Taramasco@imag.fr> *
 *                                                         *
 * Date: 2008/08/08                                        *
 *                                                         *
 ***********************************************************/
#include "chmmfit.h"

cHmmFit::cHmmFit(distrDefinitionEnum theDistrType, uint theNClass, uint theDimObs, uint theNMixt, uint theNProba, uint theNSample, uint* myT):cBaumWelch(theNSample, myT, theDimObs), cHmm(theDistrType, theNClass, theDimObs, theNMixt, theNProba)
{	mNIter = 0 ;
	mTol = 1e100 ;
	mBic = -1e100 ;
}
cHmmFit::cHmmFit(cInParam& theInParam):cBaumWelch(theInParam), cHmm(theInParam)
{	mNIter = 0 ;
	mTol = 1e100 ;
	mBic = -1e100 ;
}

cHmmFit::~cHmmFit()
{
}

cHmmFit & cHmmFit::operator = (cHmmFit &theSrc)
{	mLLH = theSrc.mLLH ;
	CopyHmm(theSrc) ;
	mDistrParam->CopyDistr(theSrc.mDistrParam) ;
	return(*this) ;
}

void cHmmFit::BaumWelchAlgo(cBaumWelchInParam& theInParam)
{
uint			myNbIter		;
double			myLogVraisCour,
				myRap			;
register uint	i,
				j,
				n				;
uint			myT = 0			;

cOTMatrix*	myProbaCond = new cOTMatrix[theInParam.mNSample] ; 
	
	for (n = 0 ; n < theInParam.mNSample ; n++)
	{	
	uint mySize = theInParam.mY[n].mSize/theInParam.mDimObs ;
		myT +=  mySize ;
		myProbaCond[n].ReAlloc(theInParam.mNClass, mySize) ;
	}
	mDistrParam->ComputeCondProba(theInParam.mY, theInParam.mNSample, myProbaCond) ;

	ForwardBackward(myProbaCond, *this) ;
	mLLH = 0.0 ;
	for (n = 0 ; n < theInParam.mNSample ; n++)
		mLLH += mLogVrais[n] ;
	myLogVraisCour = mLLH ;

	myNbIter = 0 ;
	if (theInParam.mVerbose > 0)
		Rprintf("Iter num %d - LLH : %10.4lf -  Normalized LLH : %8.6lf\n", myNbIter, mLLH, mLLH/myT) ;

	do
	{	for (i = 0 ; i < theInParam.mNClass ; i++)
		{	mInitProba[i] = 0.0 ;
			for (n = 0 ; n < theInParam.mNSample ; n++)
				mInitProba[i] += mGamma[n][i][0] ;
			mInitProba[i] /= (double)(theInParam.mNSample) ;
		}

		for (i = 0 ; i < theInParam.mNClass ; i++)
		{	double myDenominateur = 0.0 ;
			for (n = 0 ; n < theInParam.mNSample ; n++)
			{	for (register uint t = 0 ; t < GetSampleSize(n)-1 ; t++)
					myDenominateur += mGamma[n][i][t] ;
			}
			for (j = 0 ; j < theInParam.mNClass ; j++)
			{	mTransMat[i][j] = 0.0 ;
				for (n = 0 ; n < theInParam.mNSample ; n++)
					mTransMat[i][j] += mXsi[n][i][j] ;
				mTransMat[i][j] /= myDenominateur ;
			}
		}
		

		mDistrParam->UpdateParameters(theInParam, *this, myProbaCond) ;
		mDistrParam->ComputeCondProba(theInParam.mY, theInParam.mNSample, myProbaCond) ;
		ForwardBackward(myProbaCond, *this) ;
		mLLH = 0.0 ;
		for (n = 0 ; n < theInParam.mNSample ; n++)
			mLLH += mLogVrais[n] ;
	
		myRap = fabs((mLLH - myLogVraisCour)/myLogVraisCour) ;
		myLogVraisCour = mLLH ;
		if (theInParam.mVerbose > 0)
			Rprintf("Iter num %d - LLH : %10.4lf -  Normalized LLH : %8.6lf\n", myNbIter, mLLH, mLLH/myT) ;
		myNbIter++ ;
	}
	while ((myRap > theInParam.mTol) & (myNbIter < theInParam.mNMaxIter)) ;
/* Terminer la matrice de transition */
	for (i = 0 ; i < theInParam.mNClass ; i++)
	{	double mySomme = 0.0 ;
		for (j = 0 ; j < theInParam.mNClass ; j++)
			mySomme += mTransMat[i][j] ;
		for (j = 0 ; j < theInParam.mNClass ; j++)
			mTransMat[i][j] /= mySomme ;
	}
	
	mBic = myLogVraisCour ;
	for (n = 0 ; n < theInParam.mNSample ; n++)
		mBic -= 2*log((double)myT) ;
	mNIter = myNbIter ;
	mTol = myRap ;
	for (i = 0 ; i < theInParam.mNSample ; i++)
		myProbaCond[i].Delete() ;
	delete [] myProbaCond ;
}

void cHmmFit::BaumWelchAlgoInit(cBaumWelchInParam &theInParam)
{
#ifndef _RDLL_
	if (theInParam.mInitType == eKMeans)
	{	
	register uint k ;
	uint myT = 0 ;
		for (k = 0 ; k < theInParam.mNSample ; k++)
			myT += theInParam.mY[k].mSize  ;
	myT /= theInParam.mDimObs ;
	int* mySeq = new int[myT] ;
	cOTVector myY(myT*theInParam.mDimObs) ;
	register uint	t = 0,
					i ;
		for (k = 0 ; k < theInParam.mNSample ; k++)
		{	uint myTT = theInParam.mY[k].mSize * theInParam.mDimObs ;
			for (i = 0 ; i < myTT ; i++)
				myY[t++] = theInParam.mY[k][i] ;
		}
		register uint j ;
		
		mTransMat = 1.0L/(double)(theInParam.mNClass) ;
		
		mInitProba = 1.0/(double)(theInParam.mNClass) ;
		
		mDistrParam->InitParameters(theInParam) ;
		delete mySeq ;
		myY.Delete() ;
		return ;
	}
#else
	GetRNGstate();
#endif _RDLL_

cHmmFit	myHMMFitCour(theInParam),
		myHMM(theInParam)		;
cBaumWelchInParam myParamEntree ;
	myParamEntree = theInParam ;
												;	
double	myLogVraisCour = -1e100 ;
	
	myParamEntree.mNMaxIter = theInParam.mNMaxIterInit  ;

	if (theInParam.mVerbose < 2)
		myParamEntree.mVerbose = 0 ;
	else
		myParamEntree.mVerbose = 2 ;

register uint	t											;
	for (t = 0 ; t < theInParam.mNInitIter ; t++)
	{	double	mySum = 0.0 ;
		register uint i ;
		for (i = 0 ; i < myParamEntree.mNClass ; i++)
		{	myHMMFitCour.mInitProba[i]  = unif_rand() ;
			mySum += myHMMFitCour.mInitProba[i] ;
		}
		myHMMFitCour.mInitProba /= mySum ;
		
		register uint j ;

		for (i = 0 ; i < myParamEntree.mNClass ; i++)
		{	mySum = 0.0 ;
			for (j = 0 ; j < myParamEntree.mNClass ; j++)
			{	myHMMFitCour.mTransMat[i][j] = unif_rand() ;
				mySum += myHMMFitCour.mTransMat[i][j] ;
			}
			for (j = 0 ; j < myParamEntree.mNClass ; j++)
				myHMMFitCour.mTransMat[i][j] /= mySum ;
		}
		
		myHMMFitCour.mDistrParam->InitParameters(myParamEntree) ;

		myHMMFitCour.BaumWelchAlgo(myParamEntree) ;
		if(theInParam.mVerbose > 1)
			Rprintf("Rand init num %d - LLH = %f\n", t, myHMMFitCour.mLLH) ;
		if (myHMMFitCour.mLLH > myLogVraisCour)
		{	myHMM = myHMMFitCour ;
			myLogVraisCour = myHMMFitCour.mLLH ;
		} 
	}
	if (theInParam.mVerbose > 1)
	{	Rprintf("\n Random Initialisation:\n") ;
		myHMM.mDistrParam->Print() ;
		Rprintf("\n") ;
	}
	*this = myHMM ;
	
}


double cHmmFit::ComputeLLH(cBaumWelchInParam &theInParam, cOTMatrix* theProbaCond)
{
	mDistrParam->ComputeCondProba(theInParam.mY, theInParam.mNSample, theProbaCond) ;
	ForwardBackward(theProbaCond, *this) ;
double	myLLH = 0.0 ;
	for (register uint i = 0 ; i < theInParam.mNSample ; i++)
		myLLH += mLogVrais[i] ;
	return myLLH ;
}

void cHmmFit::ComputeFunction(cBaumWelchInParam &theInParam, cOTVector& theValFunct, cOTVector& theh, cOTMatrix* theProbaCond, double theDelta)
{
uint myNParam = GetNParam() ;
	theValFunct = 0.0L ;
	
cOTVector myVectInit(myNParam) ;
	GetParam(myVectInit) ;
cOTVector myVectCour ; 
	for (register uint n = 0 ; n <  myNParam  ; n++)
	{	theh[n] = MAX(fabs(myVectInit[n])*theDelta, theDelta*theDelta) ;
		myVectCour = myVectInit ;
		myVectCour[n] += theh[n] ;
		SetParam(myVectCour) ;
		theValFunct[n] = ComputeLLH(theInParam, theProbaCond)  ;
	}

}

void cHmmFit::ComputeFunction(cBaumWelchInParam &theInParam, cOTMatrix& theValFunct, cOTVector& theh, cOTMatrix* theProbaCond, double theDelta)
{
uint myNParam = GetNParam() ;
	theValFunct = 0.0L ;
	
cOTVector myVectInit(myNParam) ;
	GetParam(myVectInit) ;
cOTVector myVectCour ; 
	for (register uint n = 0 ; n <  myNParam  ; n++)	
			theh[n] = MAX(fabs(myVectInit[n])*theDelta, theDelta*theDelta) ;
	for (register uint n = 0 ; n < myNParam ; n++)
		for (register uint p = n ; p < myNParam ; p++)
		{		myVectCour = myVectInit ;
				myVectCour[n] += theh[n] ;
				myVectCour[p] += theh[p] ;
				SetParam(myVectCour) ;
				theValFunct[n][p] = theValFunct[p][n] = ComputeLLH(theInParam, theProbaCond)  ;
		}
}




void cHmmFit::ComputeGradient(cBaumWelchInParam &theInParam, cOTVector& theGrad, double theDelta)
{
uint myNParam = GetNParam() ;
	theGrad.ReAlloc(myNParam) ;
cOTMatrix* myProbaCond = new cOTMatrix[theInParam.mNSample] ; 
	
	for (register uint n = 0 ; n < theInParam.mNSample ; n++)
		myProbaCond[n].ReAlloc(theInParam.mNClass, theInParam.mY[n].mSize) ;
	
double myLLHInit = ComputeLLH(theInParam, myProbaCond) ;
	theGrad = myLLHInit ;
cOTVector	myValFunct(myNParam),
			myh(myNParam) ;
	ComputeFunction(theInParam, myValFunct, myh, myProbaCond, theDelta) ;
	for (register uint n = 0 ; n < myNParam ; n++)
		theGrad[n] = (myValFunct[n] - myLLHInit)/myh[n] ;

	for (register uint n = 0 ; n < theInParam.mNSample ; n++)
		myProbaCond[n].Delete() ;

}


void cHmmFit::ComputeHessian(cBaumWelchInParam &theInParam, cOTMatrix& theHess, double theDelta)
{
uint myNParam = GetNParam() ;
	theHess.ReAlloc(myNParam, myNParam) ;
cOTMatrix* myProbaCond = new cOTMatrix[theInParam.mNSample] ; 
	
	for (register uint n = 0 ; n < theInParam.mNSample ; n++)
		myProbaCond[n].ReAlloc(theInParam.mNClass, theInParam.mY[n].mSize) ;
	
double myLLHInit = ComputeLLH(theInParam, myProbaCond) ;
cOTVector	myValFunctGrad(myNParam),
			myh(myNParam) ;
	ComputeFunction(theInParam, myValFunctGrad, myh, myProbaCond, theDelta) ;
cOTMatrix myValFunctHess(myNParam, myNParam) ;
	ComputeFunction(theInParam, myValFunctHess, myh, myProbaCond, theDelta) ;
	for (register uint n = 0 ; n < myNParam ; n++)
		for (register uint p = n ; p < myNParam ; p++)
			theHess[n][p] = theHess[p][n] = (myValFunctHess[n][p] - myValFunctGrad[n] - myValFunctGrad[p] + myLLHInit)/(myh[n]*myh[p]) ;

	for (register uint n = 0 ; n < theInParam.mNSample ; n++)
		myProbaCond[n].Delete() ;
//	delete myProbaCond ;

}