/* this code has the same conventions and working logic than
lex.c */

#include "gram1.h"

/* identificate an element and its collection */
LIST getNextTokenG1(LIST lex,LIST currLex, SECTION* sec){
    LIST tmp = currLex;
    if (tmp == lex) return NULL; /* peut etre inutile */

    /* boucle debut : trouve le premier element
    saute : retour ligne commentaire , et peut etre le .set noreoder gere les etiquettes */
    while (condStartG1(&tmp,lex)){
        printData(tmp);
        if (tmp == lex) return NULL;
        tmp = tmp -> suiv;
    }return NULL;
    /* boucle fin */
    while (condEndG1(tmp)){
        tmp = tmp -> suiv;
    }
    /* check conformite & package */
    if (1){  /* TODO : remplacer le 1 par un cond darret de loadlex */
        
        return tmp; /* value to continue the reading of lex */
    }
    return NULL;
}

/* restart (sort of) the fsmG1 when a final state is reach*/
void G1LoadLex(LIST lex/* ,other collections to be returned to main */){
    if (lex != NULL ){
        LIST currLex = lex->suiv;
        /* global info */
        SECTION currSection = none;

        while((currLex = getNextTokenG1(lex,currLex, &currSection/*, other shit  */)) !=NULL ){
            /* affiche  */
        }
    }
}