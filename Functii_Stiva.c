/* NICOLESCU Daniel-Marian - 314CB */
#include "TStiva-Lista.h"
#include "TCoada-Lista.h"
#include "TInfo.h"
#include "Functii_Comune.h"

// initializare stiva
void* InitS(size_t d)
{
	AStiva s = (AStiva)malloc(sizeof(TStiva));

	if(!s) return NULL;

	DIME_S(s) = d;
	NR_E_S(s) = 0;
	VF(s) = NULL;

	return (void*)s;
}

// introduce un element in stiva cu informatia de la adresa ae
int Push(void *s, void *ae)
{
	// aloca spatiu pentru o celula
	ACel_s aux = (ACel_s)malloc(sizeof(TCel_s));

	if(!aux) return 0;

	// aloca spatiu pentru informatie
	aux->info = AlocInfo(DIME_S(s));

	if(!aux->info)
	{ 
		FreeCel((void**)&aux);
		return 0;
	}

	// copiaza informatia de la ae la adresa informatiei celulei
	memcpy(aux->info, ae, DIME_S(s));

	// construirea legaturilor 
	// aux devine noul varf al stivei
	aux->urm = VF(s);
	VF(s) = aux;
	// numarul de elemente din stiva se mareste
	++NR_E_S(s);

	return 1;
}

// extrage un element din stiva s, iar informatia este copiata
// la adresa ae
int Pop(void *s, void *ae)
{
	ACel_s aux;

	if(VIDA_S(s))
		return 0;

	aux = VF(s);
	// copiaza informatia
	memcpy(ae, aux->info, DIME_S(s));
	// varful va fi urmatoarea celula
	VF(s) = VF(s)->urm;
	// eliberarea informatiei si a celulei
	FreeInfo((void**)&aux->info);
	FreeCel((void**)&aux);
	// scade numarul de elemente din stiva
	--NR_E_S(s);

	return 1;
}

// copiaza informatia din varful stivei la adresa ae
int Top(void *s, void *ae)
{
	if(VIDA_S(s))
		return 0;
	memcpy(ae, VF(s)->info, DIME_S(s));
	return 1;
}

// eliberare stiva
void FreeS(void **s)
{
	void *info = AlocInfo(DIME_S(*s));

	while(!VIDA_S(*s))
		Pop(*s, info);

	free(*s);
	*s = NULL;

	FreeInfo((void**)&info);
}

// afisarea stivei
void PrintS(void *s, FILE *output)
{
	// initializarea unei stive auxiliare in care se va introduce
	// informatia scoasa din stiva s
	// aceasta este folosita si pentru a reintroduce informatia
	// in stiva s
	void *info = AlocInfo(DIME_S(s));

	if(!info) return;

	AStiva aux = InitS(DIME_S(s));

	if(!aux)
	{
		FreeInfo((void**)&info);
		return;
	}

	while(!VIDA_S(s))
	{
		Pop(s, info);
		Push(aux, info);
	}
	fprintf(output, "\"");
	while(!VIDA_S(aux))
	{
		Pop(aux, info);
		// afisarea informatiei
		PrintInfo(info, output);
		Push(s, info);
	}
	fprintf(output, "\"\n");

	FreeInfo((void**)&info);
	FreeCel((void**)&aux);
}

// sortarea stivei
void SortS(void *s)
{
	size_t check;
	AStiva aux = InitS(DIME_S(s));

	if(!aux) return;

	void *info = AlocInfo(DIME_S(s));

	if(!info)
	{
		FreeS((void**)&aux);
		return;
	}
	void *info_aux = AlocInfo(DIME_S(s));

	if(!info_aux)
	{
		FreeS((void**)&aux);
		FreeInfo((void**)&info);
		return;
	}
	// aux - stiva ordonata
	// algoritmul extrage din s elemente si le introduce
	// in stiva aux doar daca elementul extras din s este mai mic decat
	// varful stivei aux, altfel extrage din stiva aux si introduce inapoi 
	// in s cat timp varful stivei aux este mai mare decat elementul curent
	// scos din s. Astfel aux se pastreaza ordonat
	while(!VIDA_S(s))
	{
		Pop(s, info);

		check = Top(aux, info_aux);
		while(check && BiggerID(info_aux, info))
		{
			Pop(aux, info_aux);
			Push(s, info_aux);
			check = Top(aux, info_aux);
		}
		Push(aux, info);
	}
	// varful stivei s va deveni varful stivei aux
	VF(s) = VF(aux);
	NR_E_S(s) = NR_E_S(aux);

	FreeCel((void**)&aux);
	FreeInfo((void**)&info);
	FreeInfo((void**)&info_aux);
}

//creeaza o copie rasturnata a lui s
// 1 - copiere cu succes
// 0 - nu a putut face copie
int CopyS(void *s, void *copy)
{
	AStiva aux = InitS(DIME_S(s));

	if(!aux) 
	{
		return 0;
	}

	void *info_aux = AlocInfo(DIME_S(s));

	if(!info_aux)
	{
		FreeS((void**)&aux);
		return 0;
	}

	// in aux se pastreaza elementele ce se vor introduce inapoi in s
	while(!VIDA_S(s))
	{
		Pop(s, info_aux);
		Push(copy, info_aux);
		Push(aux, info_aux);
	}

	while(!VIDA_S(aux))
	{
		Pop(aux, info_aux);
		Push(s, info_aux);
	}

	FreeInfo((void**)&info_aux);
	FreeS((void**)&aux);

	return 1;
}

void CorrectS(void *s, FILE *output)
{
	AStiva copy = InitS(DIME_S(s));

	if(!copy) return;

	// creeaza o copie a stivei s ce va fi
	// folosita in functia de determinare a celui mai
	// lung subsir de paranteze inchise corect
	// desi copy e rasturnata fata de s, rezultatul
	// lui Correct va fi acelasi
	if(!CopyS(s, copy))
	{
		FreeS((void**)&copy);
		return;
	}

	// Correct este folosita si pentru stive, cat si pentru cozi
	// ultimul parametru al functiei este un pointer la functia
	// de extragere a unui element din stiva/coada
	Correct(copy, output, Pop);

	FreeS((void**)&copy);
}