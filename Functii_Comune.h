/* NICOLESCU Daniel-Marian - 314CB */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "TInfo.h"

#ifndef _COMUNE_
#define _COMUNE_

	void FreeInfo(void**);
	void FreeCel(void**);
	void* AlocInfo(size_t);
	void PrintInfo(void*, FILE*);
	void InfoStar(void*, size_t);
	void ChangeID(void*, size_t);
	size_t CurrentLen(void*, void*);
	void Correct(void*, FILE*, GetElemF);

#endif