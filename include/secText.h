/* sectext.h handle the text collection */

#ifndef _sec_text_
#define _sec_text_

#include "list.h"
#include "dicoG1.h"
#include <stdio.h>

struct _textlist {
    int instr;/* indice dans dico */
    unsigned int line;
    char nbop;
    int decalage;
    LIST op[3];/* bcause 3 arguemnts max */
    struct _textlist * suiv;
}; typedef struct _textlist* TEXTLIST;

struct _textcol{
    TEXTLIST l;
    int currOffset;
}; typedef struct _textcol TEXTCOL;

TEXTCOL createTextCol();

void addHeadText(TEXTCOL * col, int instr,unsigned int line,
                char nbop,int decalage,LIST op1,LIST op2,LIST op3);

/* returns 1 for sucess */
char addRegister(LIST lex,TEXTLIST l);

void printElT(TEXTLIST l, INSTR * dico);

void printColT(TEXTCOL col,INSTR * dico);

void freeElT(TEXTLIST l);

void freeColT(TEXTCOL col);

#endif