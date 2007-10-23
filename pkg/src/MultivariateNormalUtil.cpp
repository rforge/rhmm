#include "MultivariateNormalUtil.hpp"

void SymetricInverseAndDet	(	cOTMatrix&	theMat,
								double&		theDet,
								cOTMatrix&	theInvMat
							)

#ifndef _GSL_
#ifndef _RDLL_
{
unsigned int	myDimObs = theMat.mNCol ;
cOTVector		myW(myDimObs)	;
cOTMatrix		myU(myDimObs, myDimObs),
				myV(myDimObs, myDimObs)	;
register uint	i,
				j,
				k		;

	
	svd(theMat.mMat, myDimObs, myDimObs, myU.mMat, myW.mVect, myV.mMat) ;

	theDet = myW[0] ;
	for (i = 1 ; i < myDimObs ; i++)
		theDet *= myW[i] ;
	for (i = 0 ; i < myDimObs ; i++)
		for (j = 0 ; j < myDimObs ; j++)
		{	double myAux = 0 ;
			for (k = 0 ; k < myDimObs ; k++)
				myAux += myV[i][k] * myV[j][k] / myW[k] ;
			theInvMat[i][j] = myAux ;
		}
}
#else
{
	LapackInvAndDet(theMat, theInvMat, theDet) ;
}
#endif // _RDLL_

#else //ifndef _GSL_
{
gsl_matrix					*myLambda,
							*myVectPropre		;
gsl_vector					*myValPropre		;
gsl_eigen_symmv_workspace	*myWorkspace		;
register uint				i,
							j,
							k					;
uint myDimObs = (uint)theMat.mNCol ;
	myLambda = gsl_matrix_alloc(myDimObs, myDimObs) ;
	for (i = 0 ; i < myDimObs ; i++)
		for (j = 0 ; j < myDimObs ; j++)
			gsl_matrix_set(myLambda, i, j, theMat[i][j]) ;

	myValPropre = gsl_vector_alloc(myDimObs) ;
	myVectPropre = gsl_matrix_alloc(myDimObs, myDimObs) ;
	myWorkspace = gsl_eigen_symmv_alloc(myDimObs);
  
	gsl_eigen_symmv(myLambda, myValPropre, myVectPropre, myWorkspace) ;
	
	gsl_eigen_symmv_free(myWorkspace) ;
	gsl_eigen_symmv_sort (myValPropre, myVectPropre, GSL_EIGEN_SORT_VAL_DESC) ; 

	theDet = gsl_vector_get(myValPropre, 0) ;
	for (i = 1 ; i < myDimObs ; i++)
		theDet *= gsl_vector_get(myValPropre, i) ;
	for (i = 0 ; i < myDimObs ; i++)
		for (j = 0 ; j < myDimObs ; j++)
		{	double myAux = 0.0 ; ;
			for (k = 0 ; k < myDimObs ; k++)
				myAux += gsl_matrix_get(myVectPropre, i, k) * gsl_matrix_get(myVectPropre, j, k) / gsl_vector_get(myValPropre, k) ;
			theInvMat[i][j] = myAux ;
		}
	gsl_vector_free(myValPropre) ;
	gsl_matrix_free(myVectPropre) ;
	gsl_matrix_free(myLambda) ;
}
#endif //_GSL_


/*
void dens_normale_multivariee	(	cOTVector&	thex,
									uint		theDimObs,	// dim de la loi multivariée
									cOTVector&	theMu,
									cOTMatrix&	theCov,
									double*		theDens
								) 

{
register uint	i,
				j,
				t				;
double			myDet,
				myAux,
				myRapport		;
cOTMatrix		myInvLambda(theDimObs, theDimObs)	;

	SymetricInverseAndDet(theCov, myDet, myInvLambda) ;
	
	myRapport = pow(SQRT_TWO_PI*sqrt(myDet), (int)theDimObs) ;

uint myT = thex.mSize / theDimObs ;
	for ( t = 0 ; t < myT ; t++)
	{	myAux = 0.0 ;
		for (i = 0 ; i < theDimObs ; i++)
			for (j = 0 ; j < theDimObs ; j++)
				myAux += (thex[t+i*myT]-theMu[i]) * myInvLambda[i][j] * (thex[t+j*myT]-theMu[j]) ;
		theDens[t] = exp(-0.5*myAux)/myRapport ;
	}
}
*/

void MultivariateNormalDensity	(	cOTVector&	thex,
									cOTVector&	theMu,
									cOTMatrix&	theInvCov,
									double		theDet,
									double*		theDens
								) 

{
register uint	i,
				j,
				t				;
double			myAux,
				myRapport		;

uint myDimObs = theMu.mSize ;	
	myRapport = pow(SQRT_TWO_PI*sqrt(theDet), (int)myDimObs) ;

uint myT = thex.mSize / myDimObs ;

	for ( t = 0 ; t < myT ; t++)
	{	myAux = 0.0 ;
		for (i = 0 ; i < myDimObs ; i++)
			for (j = 0 ; j < myDimObs ; j++)
				myAux += (thex[t+i*myT]-theMu[i]) * theInvCov[i][j] * (thex[t+j*myT]-theMu[j]) ;
		theDens[t] = exp(-0.5*myAux)/myRapport ;
	}
}
