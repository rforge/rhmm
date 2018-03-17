/**************************************************************
 *** RHmm package
 ***                                                         
 *** File: Main.cpp 
 ***                                                         
 *** Author: Ollivier TARAMASCO <Ollivier.Taramasco@imag.fr> 
 *** Author: Sebastian BAUER <mail@sebastianbauer.info>
 ***                                                         
 **************************************************************/

#ifndef _RDLL_
#include <iostream>
#include <fstream>
#include "StdAfxRHmm.h"

using namespace std;

#define FIC_NAME     "chrm.txt" /* "Cac40.txt" "n2d_2s.txt" "n3d2s.txt"  "data_mixture.txt" "Meteo.txt" "n3s.txt" "Geyser.txt"  "m_2d_2s.txt" "Weather2.txt" "Weather.txt" "Xirisx.txt" "n1d_3s.txt"    "DISCRETEb.txt" "DISCRETE.txt"  "SimulMultiMixt.txt" "Norm.txt"  */
#define DIM_OBS 1
#define NB_SAMPLE 1 /* 5*/
#define NB_STATES 2
#define NB_MIXT 3
#define NB_PROBA 2
int main(void)
{
/*
cMixtMultivariateNormal myMixt(2,2,2) ;
double	myMeanD11[2] = {10, 0},
		myMeanD12[2] = {0, -5},
		myMeanD21[2] = {15, 15},
		myMeanD22[2] = {-7, -7},
		myCovD11[4] = {1, 1.6, 1.6, 4},
		myCovD12[4] = {4, -3, -3, 9},
		myCovD21[4] = {4, 1, 1, 1},
		myCovD22[4] = {1, -2.1, -2.1, 9},
		mypD1[2] = {0.2, 0.8},
		mypD2[2] = {0.7, 0.3};
cDVector myMean11(2, myMeanD11), myMean12(2, myMeanD12), myMean21(2, myMeanD21), myMean22(2, myMeanD22) ;
cDMatrix myCov11(2,2, myCovD11), myCov12(2,2, myCovD12), myCov21(2,2, myCovD21), myCov22(2,2, myCovD22) ;
cDVector myp1(2, mypD1), myp2(2, mypD2) ;


	myMixt.mMean[0][0] = myMean11;
	myMixt.mMean[0][1] = myMean12 ;
	myMixt.mMean[1][0] = myMean21 ;
	myMixt.mMean[1][1] = myMean22 ;
	myMixt.mCov[0][0] = myCov11;
	myMixt.mCov[0][1] = myCov12 ;
	myMixt.mCov[1][0] = myCov21 ;
	myMixt.mCov[1][1] = myCov22 ;
	myMixt.mp[0] = myp1 ;
	myMixt.mp[1] = myp2 ;
	myMixt.Print() ;

cDVector myY = Zeros(2) ;
cDVector** myGrad = new cDVector*[2] ;
cDMatrix** myHess = new cDMatrix*[2] ;
	for (uint j = 0 ; j < 2 ; j++)
	{	myGrad[j] = new cDVector[1] ;
		myGrad[j][0].ReAlloc(25) ;
		myHess[j] = new cDMatrix[1] ;
		myHess[j][0].ReAlloc(25, 25) ;
	}
	myMixt.ComputeDerivative(myY, myGrad, myHess) ;
	for (uint j = 0 ; j < 2 ; j++)
	{
		cout << "Grad[" << j <<"] : " << endl << myGrad[j][0] << endl ;
		cout << "Hess[" << j <<"] : " << endl << myHess[j][0] << endl ;
	}
	return 0 ;
*/

ifstream myFile ;
cDVector* myRt = new cDVector[NB_SAMPLE] ;
uint n = 0 ;
uint myT[NB_SAMPLE] ;
double myAux ;
	myFile.open(FIC_NAME) ;
	if (myFile.fail())
	{
	        cerr << "Opening " << FIC_NAME << " failed" << endl;
	        return 1;
	}
	if ((int)NB_SAMPLE == 1)
	{	while (myFile)
		{	for (int l = 0 ; l < DIM_OBS ; l++)
				myFile >> myAux ;		
			n++ ;
		}
		n = (n-1)/DIM_OBS ;
		myT[0] = n-1 ;
	}
	else
	{
	uint i, j = 1 ;
		while (myFile)
		{	myFile >> i ;
			for (uint l = 0 ; l < DIM_OBS ; l++)
				myFile >> myAux ;
			if (i == j)
				n++ ;
			else
			{	myT[j-1] = n+1 ;
				n = 0 ;
				j++ ;
			}
		}
		myT[j-1] = n ;
		//for (j = 0 ; j < NB_SAMPLE ; j++)
		//	myT[j] = myT[j]/(DIM_OBS) ;
		myT[0]-- ;
	}

	
	myFile.close() ;
double myMin = 1e+100, myMax=-1e+100 ;
	if ((int)NB_SAMPLE == 1)
		myRt[0].ReAlloc(DIM_OBS*n) ;
	else
		for (uint j = 0 ; j < NB_SAMPLE ; j++)
			myRt[j].ReAlloc(myT[j]*DIM_OBS) ;
	std::fstream myFile1(FIC_NAME) ;
	if ((int)NB_SAMPLE == 1)
	{	for (uint j = 0 ; j < n  ; j++)
			for (uint k = 0 ; k < DIM_OBS ; k++)
			{	myFile1 >> myRt[0][j + k*n]  ;
				myMin = MIN(myMin, myRt[0][j + k*n]) ;
				myMax = MAX(myMin, myRt[0][j + k*n]) ;
			}
	}
	else
	{	uint myAux1 ;
		for (uint i = 0 ; i < NB_SAMPLE ; i++)
			for (uint j = 0 ; j < myT[i]  ; j++)
			{	myFile1 >> myAux1 ;
				for (uint k = 0 ; k < DIM_OBS ; k++)
					myFile1 >>  myRt[i][j + k*myT[i]]  ;
			}
	}

	myFile1.close() ;
	cout << "MIN : " << myMin << endl << "MAX : " << myMax << endl ;


//cHmm MyHMM(eNormalDistr, 2) ;
uint myDimObs = DIM_OBS ;

cBaumWelchInParam myParam=cBaumWelchInParam(NB_SAMPLE, myDimObs, myRt, eNormalDistr, NB_STATES) ;
//cBaumWelchInParam myParam=cBaumWelchInParam(NB_SAMPLE,myDimObs, myRt, eDiscreteDistr, NB_STATES, 0, NB_PROBA) ;
//cBaumWelchInParam myParam=cBaumWelchInParam(1, myDimObs, myRt, eDiscreteDistr, 2, 0, 2) ;
//cBaumWelchInParam myParam=cBaumWelchInParam(NB_SAMPLE, myDimObs, myRt, eMixtUniNormalDistr, NB_STATES, NB_MIXT) ;
//cBaumWelchInParam myParam=cBaumWelchInParam(NB_SAMPLE, myDimObs, myRt, eMultiNormalDistr, NB_STATES) ;
//cBaumWelchInParam myParam=cBaumWelchInParam(NB_SAMPLE, myDimObs,  myRt, eMixtMultiNormalDistr, NB_STATES, NB_MIXT) ;

	myParam.mVerbose = 3 ;
	myParam.mNInitIter = 10 ;
	myParam.mNMaxIterInit = 10 ;
	myParam.mNMaxIter = 3000 ;


cHmmFit myHMMFit(myParam) ;


	myHMMFit.BaumWelchAlgoInit(myParam) ;
	myHMMFit.BaumWelchAlgo(myParam) ;

	myHMMFit.Print() ;

cViterbi myViterbi(myParam) ;
	myViterbi.ViterbiPath(myParam, myHMMFit) ;



cDMatrix* myProbaCond = new cDMatrix[NB_SAMPLE] ;

	for (uint q = 0 ; q < NB_SAMPLE ; q++)
		myProbaCond[q].ReAlloc(NB_STATES, myT[q]) ;

	myHMMFit.mDistrParam->ComputeCondProba(myRt, NB_SAMPLE, myProbaCond) ;

cBaumWelch myBaumWelch=cBaumWelch(NB_SAMPLE, myT, NB_STATES) ;

	myBaumWelch.OutForwardBackward(myProbaCond, myHMMFit, NB_SAMPLE) ;

	return(0) ;

uint myNFreeParam = myHMMFit.GetNFreeParam() ;
cDerivative myDerivative(myParam, myNFreeParam) ;
	
 	myDerivative.ComputeDerivative(myHMMFit, myParam) ;

ofstream myFileInfo("OutInfo.txt") ;

//uint myT = myRt[0].GetSize() ;

cDVector myScore(myNFreeParam) ;
cDMatrix myInformation(myNFreeParam, myNFreeParam) ;
	myDerivative.ComputeScoreAndInformation(myScore, myInformation) ;
	cout << "Score : " << endl ;
	cout << myScore << endl ;
	cout << "Information : " << endl ;
	cout << myInformation << endl ;


cDMatrix myCov = Inv(myInformation) ;
	cout << "Covariance :" << endl ;
	cout << myCov << endl ;


cDVector myStdError(myNFreeParam) ;
	for (uint i = 0 ; i < myNFreeParam ; i++)
		myStdError[i] = sqrt(myCov[i][i]) ;
	cout << "Ecart-types : " << endl << myStdError << endl ;

cDMatrix myCov1 = myCov ;
	myDerivative.ComputeCov(myHMMFit, myCov1) ;
	cout << "Covariance 1 :" << endl ;
	cout << myCov1 << endl ;


	return 0 ;

} 

#endif
