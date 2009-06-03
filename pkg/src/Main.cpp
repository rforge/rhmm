/**************************************************************
 *** RHmm version 1.3.0                                      
 ***                                                         
 *** File: Main.cpp 
 ***                                                         
 *** Author: Ollivier TARAMASCO <Ollivier.Taramasco@imag.fr> 
 ***                                                         
 *** Date: 2009/06/03                                      
 ***                                                         
 **************************************************************/

#ifndef _RDLL_
#include <iostream>
#include <fstream>
#include "Hmm.h"
#include "cInParam.h"
#include "cBaumWelchInParam.h"
#include "cBaumWelch.h"
#include "AllDistributions.h"
#include "cHmm.h"
#include "cHmmFit.h"
#include "cViterbi.h"
#include "RHmm.h"
using namespace std;

#define FIC_NAME  "Geyser.txt" /*"data_mixture.txt" "DISCRETEb.txt" "DISCRETE.txt"  "CAC40.txt"   "Geyser.txt" "SimulMultiMixt.txt"*/
#define DIM_OBS 2
#define NB_SAMPLE 1
int main(void)
{
ifstream myFile ;
cOTVector* myRt = new cOTVector[NB_SAMPLE] ;
register uint n = 0 ;
double myAux ;
	myFile.open(FIC_NAME) ;
	while (myFile)
	{	myFile >> myAux ;		
		n++ ;
	}
	n = (n-1)/(DIM_OBS*NB_SAMPLE) ;
	myFile.close() ;
	for (register uint j = 0 ; j < NB_SAMPLE ; j++)
		myRt[j].ReAlloc(DIM_OBS*n) ;
	std::fstream myFile1(FIC_NAME) ;
	for (register uint i = 0 ; i < NB_SAMPLE ; i++)
		for (register uint j = 0 ; j < n  ; j++)
			for (register uint k = 0 ; k < DIM_OBS ; k++)
				myFile1 >> myRt[i][j + k*n]  ;
	
//	myRt[1] = myRt[0] ;
	myFile1.close() ;

/*cOTVector* myRt1 = new cOTVector[1] ;
	myRt1[0].ReAlloc(n) ;
	for (register uint i = 0 ; i < n ; i++)
//		myRt1[0][i] = myRt[0][i(*+n*)] - 1;
*/

//cHmm MyHMM(eNormalDistr, 2) ;
uint myDimObs = DIM_OBS ;

//cBaumWelchInParam myParam=cBaumWelchInParam(1, myDimObs, myRt1, eNormalDistr, 2) ;
//cBaumWelchInParam myParam=cBaumWelchInParam(1, myDimObs, myRt1, eDiscreteDistr, 3, 0, 10) ;
//cBaumWelchInParam myParam=cBaumWelchInParam(NB_SAMPLE, myDimObs, myRt, eMixtUniNormalDistr, 2, 3) ;
cBaumWelchInParam myParam=cBaumWelchInParam(NB_SAMPLE, myDimObs, myRt, eMultiNormalDistr, 3) ;

/*cHmm myHMM(eDiscreteDistr, 2) ;
	myHMM.mInitProba[0] = myHMM.mInitProba[1] = 0.5L ;
	myHMM.mTransMat[0][0]=0.95L ;
	myHMM.mTransMat[0][1]=0.05L ;
	myHMM.mTransMat[1][0]=0.10L ;
	myHMM.mTransMat[1][1]=0.90L ;

cDiscrete myDistrParam(2, 6) ;
	for (register int j = 0 ; j < 6 ; j++)
	{	myDistrParam.mProba[0][j] = 1.0L/6.0L ;
		myDistrParam.mProba[1][j] = 1.0L/10.0L ;
	}
	myDistrParam.mProba[1][5] = 1.0L/2.0L ;
	myHMM.mDistrParam = &myDistrParam ;
	
*/
	myParam.Print() ;
	myParam.mVerbose = 2 ;
	myParam.mNInitIter = 5 ;
	myParam.mNMaxIterInit = 5 ;
	myParam.mNMaxIter = 500 ;


cHmmFit myHMMFit(myParam) ;
	myHMMFit.BaumWelchAlgoInit(myParam) ;
	myHMMFit.BaumWelchAlgo(myParam) ;
	myHMMFit.Print() ;
/*
cOTMatrix*	myProbaCond = new cOTMatrix[myParam.mNSample] ; 
	
 	for (register uint n = 0 ; n < myParam.mNSample ; n++)
	{	
	uint mySize = myParam.mY[n].mSize/myParam.mDimObs ;
		myProbaCond[n].ReAlloc(myParam.mNClass, mySize) ;
	}
	myHMMFit.mDistrParam->ComputeCondProba(myParam.mY, myParam.mNSample, myProbaCond) ;
	myHMMFit.ForwardBackward(myProbaCond, myHMMFit) ;
	cout << *(myHMMFit.mRho) ;


cViterbi myViterbi(myParam) ;
	myViterbi.ViterbiPath(myParam, myHMMFit) ;
//	myViterbi.ViterbiPath(myParam, myHMM) ;
	for (register uint n = 0 ; n < myParam.mNSample ; n++)
		for (register uint i = 0 ; i < myParam.mY[n].mSize ; i++)
			std::cout << myViterbi.mSeq[n][i] << std::endl ;
			source("C:/Users/taram/Documents/R/RHMM DEBUG/debug.R")
*/
/*
cOTVector myGrad ;
	myHMMFit.ComputeGradient(myParam, myGrad, 1e-2) ;
	std::cout << "Gradient : \n" ;
	std::cout << myGrad ;

cOTMatrix myHess	;
	myHMMFit.ComputeHessian(myParam, myHess,1e-5) ;
	std::cout << "Hessian : \n" ;
	std::cout << myHess ;

cOTMatrix	myI,
			myJ,
			myInvJ,
			myCov	;

	myI = myGrad*transpose(myGrad) ;
	myJ = myHess ;
	myJ /= -(double)n ;
	myInvJ = inv(myJ) ;
	myCov = myInvJ ;
	myCov /= (double)n ;
	myCov = myInvJ * myI ;
	myCov *= myInvJ ;
	std::cout << "Cov : \n" ;
	std::cout << myCov ;

*/
	return 0 ;
} 



#endif _RDLL_
