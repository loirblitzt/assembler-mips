/*

	secData.h
gere la collection de .data
reste à definir la sttructure de la collection

en soit cest juste une liste
*/
#ifndef _secdata_h_
#define _secdata_h_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum _typeG1{
	intG,
	charG,
	uintG,
	symbG
}; typedef enum _typeG1 TYPEG1;

enum _directive{
	space,
	byte,
	word,
	ascizz
}; typedef enum _directive DIRG1;

enum _section {
	none,
	text,
	data,
	bss
}; 
typedef enum _section SECTION;

union _dataG {
	unsigned int space;
	char* asciiz;
	int word;
	char byte;
}; typedef union _dataG DATAG;

struct _dataList {
	DATAG data;	
	TYPEG1 type;
/* 	DIRG1 dir; avec le nom de la dir on peut
	savoir la taille de la donne et ou son utilite
	 A VOIR */
	int offset; /* la section est précisé dans datacol */
	int nbLine;
	struct _dataList* suiv;
}; 
typedef struct _dataList* DATALIST;

struct _dataColection {
	DATALIST l;
	SECTION sec;
	int currentOffset; /* curent offset kept in memory */
};
typedef struct _dataColection DATACOL;
/*creation*/
DATACOL createDataCol();

/*ajout*/
void addHeadG(DATACOL * col, DATAG data, 
			TYPEG1 type, int offset, int nbline);

/* affichage */
void printElementG(DATALIST l);

void printColG(DATACOL col);
/*suppression*/

void freeElementG(DATALIST l);

void freeColG(DATACOL col);

#endif