/* this code has the same conventions and working logic than
lex.c */

#include "gram1.h"

/* identificate an element and its collection */
LIST getNextTokenG1(LIST lex,LIST currLex, SECTION* sec,COLG * pcol){
    LIST tmp = currLex;
    STATEG1 state = initG;
    if (tmp == lex) return NULL; /* peut etre inutile */

    /* boucle debut : trouve le premier element
    saute : retour ligne commentaire , et peut etre le .set noreoder gere les etiquettes */
    while (condStartG1(&tmp,lex,pcol)){
        if (tmp == lex) return NULL;
        tmp = tmp -> suiv;
    }
    /* boucle fin */
    while (condEndG1(tmp,lex,sec,&state,pcol)){
        if (tmp == lex){ printf("ERROR\n"); return NULL;}
        tmp = tmp -> suiv;
    }
    /* check conformite & package */
    if (state == error){printf("\033[31m:ERROR IN FSM:\033[0m\n");return NULL;}
    if (tmp != lex){
        return tmp->suiv; /* value to continue the reading of lex */
    }
    return NULL;
}

/* restart (sort of) the fsmG1 when a final state is reach*/
void G1LoadLex(LIST lex,COLG *pcol/* ,other collections to be returned to main */){
    if (lex != NULL ){
        LIST currLex = lex->suiv;
        /* global info */
        SECTION currSection = none;

        while((currLex = getNextTokenG1(lex,currLex, &currSection,pcol/*, other shit  */)) !=NULL ){
            /* affiche  */
        }
    }
}