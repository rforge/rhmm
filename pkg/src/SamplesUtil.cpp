/**************************************************************
 *** RHmm version 1.2.0                                      
 ***                                                         
 *** File: SamplesUtil.cpp 
 ***                                                         
 *** Author: Ollivier TARAMASCO <Ollivier.Taramasco@imag.fr> 
 ***                                                         
 *** Date: 2008/11/29                                        
 ***                                                         
 **************************************************************/

#include "SamplesUtil.h"

void flatSamples(cOTVector* theInVect, uint theNSample, uint theDimObs, uint theNObsAllSamples, cOTVector& theOutVect)
{
// Pour un sample Y[i][j]== Y[i + j*DimObs]
// Pour N samples Y[n][i][j] == Y[n][i + j *DimObs] � remplacer par un seul sample de taille correcte
	for (register uint n = 0 ; n < theNSample ; n++)
		for (register uint j = 0 ; j < theDimObs ; j++)
		{	uint myNObs = theInVect[n].mSize / theDimObs ;
			for (register uint s = 0 ; s < myNObs ; s++)
			{	uint myOldInd = s + j*myNObs ;
				uint myNewInd = n*theNObsAllSamples + myOldInd ;
				theOutVect[myNewInd] = theInVect[n][myOldInd] ;
			}
		}
}

void listSamples(cOTVector& theInVect, uint theNSample, uint theDimObs, uint* theNObsSample, cOTVector* theOutVect)
{
uint myBegInd = 0 ;
	for (register uint n = 0 ; n < theNSample ; n++)
	{	for (register uint j = 0 ; j < theDimObs ; j++)
		{	for (register uint s = 0 ; s < theNObsSample[n] ; s++)
			{	uint myNewInd = s + j * theDimObs  ;
				uint myOldInd = myBegInd + myNewInd ;
				theOutVect[n][myNewInd] = theInVect[myOldInd] ;
			}
		}
		myBegInd += theNObsSample[n] ;
	}
}