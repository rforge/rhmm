/**************************************************************
 *** RHmm version 1.4.9
 ***                                                         
 *** File: logprob.cpp 
 ***                                                         
 *** Author: Ollivier TARAMASCO <Ollivier.Taramasco@imag.fr> 
 *** Author: Sebastian BAUER <sebastian.bauer@charite.de>
 *** Date: 2011/04/21                                     
 ***                                                         
 **************************************************************/

#include "logprob.h"

double eexp( double theX)
{
        if (theX <= LOGZERO)
                return(0.0L) ;
        else
                return(exp(theX)) ;
}

double eln( double theX)
{
        if (theX > 0.0L)
                return(log(theX)) ;
        else
                return(LOGZERO) ;
}

double elnsum1( double theX,  double theY)
{       
double  myeLnX = eln(theX), myeLnY = eln(theY) ;
        
        if ( (myeLnX <= LOGZERO) || (myeLnY <= LOGZERO) )
        {       if (myeLnX <= LOGZERO)
                        return(myeLnY) ;
                else
                        return(myeLnX) ;
        }
        else
        {       if (myeLnX > myeLnY) 
                        return(myeLnX + eln(1.0+exp(myeLnY-myeLnX))) ;
                else
                        return(myeLnY + eln(1.0+exp(myeLnX-myeLnY))) ;
        }
}

double elnsum( double theeLnX,  double theeLnY)
{       
// elnsum(eln(x), eln(y)) = eln(x+y) pour x, y > LOGZERO
// elnsum(LOGZERO, eln(y)) = eln(y)
// elnsum(eln(x), LOGZERO) = eln(x)
double  myeLnX = MAX(theeLnX, theeLnY),
                myeLnY = MIN(theeLnX, theeLnY) ;
        
        if (myeLnY <= LOGZERO)
                return(myeLnX) ;
        else
                return(myeLnX + eln(1.0+exp(myeLnY-myeLnX))) ;
}


double elnproduct1( double theX,  double theY)
{
double  myeLnX = eln(theX),
                myeLnY = eln(theY) ;

        if ( (myeLnX <= LOGZERO) || (myeLnY <= LOGZERO) )
                return(LOGZERO) ;
        else
                return(myeLnX + myeLnY) ;
}

double elnproduct( double theeLnX,  double theeLnY)
// elnproduct(eln(x), eln(y)) = eln(x) + eln(y) pour x, y > 0
// elnproduct(LOGZERO, eln(y)) = elnproduct(eln(x), LOGZERO) = LOGZERO
{
        if ( (theeLnX <= LOGZERO) || (theeLnY <= LOGZERO) )
                return(LOGZERO) ;
        else
                return(theeLnX + theeLnY) ;
}
