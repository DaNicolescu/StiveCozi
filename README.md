StiveCozi
	In main se initializeaza stivele si cozile si se citesc datele
din fisier. De asemenea sunt apelate functiile corespunzatoare fiecarei operatii.
La sfarsit se realizeaza eliberarile de memorie.
	Functii pentru stive:  
	InitS primeste ca parametru dimensiunea informatiei si aloca o structura
AStiva. Seteaza DIME_S cu parametrul primit, initializeaza numarul de elemente
cu 0 si varful NULL.  
	Push introduce un element in stiva cu informatia de la adresa primita
ca parametru. Aloca spatiu pentru o celula (ACel_s) si pentru informatia din
acea celula, apoi copiaza informatia de la adresa primita ca parametru la adresa
celulei nou alocate, seteaza varful ca fiind noua celula alocata si incrementeaza
numarul de elemente din stiva.  
	Pop extrage un element din stiva. Copiaza informatia din varful stivei
la adresa primita ca parametru, muta varful pe celula urmatoare, apoi
elibereaza informatia si celula vechiului varf.  
	Top copiaza la adresa primita ca parametru informatia din varful stivei.
	FreeS elibereaza stiva.  
	PrintS rastoarna elementele stivei primite ca parametru intr-o stiva
auxliara, apoi, in timp ce le reintroduce in stiva initiala, afiseaza
informatia elementului curent.  
	SortS foloseste o stiva auxiliara pentru sortare. Extrage din stiva s
primita ca parametru elemente si le introduce in stiva aux doar daca elementul
extras din stiva este mai mic decat varful stivei aux, altfel extrage din 
stiva aux si introduce inapoi in stiva data ca parametru cat timp varful 
stivei aux este mai mare decat elementul curent scos din s. Astfel aux se 
pastreaza ordonat.  
	CopyS creeaza o copie rasturnata a stivei primite ca parametru.
Functia e folosita in cadrul functiei de Correct.  
	CorrectS determina lungimea celui mai lung subsir corect parantezat
din stiva s data ca parametru. Creeaza o copie a lui s, apoi apeleaza functia
Correct ce determina practic lungimea subsirului. Correct e folosita atat
pentru stiva, cat si pentru coada. Unul din parametrii functiei este un
pointer la functia de extragere a elementului din stiva/coada.  
	Correct runumeroteaza parantezele, schimbandu-le id-ul. Cat timp 
exista elemente de extras din stiva/coada data ca parametru:  
	Extrage un element. Daca e paranteza deschisa o introduce intr-o stiva 
auxiliara, daca e paranteza inchisa, se face Pop din stiva aux si se verifica 
daca sunt de acelasi tip. Daca sunt de acelasi tip, atunci, pentru a afla
lungimea subsirului corect curent, se face top pe aux. Cand se face top, 
se va copia fie paranteza anterioara, fie info_star. info_star este folosit ca 
o baza a subsirului corect curent de paranteze deschise din aux. Se compara
apoi lungimea subsirului curent cu maximul curent. Daca paranteza din s este 
inchisa dar de tip diferit fata de cea din aux, sau aux nu contine paranteze
deschise, atunci se elibereaza stiva aux si id-ul bazei se schimba cu id-ul 
parantezei curente din s.  
	Functii pentru cozi:  
	InitQ initializeaza coada. Aloca o structura ACoada, initializeaza
dimensiunea informatiei cu parametrul primit, numarul de elemente cu 0,
inceputul si sfarsitul cozii cu NULL.  
	IntrQ introduce un element in coada cu informatia de la adresa primita
ca parametru. Aloca o celula ACel_q si informatia de la acea celula, copiaza
informatia de la adresa data ca parametru la adresa informatiei structurii 
ACel_q, apoi modifica inceputul si sfarsitul cozii. Daca se introduce pentru
prima data in coada, inceputul si sfarsitul vor pointa catre aceeasi celula nou
alocata. Altfel, doar sfarsitul cozii va pointa catre noua celula.
La sfarsit se incrementeaza numarul de elemente din coada.  
	ExtrQ extrage un element din coada data ca parametru si copiaza
informatia de la acea celula la adresa ae, data ca parametru. In cazul in
care se extrage ultimul element din coada, sfarsitul cozii va deveni NULL.
	FreeC elibereaza coada din memorie.  
	PrintQ afiseaza coada c data ca parametru cu ajutorul unei cozi 
auxiliare. Elementele din c sunt extrase, iar informatia este afisata.
La sfarsit, coada c va primi inceputul, sfarsitul si numarul de elemente ale
cozii auxiliare, iar structura stivei aux va fi eliberata din memorie.
	CopyQ creeaza o copie a cozii date ca parametru. Functia este folosita
in cadrul functiei CorrectQ.  
	CorrectQ creeaza o copie a cozii date ca parametru si apeleaza functia
Correct de determinare a lungimii celui mai mare subsir corect de paranteze.
	SortQ sorteaza elementele cozii date ca parametru utilizand 2 stive
auxiliare. Initial muta toate elementele din coada in prima stiva auxiliara
cu exceptia celui mai mic element, pe care il introduce inapoi in coada.
Mai apoi, cat timp exista elemente de mutat, extrage din prima stiva auxiliara
si introduce in a doua stiva auxiliara cu exceptia minimului, pe care il
introduce in coada. La fel si in cazul
extragerii din a doua stiva si introducerii in prima. Extragerile si
introducerile din prima stiva in a doua si invers se produc cat timp exista
elemente de mutat.
