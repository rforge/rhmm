#include "cRandomGenerator.hpp"
#ifdef _GSL_
cRandomGenerator::cRandomGenerator()
{
	gsl_rng_env_setup() ;
	mT = gsl_rng_default ;
	mr = gsl_rng_alloc(mT) ;
} 

cRandomGenerator::~cRandomGenerator()
{
	gsl_rng_free(mr);
}
#endif // _GSL_NO_R_

