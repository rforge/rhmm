#ifndef _CVITERBI_HPP_
#define _CVITERBI_HPP_
#include "cInParam.hpp"
#include "cHmm.hpp"
#include "cDistribution.hpp"

class cViterbi
{	public :
		uint		**mSeq		;
		cOTVector	mLogProb	;
	public :
		cViterbi(cInParam &theInParam) ;
		~cViterbi() ;
		void ViterbiPath(cInParam& theInParam, cHmm& theHMM) ;
} ;

#endif // _CVITERBI_HPP_
