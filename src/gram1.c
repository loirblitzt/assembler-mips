/* this code has the same conventions and working logic than
lex.c */

#include "list.h"
#include "fsmG1.h"

/* identificate an element and its collection */
char getNextTokenG1(LISTE lex){
    LISTE tmp = createList();
    /* enum to indicate in which section we are */

    /* boucle debut : trouve le premier element
    saute : retour ligne commentaire , et peut etre le .set noreoder gere les etiquettes */

    /* boucle fin */
    
    /* check conformite & package */
    if (1){  /* TODO : remplacer le 1 par un cond darret de loadlex */
        
        return 1; /* value to continue the reading of lex */
    }
    return 0;
}

void G1LoadLex(LISTE lex/* ,other collections to be returned to main */){
    while(getNextTokenG1(lex/*, other shit  */))
}