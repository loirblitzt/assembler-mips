/** Gestion des erreurs pour les directives et les instructions **/
#ifndef _erreur_
#define _erreur_
#include "fsmG1.h"
#include <stdio.h>
#include "list.h"
#include "secText.h"
#include "dicoG1.h"

/* #include "secData.h" */
enum _stateg2{
	binitG,
	battFinSpace,
	battFinWord,
	battFinByte,
	battFinAsciiz,
	battArgSpace,
	battArgByte,
	battArgAsciiz,
	battArgWord,
	battArgText,
	battTextpg,
	battTextreg,
	battTextpd,
	battFinText,
	bTEXT,
	bBSS,
	bDATA,
	bSPACE,
	bASCIIZ,
	bBYTE,
	bWORD,
	bINSTRUCTION,
	berror
};
typedef enum _stateg2 STATEG2;
int erreurDirective(STATEG2 state, char* lex);
#endif