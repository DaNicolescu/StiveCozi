/* NICOLESCU Daniel-Marian - 314CB */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "TStiva-Lista.h"
#include "TCoada-Lista.h"
#include "TInfo.h"

// eliberare informatie
void FreeInfo(void **ae)
{
	free(*ae);

	*ae = NULL;
}

// eliberare celula
void FreeCel(void **ac)
{
	free(*ac);

	*ac = NULL;
}

// alocare memorie pentru informatie
void* AlocInfo(size_t d)
{
	TInfo *info = (TInfo*)malloc(d);

	if(!info)
		return NULL;

	return (void*)info;
}

// afisarea informatiei de la adresa ae
void PrintInfo(void *ae, FILE *output)
{
	fprintf(output, "%c", ((TInfo*)ae)->tip);
}

// verifica daca id-ul parantezei de la ae1 este mai mare decat id-ul
// parantezei de la ae2
int BiggerID(void *ae1, void *ae2)
{
	return ((TInfo*)ae1)->id_paranteza > ((TInfo*)ae2)->id_paranteza;
}

// functie folosita pentru Correct
// primul element din stiva de paranteze deschise va avea
// tipul * si id-ul dat ca parametru
void InfoStar(void *ae, size_t id)
{
	((TInfo*)ae)->id_paranteza = id;
	((TInfo*)ae)->tip = '*';
}

// functie folosita in Correct pentru renumerotarea parantezelor
// renumerotarea parantezelor este folosita pentru a determina lungimea 
// unui subsir de paranteze bine inchise
void ChangeID(void *ae, size_t id)
{
	((TInfo*)ae)->id_paranteza = id;
}

// verifica daca tipul parantezei de la ae este deschis
int OpenParan(void *ae)
{
	return ((TInfo*)ae)->tip == '(' || ((TInfo*)ae)->tip == '[' || 
		((TInfo*)ae)->tip == '{';
}

// verifica daca paranteza de la ae1 este deschisa, paranteza de la ae2
// este inchisa si sunt de acelasi tip
int SameType(void *ae1, void *ae2)
{
	return (((TInfo*)ae1)->tip == '(' && ((TInfo*)ae2)->tip == ')') || 
		(((TInfo*)ae1)->tip == '[' && ((TInfo*)ae2)->tip == ']') ||
		(((TInfo*)ae1)->tip == '{' && ((TInfo*)ae2)->tip == '}');
}

// returneaza lungimea subsirului curent
size_t CurrentLen(void *ae1, void *ae2)
{
	return ((TInfo*)ae1)->id_paranteza - ((TInfo*)ae2)->id_paranteza;
}

// Correct runumeroteaza parantezele, schimbandu-le id-ul.
// Pentru a putea afla lungimea subsirului maxim corect, introduce
// parantezele deschise intr-o stiva auxiliara, daca intalneste
// vreo paranteza inchisa, face Pop din stiva aux si se verifica daca
// sunt de acelasi tip. Daca sunt de acelasi tip, atunci, pentru a afla
// lungimea subsirului corect curent, se face top pe aux.
// Cand se face top, se va copia fie paranteza anterioara, fie info_star.
// info_star este folosit ca o baza a subsirului corect curent de 
// paranteze deschise din aux.
// La inceput, baza stivei aux are id-ul 0. Dupa ce s-a aflat lungimea
// primului subsir corect si/sau se identifica o paranteza pusa gresit, id-ul 
// acelei paranteze va fi folosit drept baza pentru noul subsir corect 
// ce se poate afla in sirul de paranteze
//            _______________        _______________
// Ex: ( [ { [ ] ( [ ] ) {  } ​ ]  ) ​ [  ]  {  }  (  )
//     1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19
// Primul element din stiva auxiliara este *, cu id-ul 0
// Se introduc cele 4 paranteze deschise in aux: 
// * ( [ { ​[
// 0 1 2 3 4
// paranteza curenta din stiva este ], se extrage o paranteza din aux
// * ( [ {
// 0 1 2 3
// paranteza din sirul de paranteze si cea scoasa din aux sunt de acelasi
// tip, se face top pe aux si se face diferenta dintre id-urile parantezei
// din s si cea copiata cu top. lungimea rezultata este 2.
// se introduc alte 2 paranteze deschise in aux
// * ( [ { ( [
// 0 1 2 3 6 7
// urmatoarea paranteza din s este inchisa, se da pop la aux, sunt de acelasi
// tip, se face top, iar lungimea este 8-6 = 2
// aux devine:
// * ( [ { (
// 0 1 2 3 6
// urmatoarea paranteza din s e si ea inchisa si de acelasi tip cu cea din aux
// Se face top, id-ul parantezei copiate e 5, iar id-ul parantezei din s este 9
// lungimea e astfel 4
// Urmatoarea paranteza din s este deschisa
// * ( [ { {
// 0 1 2 3 10
// urmatoarea paranteza din s este inchisa, de acelasi tip cu cea din aux,
// se da top, iar noua lungime este 11-3 = 8
// aux :
// * ( [
// 0 1 2
// urmatoarea paranteza din s este inchisa, dar de tip diferit fata de cea din
// aux. Se elibereaza celelalte paranteze din aux, iar baza va avea id-ul
// parantezei gresite.
// aux:
// *
// 12
// Urmatoarea paranteza e inchisa, iar stiva aux nu are paranteze
// deschise. aux devine:
// *
// 13
// urmatoarea paranteza din s este deschisa:
// *  [
// 13 14
// urmatoarea paranteza din s este inchisa
// lungimea subsirului corect curent este 2 ...
// in final lungimea maxima ramane 8
void Correct(void *s, FILE *output, GetElemF GetElem)
{
	AStiva aux = InitS(DIME_S(s));
	void *info_s = AlocInfo(DIME_S(s));
	void *info_aux = AlocInfo(DIME_S(s));
	void *info_star = AlocInfo(DIME_S(s));
	void *info_ant = AlocInfo(DIME_S(s));
	size_t maxlen = 0;
	size_t i = 0;

	InfoStar(info_star, 0);
	Push(aux, info_star);

	while(!VIDA_S(s))
	{
		++i;
		//extrage element din s
		GetElem(s, info_s);
		//renumeroteaza paranteza
		ChangeID(info_s, i);

		//daca e paranteza deschisa o introduce in aux
		if(OpenParan(info_s))
			Push(aux, info_s);
		//daca e paranteza inchisa
		else
		{
			Pop(aux, info_aux);
			//verfica daca paranteza curenta din s si cea din aux sunt
			//de acelasi tip
			if(SameType(info_aux, info_s))
			{
				//se face top pe aux si se determina daca lungimea 
				//subsirului curent e mai mare decat maximul curent
				Top(aux, info_ant);

				if(CurrentLen(info_s, info_ant) > maxlen)
					maxlen = CurrentLen(info_s, info_ant);
			}
			else
			{
				//daca paranteza din s este inchisa dar de tip diferit
				//fata de cea din aux, sau aux nu contine paranteze deschise
				//se elibereaza stiva aux si id-ul bazei se schimba cu id-ul
				//parantezei curente din s 
				while(!VIDA_S(aux))
					Pop(aux, info_s);

				ChangeID(info_s, i);
				Push(aux, info_s);
			}
		}
	}

	FreeS((void**)&aux);
	FreeInfo((void**)&info_s);
	FreeInfo((void**)&info_aux);
	FreeInfo((void**)&info_star);
	FreeInfo((void**)&info_ant);

	fprintf(output, "%zu\n", maxlen);
}