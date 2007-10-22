#ifndef _SVDH_
#define _SVDH_
#include <math.h>
/*#include <iostream>
using namespace std;
*/
#ifndef MIN_DBLE
	#define MIN_DBLE 1e-16L
#endif //MIN_DBLE

#ifndef SQR
	#define SQR(p)	(p*p)
#endif //SQR
#ifndef FMAX
	#define FMAX(p, q)	(p > q ? p : q)
#endif //FMAX
#ifndef IMAIN
	#define IMIN(p, q)	(p < q ? p : q)
#endif //IMAIN
#ifndef SIGN
	#define SIGN(a,b) ((b) >= 0.0 ? fabs(a) : -fabs(a))
#endif // SIGN
#ifndef uint
	typedef unsigned int uint ;
#endif //uint
int svd(double **TheMat, uint Then, uint Thep, double** Theu, double *Thew, double **Thev) ;
#endif //_SVDH_

