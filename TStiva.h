/* NICOLESCU Daniel-Marian - 314CB */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#ifndef _STIVA_
#define _STIVA_

	void FreeS(void**);
	void* InitS(size_t);    
	int Push(void*, void*);
	int Pop(void*, void*);
	int Top (void*, void*);
	void PrintS(void*, FILE*);
	void SortS(void*);
	int CopyS(void*, void*);
	void CorrectS(void*, FILE*);

#endif
