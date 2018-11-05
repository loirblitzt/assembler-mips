/* gere la fsm pour la grammaire 1 */

#include "fsmG1.h"

char condStartG1(LIST * lex,LIST nullLex,COLG * pcol){
    if((*lex)->type == commentaire ||(*lex)->type == retourLine )return 1;
    if ((*lex)->type == directive && (strcmp((*lex)->data,".set")==0)){
        *lex = (*lex)->suiv;
        if(*lex == nullLex) return 1; /* the null case is handled in the while loop */
        if((*lex)->type == symb && (strcmp((*lex)->data,"noreorder")==0) ){
            return 1;
        }
    }
    return 0; /* end the loop */
}

/* same as fsm.c */
char condEndG1(LIST lex, LIST nullLEx, SECTION* psec,STATEG1* pstate,COLG * pcol){
    *pstate = updateSTATEG1(lex,*pstate,psec,pcol);
    return !isFinalG1(*pstate);
}

STATEG1 updateSTATEG1(LIST lex,STATEG1 state,SECTION* psec,COLG * pcol){
    /* if (isFinalG1(state)) return state; */
    /* if .text???? TODO */
    switch(state){
        case initG:
            /* gestion des directives de sectionnement , avant le switch sur la section*/
            if(lex->type == directive){
                if(strcmp(lex->data,".text")==0){
                    *psec = text;
                    return TEXT;
                }
                else if(strcmp(lex->data,".data")==0){
                    *psec = data;
                    return DATA;
                }
                else if(strcmp(lex->data,".bss")==0){
                    *psec = bss;
                    return BSS;
                }
            }
            switch (*psec){
                case data:
                    /* gestion des directives de data */
                    if (lex->type == directive && strcmp(lex->data,".byte")==0){
                        return attArgByte;
                    }
                    if (lex->type == directive && strcmp(lex->data,".word")==0){
                        return attArgWord;
                    }
                    if (lex->type == directive && strcmp(lex->data,".asciiz")==0){
                        return attArgAsciiz;
                    }
                case bss:
                    /* gestion de .space pour data et bss */
                    if (lex->type == directive && strcmp(lex->data,".space")==0){
                        return attArgSpace;
                    }
                    else{
                        /* ERROR */
                    }
                break;
                case text:
                    /* gestion pour la section text */
                break;
            }
        break;
        case attArgSpace:
            if (lex->type == decimal /* || lex->type == hexa */){
                /* package into data struct
                can we expect a second argument? 
                is hexa accepted ?*/
                unsigned int d = strtol(lex->data,NULL,0);
                (pcol->data).currentOffset += d;
                if(*psec == data){
                    addHeadG(&(pcol->data),(DATAG)d,uintG,(pcol->data).currentOffset,lex->line);
                }
                return attFinSpace;
            }
            else{ return error;}
        break;
        case attFinSpace:
            if (lex->type == retourLine) return SPACE;
            else if (lex->type == virgule) return attArgSpace;
            else{return error;}
        break;
    }
}

char isFinalG1(STATEG1 state){
	if (((int)state >= (int)TEXT)){
		return 1;
	}
	return 0;
}