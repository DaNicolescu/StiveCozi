/* NICOLESCU Daniel-Marian - 314CB */
#include "TStiva.h"

#ifndef _STIVA_LISTA_
#define _STIVA_LISTA_

	typedef struct cel_s {
		struct cel_s *urm;
		void *info;
	} TCel_s, *ACel_s;

	typedef struct {
		size_t dime;
		size_t nr_e;
		ACel_s vf;
	} TStiva, *AStiva;

	// dimensiunea informatiei
	#define DIME_S(a) (((AStiva)(a))->dime)
	// varful stivei
	#define VF(a) 	(((AStiva)(a))->vf)
	// numarul de elemente din stiva
	#define NR_E_S(a) (((AStiva)(a))->nr_e)
	// verifica daca stiva e goala
	#define VIDA_S(a)  	(VF(a) == NULL)

#endif
