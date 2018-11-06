
#include "secText.h"

TEXTCOL createTextCol(){
    TEXTCOL col = {NULL,0};
    return col;
}

void addHeadText(TEXTCOL * col, int instr,unsigned int line,char nbop,int decalage,LIST op1,LIST op2,LIST op3){
    TEXTLIST tmpl = (TEXTLIST)malloc(sizeof(*tmpl));

    tmpl->instr = instr; tmpl->line = line; tmpl->nbop=nbop; tmpl->decalage=decalage;
    (tmpl->op)[0] = op1;(tmpl->op)[1] = op2;(tmpl->op)[2] = op3;

    if(col->l == NULL){
        tmpl->suiv = tmpl;
    }
    else{
        tmpl->suiv = (col->l)->suiv;
        (col->l)->suiv = tmpl;
    }
    col->l = tmpl;/* return the head "the last in"  */
}

void printElT(TEXTLIST l,INSTR * dico){
    printf("---------------\n");
    printf("instruction : %s\nligne : %d\nnombre doperandes : %d\ndecalage : %d\n",dico[l->instr].name,
            l->line,l->nbop,l->decalage);
    printf("----Opérandes : \n");
    if(l->op[0] != NULL)printData(l->op[0]);
    if(l->op[1] != NULL)printData(l->op[1]);
    if(l->op[2] != NULL)printData(l->op[2]);
    printf("---------------\n");
}

void printColT(TEXTCOL col,INSTR * dico){
    printf("Collection de la section : text\n");
    if(col.l!=NULL){
        TEXTLIST l = ((col.l)->suiv);
        do{
        printElT(l,dico);
        l = l->suiv;
    }while(l!=((col.l)->suiv)  );}
    else{
        printf("collection vide\n");
    }
}

void freeElT(TEXTLIST l){
    free(l);
}

void freeColT(TEXTCOL col){
    if(col.l!=NULL){
        TEXTLIST c = (col.l)->suiv;
        col.l->suiv = NULL;
        while(c!=NULL){
            TEXTLIST tmp = c->suiv;
            freeElT(c);
            c=tmp;
        }
    }
}

char addRegister(LIST lex,TEXTLIST l){
    if(l->op[0]==NULL){
        l->op[0] = lex;
        return 1;
    }
    else if (l->op[1]==NULL){
        l->op[1] = lex;
        return 1;
    }
    else if (l->op[2]==NULL){
        l->op[2] = lex;
        return 1;
    }
    return 0;
}