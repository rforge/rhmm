/**************************************************************
 *** RHmm version 1.4.9
 ***                                                         
 *** File: OTMathUtil.h 
 ***                                                         
 *** Author: Ollivier TARAMASCO <Ollivier.Taramasco@imag.fr> 
 *** Author: Sebastian BAUER <sebastian.bauer@charite.de>
 *** Date: 2011/04/21                                     
 ***                                                         
 **************************************************************/

#ifndef _OTMATHUTIL_H_
#define _OTMATHUTIL_H_
#pragma once

#include "cOTError.h"
#include "cDVector.h"
#include "cDMatrix.h"
typedef cDVector cOTVector ;
typedef cDMatrix cOTMatrix ;

#define mSize GetSize()
#define mNRow GetNRows()
#define mNCol GetNCols()

#endif // _OTMATHUTIL_H_
