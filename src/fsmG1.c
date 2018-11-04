/* gere la fsm pour la grammaire 1 */

#include "fsmG1.h"

char condStartG1(LIST * lex,LIST nullLex){
    if((*lex)->type == commentaire ||(*lex)->type == retourLine )return 1;
    if ((*lex)->type == directive && (strcmp((*lex)->data,".set")==0)){
        *lex = (*lex)->suiv;
        if(*lex == nullLex) return 1; /* the null case is handled in the while loop */
        if((*lex)->type == symb && (strcmp((*lex)->data,"noreorder")==0) ){
            return 1;
        }
    }
    return 0;
}

/* char condEndG1() */
