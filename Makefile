build: tema2.o Functii_Comune.o Functii_Coada.o Functii_Stiva.o
	gcc tema2.o Functii_Comune.o Functii_Coada.o Functii_Stiva.o -o tema2
tema2.o: tema2.c
	gcc -Wall -c tema2.c
Functii_Comune.o: Functii_Comune.c
	gcc -Wall -c Functii_Comune.c
Functii_Coada.o: Functii_Coada.c
	gcc -Wall -c Functii_Coada.c
Functii_Stiva.o: Functii_Stiva.c
	gcc -Wall -c Functii_Stiva.c
clean:
	rm -f *.o tema2	
