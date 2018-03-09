/* NICOLESCU Daniel-Marian - 314CB */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#ifndef _COADA_
#define _COADA_

	void* InitQ(size_t); 
	int IntrQ(void*, void*); 
	int ExtrQ(void*, void*);
	void FreeC(void**);
	void PrintQ(void*, FILE*);
	int CopyQ(void*, void*);
	void CorrectQ(void*, FILE*);
	void SortQ(void*); 

#endif
