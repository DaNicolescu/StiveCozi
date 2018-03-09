/* NICOLESCU Daniel-Marian - 314CB */
#include "TStiva-Lista.h"
#include "TCoada-Lista.h"
#include "TInfo.h"
#include "Functii_Comune.h"

// initializare coada
void* InitQ(size_t d)
{
	ACoada c = (ACoada)malloc(sizeof(TCoada));

	if(!c) return NULL;

	DIME_C(c) = d;
	NR_E_C(c) = 0;
	IC(c) = NULL;
	SC(c) = NULL;

	return (void*)c;
}

// introduce un element in coada cu informatia de la adresa ae
int IntrQ(void *c, void* ae)
{
	// aloca spatiu pentru o celula
	ACel_q aux = (ACel_q)malloc(sizeof(TCel_q));

	if(!aux) return 0;

	aux->urm = NULL;
	// aloca spatiu pentru informatie
	aux->info = AlocInfo(DIME_C(c));

	// copiaza informatia de la ae la adresa informatiei celulei
	memcpy(aux->info, ae, DIME_C(c));

	// daca nu mai e niciun alt element in coada, 
	// inceputul si sfarsitul vor pointa catre acelasi element
	// nou introdus
	if(!IC(c))
	{
		IC(c) = aux;
		SC(c) = aux;
	}
	// altfel se schimba sfarsitul cozii
	else
	{
		SC(c)->urm = aux;
		SC(c) = SC(c)->urm;
	}
	// se incrementeaza numarul de elemente din coada
	++NR_E_C(c);

	return 1;
}

// extrage un element din coada c, iar informatia este copiata
// la adresa ae
int ExtrQ(void *c, void *ae)
{
	ACel_q aux;
	if(VIDA_C(c))
		return 0;
	aux = IC(c);
	// copiaza informatia
	memcpy(ae, aux->info, DIME_C(c));
	// in cazul in care coada avea un singur element, 
	// sfarsitul devine NULL
	if(IC(c) == SC(c))
		SC(c) = NULL;
	IC(c) = IC(c)->urm;
	// eliberare element
	FreeInfo((void**)&aux->info);
	FreeCel((void**)&aux);
	//decrementeaza numarul de elemente din coada
	--NR_E_C(c);
	return 1;
}

// eliberare coada
void FreeC(void **c)
{
	void *info = AlocInfo(DIME_C(*c));

	while(!VIDA_C(*c))
		ExtrQ(*c, info);

	free(*c);
	*c = NULL;

	FreeInfo((void**)&info);
}

// afisare coada
void PrintQ(void *c, FILE *output)
{
	void *info = AlocInfo(DIME_C(c));

	if(!info) return;

	ACoada aux = InitQ(DIME_C(c));

	if(!aux)
	{
		FreeInfo((void**)&info);
		return;
	}

	// introduce elementele din coada c in aux
	fprintf(output, "\"");
	while(!VIDA_C(c))
	{
		ExtrQ(c, info);
		PrintInfo(info, output);
		IntrQ(aux, info);
	}
	fprintf(output, "\"\n");
	
	// inceputul, sfarsitul si numarul de elemente ale lui c
	// vor fi cele ale lui aux
	IC(c) = IC(aux);
	SC(c) = SC(aux);
	NR_E_C(c) = NR_E_C(aux);

	// eliberare informatie
	FreeInfo((void**)&info);
	// eliberare doar structura Acoada
	FreeCel((void**)&aux);
}

// creeaza o copie a lui c
int CopyQ(void *c, void* copy)
{
	void *info = AlocInfo(DIME_C(c));

	if(!info) return 0;

	size_t i = NR_E_C(c);
	while(i > 0)
	{
		ExtrQ(c, info);
		IntrQ(copy, info);
		IntrQ(c, info);
		--i;
	}

	FreeInfo((void**)&info);

	return 1;
}

void CorrectQ(void *c, FILE *output)
{	
	ACoada copy = InitQ(DIME_C(c));

	if(!copy) return;

	// creeaza o copie a lui c
	CopyQ(c, copy);

	// copia este folosita in functia de determinare a celui mai
	// lung subsir de paranteze inchise corect
	Correct(copy, output, ExtrQ);

	// eliberare coada auxiliara
	FreeC((void**)&copy);
}

void SortQ(void *c)
{
	if(VIDA_C(c)) return;

	AStiva aux1 = InitS(DIME_C(c));

	if(!aux1) return;

	AStiva aux2 = InitS(DIME_C(c));

	if(!aux2)
	{
		FreeS((void**)&aux1);
		return;
	}

	void *aux_info = AlocInfo(DIME_C(c));

	if(!aux_info)
	{
		FreeS((void**)&aux1);
		FreeS((void**)&aux2);
		return;
	}

	void *min = AlocInfo(DIME_C(c));

	if(!min)
	{
		FreeS((void**)&aux1);
		FreeS((void**)&aux2);
		FreeInfo((void**)&aux_info);
		return;
	}

	// initial muta toate elementele din coada c in stiva aux1,
	// cu exceptia celui mai mic element care este reintrodus in coada
	ExtrQ(c, min);

	while(!VIDA_C(c))
	{
		ExtrQ(c, aux_info);
		// BiggerID verifica daca id-ul primului parametru e mai mare decat
		// id-ul celui de-al doilea parametru 
		if(BiggerID(min, aux_info))
		{
			// daca aux_info are un id mai mic, 
			Push(aux1, min);
			memcpy(min, aux_info, DIME_C(c));
		}
		else
			Push(aux1, aux_info);
	}
	IntrQ(c, min);

	// apoi foloseste stiva aux1 in care au ramas n-1 elemente de sortat
	// si o alta stiva aux2
	// extrage toate elementele din aux1 si le introduce in aux2, cu exceptia
	// celui mai maic element pe care il introduce in coada
	// similar si din aux2 in aux1
	// mutarle din aux1 in aux2 se repeta pana cand nu mai exista elemente
	// de mutat
	while(!VIDA_S(aux1))
	{
		Pop(aux1, min);
		while(!VIDA_S(aux1))
		{
			Pop(aux1, aux_info);
			if(BiggerID(min, aux_info))
			{
				Push(aux2, min);
				memcpy(min, aux_info, DIME_S(aux1));
			}
			else
				Push(aux2, aux_info);
		}
		IntrQ(c, min);

		if(!VIDA_S(aux2))
		{
			Pop(aux2, min);
			while(!VIDA_S(aux2))
			{
				Pop(aux2, aux_info);
				if(BiggerID(min, aux_info))
				{
					Push(aux1, min);
					memcpy(min, aux_info, DIME_S(aux2));
				}
				else
					Push(aux1, aux_info);
			}
			IntrQ(c, min);
		}
	}

	FreeS((void**)&aux1);
	FreeS((void**)&aux2);
	FreeInfo((void**)&aux_info);
	FreeInfo((void**)&min);
}