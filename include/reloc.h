#ifndef _relocation_
#define _relocation_

#include <stdio.h>

#include "secData.h"
#include "list.h"
#include "hach.h"

enum _relocType {
    R_MIPS_32=2,
    R_MIPS_26=4,
    R_MIPS_HI16=5,
    R_MIPS_LO16=6
}; typedef enum _relocType RELOCTYPE;

struct _reloclist {
    SECTION sec;
    int offset;
    RELOCTYPE relocType;
    LISTH pHach;
    LIST lex;
    struct _reloclist * suiv;
}; typedef struct _reloclist* RELOCLIST;

RELOCLIST addHeadR(RELOCLIST l,SECTION sec, int offset, RELOCTYPE type, LISTH indHach,LIST lex);

void printELR(RELOCLIST);

void printAllElR(RELOCLIST);

void freeListR(RELOCLIST);
#endif