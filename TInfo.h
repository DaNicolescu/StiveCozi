/* NICOLESCU Daniel-Marian - 314CB */
#ifndef _TInfo_
#define _TInfo_
	
	typedef struct {
		size_t id_paranteza;
		char tip;
	} TInfo;

	typedef int (*GetElemF)(void*, void*);

	void *AlocInfo(size_t);
	void PrintInfo(void*, FILE*);
	int BiggerID(void*, void*);
	void InfoStar(void*, size_t);
	void ChangeID(void*, size_t);
	int OpenParan(void*);
	int SameType(void*, void*);
	size_t CurrentLen(void*, void*);
	void Correct(void*, FILE*, GetElemF);

#endif