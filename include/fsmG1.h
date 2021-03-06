/*
	fsmG1.h
	
interpreter les lexemes (les rassembler en structure logique) determiner dans quoi les mettres

!!!pas les noms definitifs il fauit les changer!!! peut evoluer !!!
conddebutg1
condEndG1
updatefsmG1state

gere .bss .data .text en me temps mais check apres coup si cest valide
*/
#ifndef _fsmG1_H_
#define _fsmG1_H_

#include "list.h"
#include "secData.h"
#include "secText.h"
#include "symb.h"
#include "reloc.h"
#include "erreur.h"
/* la data colection qui enclobe tout */
struct _globCol{
    DATACOL data;
    DATACOL bss;
    TEXTCOL text; /* possible par un astucieux bricolage ? */
    /* reste ,la table de symb, text*/
}; typedef struct _globCol COLG;

enum _stateg1{
	initG,
	attFinSpace,
	attFinWord,
	attFinByte,
	attFinAsciiz,
	attArgSpace,
	attArgByte,
	attArgAsciiz,
	attArgWord,
	attArgText,
	attTextpg,
	attTextreg,
	attTextpd,
	attFinText,
	TEXT,
	BSS,
	DATA,
	SPACE,
	ASCIIZ,
	BYTE,
	WORD,
	INSTRUCTION,
	error
};
typedef enum _stateg1 STATEG1;

char condStartG1(LIST * lex, LIST nullLex,COLG * pcol,LISTH * pendingEtiq,STATEG1* pstate);

char condEndG1(LIST lex, LIST nullLEx, SECTION* sec,STATEG1* pstate,COLG *pcol,INSTR * dico,int sizeDico,LISTH * pendingEtiq,LISTH * TAB,RELOCLIST* reloclist);

STATEG1 updateSTATEG1(LIST lex,STATEG1 state, SECTION * psec,COLG * pcol,INSTR * dico,int sizeDico,LISTH * pendingEtiq,LISTH * TAB, RELOCLIST* reloclist);

char isFinalG1(STATEG1 state);

#endif