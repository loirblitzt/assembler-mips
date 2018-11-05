#include "secData.h"

DATACOL createDataCol(){
    DATACOL col = {NULL,none,0}; /* 0 == NULL type for datalist */
    return col ;
}

/*ajout*/
void addHeadG(DATACOL * col, DATAG data, TYPEG1 type, int offset, int nbline){
    DATALIST tmpl = (DATALIST)malloc(sizeof(*tmpl));

    tmpl->type= type; tmpl->offset = offset; tmpl->nbLine = nbline;
    tmpl->data = data; /* halla waka bah */

    if(col->l == NULL){
        tmpl->suiv = tmpl;
    }
    else{
        tmpl->suiv = (col->l)->suiv;
        (col->l)->suiv = tmpl;
    }
    col->l = tmpl;/* return the head "the last in"  */
}

/* affichage */
void printElementG(DATALIST l){
    printf("---------------\n");
    switch(l->type){
        case intG:
            printf("type : int\ndata : %d\n",(l->data).word);
        break;
        case uintG:
            printf("type : int\ndata : %d\n",(l->data).space);
        break;
        case charG:
            printf("type : int\ndata : %d\n",(l->data).byte);
        break;
        case symbG:
            printf("type : string\ndata : %s\n",(l->data).asciiz);
        break;
    }
    printf("offset : %d\nnbLine : %d\n",l->offset,l->nbLine);
    printf("---------------\n");
}
char* printsec[]={"none",
                "text",
                "data",
                "bss"};
void printSection(SECTION sec){
    printf("Collection de la section : %s\n",printsec[(int)sec]);
}

void printColG(DATACOL col){
    printSection(col.sec);
    if(col.l!=NULL){
    DATALIST l =(col.l)->suiv;
    do{
        printElementG(l);
        l = l->suiv;
    }while(l!=((col.l)->suiv)  );}
    else{
        printf("collection vide\n");
    }
}
/*suppression*/

void freeElementG(DATALIST l){
    free(l);
}

void freeColG(DATACOL col){
    if(col.l!=NULL){
        DATALIST c = (col.l)->suiv;
        col.l->suiv = NULL;
        while(c!=NULL){
            DATALIST tmp = c->suiv;
            freeElementG(c);
            c=tmp;
        }
    }
}