/* NICOLESCU Daniel-Marian - 314CB */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "TStiva.h"
#include "TCoada.h"
#include "TStiva-Lista.h"
#include "TCoada-Lista.h"
#include "TInfo.h"
#include "Functii_Comune.h"

int main(int argc, char *argv[])
{
	//numarul de operatii, numarul de stive, numarul de cozi
	size_t nr_op, nr_s, nr_c;
	//stivele
	void **s;
	//cozile
	void **c;
	size_t i, j;
	int check;

	TInfo *info, *elimina;
	char operatie[50];
	size_t id_stiva, id_coada;

	if(argc != 3)
	{
		printf("Not enough arguments");
		return 0;
	}

	FILE *input = fopen(argv[1], "r");

	if(!input)
	{
		printf("No such input file");
		return -1;
	}

	FILE *output = fopen(argv[2], "w");

	fscanf(input, "%zu", &nr_op);
	fscanf(input, "%zu", &nr_s);
	fscanf(input, "%zu", &nr_c);

	s = (void**)malloc(nr_s * sizeof(void*));

	if(!s) return -2;

	c = (void**)malloc(nr_c * sizeof(void*));

	if(!c) 
	{
		free(s);
		return -2;
	}

	for(i = 0; i < nr_s; i++)
	{
		s[i] = InitS(sizeof(TInfo));

		if(!s[i])
		{
			for(j = 0; j < i; j++)
				free(s[j]);
			free(s);
			free(c);
			return -2;
		}
	}

	for(i = 0; i < nr_c; i++)
	{
		c[i] = InitQ(sizeof(TInfo));

		if(!c[i])
		{
			for(j = 0; j < nr_s; j++)
				free(s[j]);
			free(s);

			for(j = 0; j < i; j++)
				free(c[j]);
			free(c);
			return -2;
		}
	}

	info = (TInfo*)malloc(sizeof(TInfo));

	if(!info)
	{
		for(i = 0; i < nr_s; i++)
			free(s[i]);
		free(s);

		for(i = 0; i < nr_c; i++)
			free(c[i]);
		free(c);

		return -2;
	}

	elimina = (TInfo*)malloc(sizeof(TInfo));

	if(!elimina)
	{
		for(i = 0; i < nr_s; i++)
			free(s[i]);
		free(s);

		for(i = 0; i < nr_c; i++)
			free(c[i]);
		free(c);

		free(info);

		return -2;
	}

	for(i = 0; i < nr_op; i++)
	{
		fscanf(input, "%s", operatie);

		if(!strcmp(operatie, "push"))
		{
			fscanf(input, "%zu", &id_stiva);
			fscanf(input, "%zu", &info->id_paranteza);
			fscanf(input, " %c", &info->tip);

			check = Push((void*)s[id_stiva], (void*)info);

			if(!check)
			{
				for(i = 0; i < nr_c; i++)
					FreeC(&c[i]);
				free(c);

				for(i = 0; i < nr_s; i++)
					FreeS(&s[i]);
				free(s);

				FreeInfo((void**)&info);
				FreeInfo((void**)&elimina);

				fclose(input);
				fclose(output);

				return -2;
			}
		}
		if(!strcmp(operatie, "intrq"))
		{
			fscanf(input, "%zu", &id_coada);
			fscanf(input, "%zu", &info->id_paranteza);
			fscanf(input, " %c", &info->tip);

			check = IntrQ((void*)c[id_coada], (void*)info);

			if(!check)
			{
				for(i = 0; i < nr_c; i++)
					FreeC(&c[i]);
				free(c);

				for(i = 0; i < nr_s; i++)
					FreeS(&s[i]);
				free(s);

				FreeInfo((void**)&info);
				FreeInfo((void**)&elimina);

				fclose(input);
				fclose(output);

				return -2;
			}
		}
		if(!strcmp(operatie, "pop"))
		{
			fscanf(input, "%zu", &id_stiva);

			Pop((void*)s[id_stiva], elimina);
		}
		if(!strcmp(operatie, "extrq"))
		{
			fscanf(input, "%zu", &id_coada);

			ExtrQ((void*)c[id_coada], elimina);
		}
		if(!strcmp(operatie, "sorts"))
		{
			fscanf(input, "%zu", &id_stiva);

			SortS((void*)s[id_stiva]);
		}
		if(!strcmp(operatie, "sortq"))
		{
			fscanf(input, "%zu", &id_coada);

			SortQ((void*)c[id_coada]);
		}
		if(!strcmp(operatie, "prints"))
		{
			for(j = 0; j < nr_s; j++)
				PrintS((void*)s[j], output);
		}
		if(!strcmp(operatie, "printq"))
		{
			for(j = 0; j < nr_c; j++)
				PrintQ((void*)c[j], output);
		}
		if(!strcmp(operatie, "corrects"))
		{
			fscanf(input, "%zu", &id_stiva);

			CorrectS((void*)s[id_stiva], output);
		}
		if(!strcmp(operatie, "correctq"))
		{
			fscanf(input, "%zu", &id_coada);

			CorrectQ((void*)c[id_coada], output);
		}
	}

	// eliberare cozi
	for(i = 0; i < nr_c; i++)
		FreeC(&c[i]);
	free(c);

	// eliberare stive
	for(i = 0; i < nr_s; i++)
		FreeS(&s[i]);
	free(s);

	FreeInfo((void**)&info);
	FreeInfo((void**)&elimina);

	fclose(input);
	fclose(output);

	return 1;
}