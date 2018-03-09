/* NICOLESCU Daniel-Marian - 314CB */
#include "TCoada.h"

#ifndef _COADA_LISTA_
#define _COADA_LISTA_

	typedef struct cel_q {
		struct cel_q *urm;
		void *info;
	} TCel_q, *ACel_q;

	typedef struct {
		size_t dime;
		size_t nr_e;
		ACel_q ic, sc;
	} TCoada, *ACoada;

	// dimensiunea informatiei
	#define DIME_C(a)  (((ACoada)(a))->dime)
	// inceputul cozii
	#define IC(a)  (((ACoada)(a))->ic)
	// sfarsitul cozii
	#define SC(a)  (((ACoada)(a))->sc)
	// numarul de elemente din coada
	#define NR_E_C(a)  (((ACoada)(a))->nr_e)
	// verifica daca e vida coada									
	#define VIDA_C(a)  (IC(a) == NULL)

#endif
