#include "reloc.h"

RELOCLIST addHeadR(RELOCLIST l,SECTION sec, int offset, RELOCTYPE type, LISTH indHach,LIST lex){
    RELOCLIST tmpl = (RELOCLIST)malloc(sizeof(*tmpl));
    tmpl->lex = lex;tmpl->pHach=indHach;tmpl->offset=offset;tmpl->relocType=type;tmpl->sec=sec;
    if(l==NULL){
        tmpl->suiv =tmpl;
    }
    else{
        tmpl->suiv = l->suiv;
        l->suiv = tmpl;
    }
    return tmpl;
}

char* reloctype[] = {
    "R_MIPS_32",
    "o",
    "R_MIPS_26",
    "R_MIPS_HI16",
    "R_MIPS_LO16",
};
char* mesgRH[]={
  "nullH",
  "textH",
  "dataH",
  "bssH"
};
void printELR(RELOCLIST l){
    printf("--------------\n");
    printSection(l->sec);
    printf("offset : %d\n",(l->offset)/* -2 */);/* why did i put -2 in here */
    if(l->pHach!=NULL){
        printf("def etiquette : %s\n  section : %s\n  offset : %d\n",(char*)(l->pHach->s),mesgRH[(int)(l->pHach->section)],l->pHach->decalage);
    }
    else{
        printf("def etiquette : %s : inconnue\n",(char*)(l->lex->data));
    }
    printf("--------------\n");
}

void printAllElR(RELOCLIST l){
    if(l!=NULL){
        RELOCLIST tmp = l->suiv;
        do{
            printELR(tmp);
            tmp = tmp-> suiv;
        }while (tmp!=(l->suiv));
    }
    else {
        printf("relocation list empty\n");
    }
}


void freeListR(RELOCLIST l){
    if(l!=NULL){
        RELOCLIST tmp = l->suiv;
        l->suiv= NULL;
        while(tmp!=NULL){
            RELOCLIST a = tmp->suiv;
            free(tmp);
            tmp=a;
        }
    }
}

/* update non-discovered etiq  */
void updateReloc(RELOCLIST relocL, LISTH * TAB){
    if(relocL != NULL ){
        RELOCLIST cursor = relocL->suiv;
        do{
            if(cursor->pHach == NULL){
                cursor->pHach = seekSymb((char*)(cursor->lex->data),TAB);
            }
            cursor = cursor->suiv;
        }while(cursor != relocL->suiv);
    }
}

/* looks for a struct with a field lex->name equals to name */
RELOCLIST seekWithName(char * name , RELOCLIST l){
    if (l == NULL)return NULL;
    RELOCLIST cur = l->suiv;
    do{
        if(strcmp(name,cur->lex->data)==0){
            return cur;
        }
        cur = cur->suiv;
    }while(cur != l->suiv);
    return NULL;
}