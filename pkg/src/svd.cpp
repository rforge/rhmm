#include "svd.hpp"

static double pytha	(	double a, 
						double b
					)
//	Computes (a2 + b2)1/2 without destructive underflow or overflow.
{
double	absa,
		absb ;
	
	absa = fabs(a) ;
	absb = fabs(b) ;
	if (absa > absb) 
		return absa*sqrt(1.0+SQR(absb/absa)) ;
	else 
		return (absb == 0.0 ? 0.0 : absb*sqrt(1.0+SQR(absa/absb))) ;
}



int svd(double **theMat, uint theN, uint theP, double** theU, double *theW, double **theV)
{
const double ZERO = 0.0 ;
const double UN = 1.0 ;
int		flag,
		i,
		its,
		j,
		jj,
		k,
		l,
		nm		;
double	anorm,
		c,
		f,
		g,
		h,
		s,
		scale,
		x,
		y,
		z,
		*rv1	;

	rv1 = new double[theP] ;
	for (i = 0 ; i < (int)theN ; i++)
		for (j = 0 ; j < (int)theP ; j++)
			theU[i][j] = theMat[i][j] ;

	g = scale = anorm = ZERO ; 
	for(i = 0 ; i < (int)theP ; i++) 
	{	l = i+1;
		rv1[i] = scale*g;
		g = s = scale = ZERO ;
		if (i < (int)theN) 
		{	for(k = i ; k < (int)theN ; k++) 
				scale +=  fabs(theU[k][i]) ;
			if (scale) 
			{	for (k = i ; k < (int)theN ; k++) 
				{	theU[k][i] /=  scale ;
					s +=  theU[k][i] * theU[k][i] ;
				}
				f = theU[i][i] ;
				g = -SIGN(sqrt(s), f) ;
				h = f*g-s ;
				theU[i][i] = f-g ;
				for (j = l ; j < (int)theP ; j++) 
				{	for (s = ZERO, k = i ; k < (int)theN ; k++) 
						s +=  theU[k][i]*theU[k][j] ;
					f = s/h ;
					for (k = i ; k < (int)theN ; k++) 
						theU[k][j] +=  f*theU[k][i] ;
				}
				for (k = i ; k < (int)theN ; k++) 
					theU[k][i] *=  scale ;
			}
		}
		theW[i] = scale *g ;
		g = s = scale = ZERO ;
		if (i <  (int)theN  && i !=  (int)theP - 1) 
		{	for (k = l ; k < (int)theP ; k++) 
				scale +=  fabs(theU[i][k]) ;
			if (scale) 
			{	for (k = l ; k < (int)theP ; k++) 
				{	theU[i][k] /=  scale ;
					s +=  theU[i][k]*theU[i][k] ;
				}
				f = theU[i][l] ;
				g = -SIGN(sqrt(s),f) ;
				h = f*g-s ;
				theU[i][l] = f-g ;
				for (k = l ; k < (int)theP ; k++) 
					rv1[k] = theU[i][k]/h ;
				for (j = l ; j < (int)theN ; j++) 
				{	for (s = ZERO, k = l ; k < (int)theP ; k++) 
						s +=  theU[j][k]*theU[i][k] ;
					for (k = l ; k < (int)theP ; k++) 
						theU[j][k] +=  s*rv1[k] ;
				}
				for (k = l ; k < (int)theP ; k++) 
					theU[i][k] *=  scale ;
			}
		}
		anorm = FMAX(anorm,(fabs(theW[i])+fabs(rv1[i]))) ;
	}
	for (i = (int)theP - 1 ; i >= 0 ; i--) 
	{	if (i < (int)theP - 1) 
		{	if (g) 
			{	for (j = l ; j < (int)theP ; j++)
					theV[j][i] = (theU[i][j]/theU[i][l])/g ;
				
				for (j = l ; j < (int)theP ; j++) 
				{	for (s = ZERO, k = l ; k < (int)theP ; k++) 
						s +=  theU[i][k] * theV[k][j] ;
					for (k = l ; k < (int)theP ; k++) 
						theV[k][j] += s * theV[k][i] ;
				}
			}
			for (j = l ; j < (int)theP ; j++) 
				theV[i][j] = theV[j][i] = ZERO ;
		}
		theV[i][i] = UN ;
		g = rv1[i] ;
		l = i ;
	}
	for (i = IMIN((int)theN,(int)theP)-1 ; i >= 0 ; i--) 
	{	l = i+1 ;
		g = theW[i] ;
		for (j = l ;j < (int)theP ; j++) 
			theU[i][j] = ZERO ;
		if (g) 
		{	g = UN/g ;
			for (j = l ; j< (int)theP ; j++) 
			{	for (s = ZERO, k = l ; k < (int)theN ; k++) 
					s += theU[k][i]*theU[k][j] ;
				f = (s/theU[i][i])*g ;
				for (k = i ; k < (int)theN ; k++) 
					theU[k][j] +=  f*theU[k][i] ;
			}
			for (j = i ; j < (int)theN ; j++) 
				theU[j][i] *=  g ;
		} 
		else 
			for (j = i ; j < (int)theN ; j++) 
				theU[j][i] = ZERO ;
		++theU[i][i] ;
	}
	for (k = (int)theP-1 ; k >= 0 ; k--) 
	{	for (its = 1 ; its <= 500 ; its++) 
		{	flag = 1 ;
			for (l = k ; l >= 0 ; l--) 
			{	nm = l-1 ; // Note that rv1[1] is always zero.
				if ((double)(fabs(rv1[l])+anorm) == anorm) 
				{	flag = 0 ;
					break ;
				}
				if ((double)(fabs(theW[nm])+anorm) == anorm) 
					break ;
			}
			if (flag) 
			{	c = ZERO ; //Cancellation of rv1[l], if l > 1.
				s = UN ;
				for (i = l ; i <= k ; i++) 
				{	f = s*rv1[i] ;
					rv1[i] = c*rv1[i] ;
					if ((double)(fabs(f)+anorm) == anorm) 
						break ;
					g = theW[i] ;
					h = pytha(f,g) ;
					theW[i] = h ;
					h = UN/h ;
					c = g*h ;
					s = -f*h ;
					for (j = 0 ; j < (int)theN ;j++) 
					{	y = theU[j][nm] ;
						z = theU[j][i] ;
						theU[j][nm] = y*c+z*s ;
						theU[j][i] = z*c-y*s ;
					}
				}
			}
			z = theW[k] ;
			if (l == k) 
			{ // Convergence.
				if (z < ZERO) 
				{	// Singular value is made nonnegative.
					theW[k]  =  -z ;
					for (j = 0 ; j< (int)theP ; j++) 
						theV[j][k] = -theV[j][k] ;
				}
				break ;
			}
			if (its == 500) 
				return(1) ;
			x = theW[l] ; //Shift from bottom 2-by-2 minor.
			nm = k-1 ;
			y = theW[nm] ;
			g = rv1[nm] ;
			h = rv1[k] ;
			f = ((y-z)*(y+z)+(g-h)*(g+h))/(2.0*h*y) ;
			g = pytha(f,UN) ;
			f = ((x-z)*(x+z)+h*((y/(f+SIGN(g,f)))-h))/x ;
			c = s = UN ; // Next QR transformation:
			for (j = l ; j<= nm ; j++) 
			{	i = j+1 ;
				g = rv1[i] ;
				y = theW[i] ;
				h = s*g ;
				g = c*g ;
				z = pytha(f,h) ;
				rv1[j] = z ;
				c = f/z ;
				s = h/z ;
				f = x*c+g*s ;
				g = g*c-x*s ;
				h = y*s ;
				y *= c ;
				for (jj = 0 ; jj < (int)theP ; jj++) 
				{	x = theV[jj][j] ;
					z = theV[jj][i] ;
					theV[jj][j] = x*c+z*s ;
					theV[jj][i] = z*c-x*s ;
				}
				z = pytha(f,h) ;
				theW[j] = z ; // Rotation can be arbitrary if z  =  0.
				if (z) 
				{	z = UN/z ;
					c = f*z ;
					s = h*z ;
				}
				f = c*g+s*y ;
				x = c*y-s*g ;
				for (jj = 0 ; jj< (int)theN ; jj++) 
				{	y = theU[jj][j] ;
					z = theU[jj][i] ;
					theU[jj][j] = y*c+z*s ;
					theU[jj][i] = z*c-y*s ;
				}
			}
			rv1[l] = ZERO ;
			rv1[k] = f ;
			theW[k] = x ;
		}
	}
	delete rv1 ;
	return(0) ;
}
