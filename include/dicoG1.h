/*
	dicoG1.h

gere lutilisation du dico pour le .text 
fonctionnalitées :
-chercher instruction
- choper les types des opérandes et leur nombre
*/
#ifndef _dico_
#define _dico_

#include <stdio.h>

struct _instr {
	char * name;
	char type;
	char numOp;
}; typedef struct _instr INSTR;

INSTR* loadDico(char * nameFile,int *);

int searchDico(char* inst,INSTR * dico,int);

void freeDico(INSTR * dico,int);
#endif