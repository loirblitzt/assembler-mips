/* gere la fsm pour la grammaire 1 */

#include "fsmG1.h"
char* pseudo[]={
    "NOP",
    "MOVE",
    "NEG",
    "LI",
    "BLT",
    "LW",
    "SW"
};
int isPseudoInstr(char* name){
    int i = 7;
    char isNotFound = 1;
    while(i > 0 && isNotFound){
        i--;
        isNotFound = strcasecmp(name,pseudo[i]);
    }
    if (!isNotFound){return i;}
    return -1;
}
char replaceInstr(LIST  lex,int indPInstr){
    /* the arguments of the pseudo instruction are supposed to be legal, otherwise the error will be handle later */
    LIST l = lex;
    LIST reg,target;
    switch(indPInstr){
        case -1:
            return 0; /* code for error */
        break;
        case 0: /* NOP */
            free(l->data);
            l->data = malloc((strlen("SLL")+1)*sizeof(char));
	        memcpy((l -> data),"SLL",(strlen("SLL")+1)*sizeof(char));
            l->type = symb;
            l = addHead2(l,(char*)"$0",registre,lex->line,3);
            l = addHead2(l,(char*)",",virgule,lex->line,2);
            l = addHead2(l,(char*)"$0",registre,lex->line,3);
            l = addHead2(l,(char*)",",virgule,lex->line,2);
            l = addHead2(l,(char*)"0",decimal,lex->line,2);
            l = addHead2(l,(char*)"\n",retourLine,lex->line,2);
        break;
        case 1: /* MOVE */
            free(l->data);
            l->data = malloc((strlen("ADD")+1)*sizeof(char));
	        memcpy((l -> data),"ADD",(strlen("ADD")+1)*sizeof(char));
            l->type = symb;
            l = l->suiv;
            if(l->type!= registre)return 0;
            l = l->suiv;
            if(l->type != virgule)return 0;
            l = l->suiv;
            if(l->type != registre)return 0;
            l = addHead2(l,(char*)",",virgule,lex->line,2);
            l = addHead2(l,"$0",registre,lex->line,3);            
        break;
        case 2:/* NEG */
            free(l->data);
            l->data = malloc((strlen("SUB")+1)*sizeof(char));
	        memcpy((l -> data),"SUB",(strlen("SUB")+1)*sizeof(char));
            l->type = symb;
            l = l->suiv;
            if(l->type!=registre)return 0;
            l= l->suiv;
            if(l->type != virgule)return 0;
            l = addHead2(l,"$0",registre,lex->line,3);
            l = addHead2(l,(char*)",",virgule,lex->line,2);
            l = l->suiv;
            if(l->type!=registre)return 0;
        break;
        case 3:/* LI */
            free(l->data);
            l->data = malloc((strlen("ADDI")+1)*sizeof(char));
	        memcpy((l -> data),"ADDI",(strlen("ADDI")+1)*sizeof(char));
            l->type = symb;
            l = l->suiv;
            if(l->type!=registre)return 0;
            l= l->suiv;
            if(l->type != virgule)return 0;
            l = addHead2(l,"$0",registre,lex->line,3);
            l = addHead2(l,(char*)",",virgule,lex->line,2);
            l = l->suiv;
            /* if(l->type!=registre)return 0;         */
        break;
        case 4:/* BLT */
            free(l->data);
            l->data = malloc((strlen("SLT")+1)*sizeof(char));
	        memcpy((l -> data),"SLT",(strlen("SLT")+1)*sizeof(char));
            l->type = symb;
            l = addHead2(l,"$1",registre,lex->line,3);
            l = addHead2(l,",",virgule,lex->line,2);
            l = l->suiv;
            if(l->type!=registre)return 0;
            l= l->suiv;
            if(l->type != virgule)return 0;
            l = l->suiv;
            if(l->type!=registre)return 0;
            l = addHead2(l,"\n",retourLine,lex->line,2);
            l = addHead2(l,"BNE",symb,lex->line,4);
            l = addHead2(l,"$1",registre,lex->line,3);
            l = addHead2(l,",",virgule,lex->line,2);
            l = addHead2(l,"$0",registre,lex->line,3);
        break;
        /* HALL OF THE WORST TO IMPLEMENT */
        case 5:/* LW */
            if(l->suiv != NULL && (l->suiv->type == registre )\
                && l->suiv->suiv != NULL && ((l->suiv)->suiv->type ==virgule) \
                && l->suiv->suiv->suiv != NULL && (l->suiv)->suiv->suiv->type == symb \
                && l->suiv->suiv->suiv->suiv != NULL && (l->suiv)->suiv->suiv->suiv->type != parentheseg ){
                    free(l->data);
                    l->data = malloc((strlen("LUI")+1)*sizeof(char));
	                memcpy((l -> data),"LUI",(strlen("LUI")+1)*sizeof(char));
                    l->type = symb;
                    l= l->suiv;
                    if(l->type!=registre)return 0;
                    reg = l;
                    l = l->suiv;
                    if(l->type != virgule)return 0;
                    l = l->suiv;
                    if(l->type != symb)return 0;
                    l->trueType=1;
                    target=l;
                    l = l->suiv;
                    l = addHead2(l,"LW",symb,lex->line,3);
                    l = addHead2(l,(char*)(reg->data),registre,lex->line,strlen(reg->data)+1);
                    l = addHead2(l,",",virgule,lex->line,2);
                    l = addHead2(l,(char*)(target->data),symb,lex->line,strlen(target->data)+1);
                    l = addHead2(l,"(",parentheseg,lex->line,2);
                    l = addHead2(l,"$1",registre,lex->line,3);
                    l = addHead2(l,")",parenthesed,lex->line,2);
                    l = addHead2(l,"\n",retourLine,lex->line,2);
                }
                else {
                    return 0;
                }
        
        break;
        case 6:/* SW */
            if(l->suiv != NULL && (l->suiv->type == registre )\
                && l->suiv->suiv != NULL && ((l->suiv)->suiv->type ==virgule) \
                && l->suiv->suiv->suiv != NULL && (l->suiv)->suiv->suiv->type == symb \
                && l->suiv->suiv->suiv->suiv != NULL && (l->suiv)->suiv->suiv->suiv->type != parentheseg ){
                    free(l->data);
                    l->data = malloc((strlen("LUI")+1)*sizeof(char));
	                memcpy((l -> data),"LUI",(strlen("LUI")+1)*sizeof(char));
                    l->type = symb;
                    l= l->suiv;
                    if(l->type!=registre)return 0;
                    reg = l;
                    l = l->suiv;
                    if(l->type != virgule)return 0;
                    l = l->suiv;
                    if(l->type != symb)return 0;
                    target=l;
                    l =lex->suiv;
                    l = addHead2(l,"$1",registre,lex->line,3);
                    l = addHead2(l,",",virgule,lex->line,2);
                    l = addHead2(l,target->data,retourLine,lex->line,strlen(target->data)+1);
                    l->trueType = 1;/* used to indicate if it is rmips_up o rmips_down relocation mode */
                    l = addHead2(l,"\n",retourLine,lex->line,2);
                    l = addHead2(l,"SW",symb,lex->line,3);
                    l = l->suiv;
                    l = l->suiv;
                    l = l->suiv;
                    l = addHead2(l,"(",parentheseg,lex->line,2);
                    l = addHead2(l,"$1",registre,lex->line,3);
                    l = addHead2(l,")",parenthesed,lex->line,2);
                }
                else {
                    return 0;
                }        
        break;
    }
    return 1;
}

char condStartG1(LIST * lex,LIST nullLex,COLG * pcol,LISTH * pendingEtiq,STATEG1* pstate,LIST * strTab){
    if((*lex)->type == commentaire ||(*lex)->type == retourLine )return 1;
    if ((*lex)->type == directive && (strcmp((*lex)->data,".set")==0)){
        *lex = (*lex)->suiv;
        if(*lex == nullLex) return 1; /* the null case is handled in the while loop */
        if((*lex)->type == symb && (strcmp((*lex)->data,"noreorder")==0) ){
            return 1;
        }
    }
    if ((*lex)->type == symb){
        LIST l = *lex;
        if((*lex)->suiv == nullLex) return 1;
        if(((*lex)->suiv)->type == deuxPoints){
            *lex = (*lex)->suiv;
            /* add to the strTab to use it then , it is in order*/
            *strTab = addHead2(*strTab,l->data,symb,0,strlen(l->data)+1);
            /* register l as a etiquette*/
            if(addToPending(pendingEtiq,(char *)(l->data))==0){
                *pstate = error;
            }
            return 1;/* continue the loop */
        }
    }
    return 0; /* end the loop */
}

/* same as fsm.c */
char condEndG1(LIST lex, LIST nullLEx, SECTION* psec,STATEG1* pstate,COLG * pcol,INSTR * dico,int sizeDico,LISTH * pendingEtiq,LISTH * TAB,RELOCLIST* reloclist){
    *pstate = updateSTATEG1(lex,*pstate,psec,pcol,dico, sizeDico,pendingEtiq,TAB,reloclist);
    return !isFinalG1(*pstate);
}

STATEG1 updateSTATEG1(LIST lex,STATEG1 state,SECTION* psec,COLG * pcol,INSTR * dico,int sizeDico,LISTH * pendingEtiq,LISTH * TAB,RELOCLIST* reloclist){
    int indiceDico;
    int indicePseudo;
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
                    else{printf("Le lexème devrait être une directive mais ne l'est pas\n");
                        /* ERROR */return error;
                    }
                break;
                case text:
                    /* gestion pour la section text */
                    /* here cannot be an etiquette because it is handled in condstart */
                    indicePseudo =isPseudoInstr((char*)(lex->data));
                    if(indicePseudo != -1){
                        replaceInstr(lex,indicePseudo);
                    }
                    indiceDico = searchDico(lex->data,dico,sizeDico); /* i will become the indice of the instruction in dico */
    /* package */   if(lex->type == symb && indiceDico>=0){
                        if(packagePending(pendingEtiq,TAB,*psec,(pcol->text).currOffset)==0){return error;}
                        addHeadText(&(pcol->text),indiceDico,lex->line,(char)dico[indiceDico].numOp,((pcol->text).currOffset),NULL,NULL,NULL);
                        (pcol->text).currOffset += 4;
                        return attArgText;
                    }
                    else{
                        printf("Le lexème devrait être une instruction connue\n");
                        return error;
                    }
                break;
            }
        break;
        case attTextreg:
            /* TODO: mettre registre dans les op ou pas ?*/
            if(addRegister(lex,pcol->text.l)==0)return error;
        case attTextpd:
        case attTextpg:
            return (STATEG1)(state+1);
        break;
        case attArgText:
            if (erreurInstruction(lex, pcol->text,dico,sizeDico)==0){
              return error;
            }
            if(isNumberOk(lex) && addRegister(lex,pcol->text.l)){
                return attTextpg;
            }
            else if ((lex->type==registre || lex->type==symb || lex->type==decimal || lex->type==hexa) && addRegister(lex,pcol->text.l)){
                /* if symb push into relocLIST */
                if(lex->type == symb){/* reloc type to be checked */
                    INSTR currInstr = dico[(pcol->text).l->instr];
                    switch(currInstr.type){/* TODO: verif LUI quand pseudo instruction*/
                        case 'I': /* r mips lo16 really ? : yes */
                            if(lex->trueType ==0){
                                *reloclist = addHeadR(*reloclist,(SECTION)text,(pcol->text).currOffset-4,(RELOCTYPE)mR_MIPS_LO16,seekSymb(/* (char*) */(lex->data),TAB),lex);
                            }
                            else{
                                *reloclist = addHeadR(*reloclist,(SECTION)text,(pcol->text).currOffset-4,(RELOCTYPE)mR_MIPS_HI16,seekSymb(/* (char*) */(lex->data),TAB),lex);
                            }
                        break;
                        case 'B':
                                *reloclist = addHeadR(*reloclist,(SECTION)text,(pcol->text).currOffset-4,(RELOCTYPE)mR_MIPS_LO16,seekSymb(/* (char*) */(lex->data),TAB),lex);
                                return attTextpg;/* because it is in the form XXX $x,label($x) so it needs to be redirected to attTextpg */
                        break;
                        case 'A': /* r mips 26 */
                            *reloclist = addHeadR(*reloclist,(SECTION)text,(pcol->text).currOffset-4,(RELOCTYPE)mR_MIPS_26,seekSymb(/* (char*) */(lex->data),TAB),lex);
                        break;
                    }
                }
                return attFinText;
            }
            else{
                printf("les opérandes ne sont pas ceux attendues ou ne sont pas séparés par des virgules\n");
                return error;
            }
        break;
        case attFinText:
            if (lex->type == retourLine) return INSTRUCTION;
            else if (lex->type == virgule) return attArgText;
            else if (lex->type == commentaire) return attFinText;
            else{
                printf("La syntaxe des opérandes n'est pas bonne\n");
                return error;
                }
        break;
        /* package */
        case attArgByte:
            if (lex->type == decimal || lex->type == hexa){
                if (erreurDirective(state, (char*)(lex->data))==0){
                    printf("L'opérande n'est pas un entier signé entre -128 et 127\n");
                    return(error);
                }
                char d = strtol(lex->data,NULL,0);
                if(*psec == data){
                    /* words begin w/ offset%4 == 0*/
                    if(packagePending(pendingEtiq,TAB,*psec,(pcol->data).currentOffset)==0){return error;}
                    addHeadG(&(pcol->data),(DATAG)d,charG,(pcol->data).currentOffset,lex->line);
                    (pcol->data).currentOffset += 1;
                }
                else {
                    printf("La directive .byte n'est gérée que par la section Data\n");
                    return error;
                    }
                return attFinByte;
            }
            else{
                printf("L'opérande de .byte doit être un nombre\n");
                return error;
                }
        break;
        case attFinByte:
            if (lex->type == retourLine) return BYTE;
            else if (lex->type == virgule) return attArgByte;
            else if (lex->type == commentaire) return attFinByte;
            else{
                printf("La syntaxe des opérandes n'est pas bonne\n");
                return error;
                }
        break;
        /* package */
        case attArgWord:
            if (lex->type == decimal || lex->type == hexa){
                if (erreurDirective(state, lex->data)==0){
                  printf("L'opérande n'est pas un entier signé entre -2 147 483 648 et 2 147 483 647\n");
                  return(error);
                }
                int d = strtol(lex->data,NULL,0);
                if(*psec == data){
                    /* words begin w/ offset%4 == 0*/
                    int modulo = (pcol->data).currentOffset%4;
                    (pcol->data).currentOffset += ((4-modulo)%4);/* magic formula */
                    if(packagePending(pendingEtiq,TAB,*psec,(pcol->data).currentOffset)==0){return error;}
                    addHeadG(&(pcol->data),(DATAG)d,intG,(pcol->data).currentOffset,lex->line);
                    (pcol->data).currentOffset += 4;
                }
                else {
                    printf("La directive .word n'est gérée que par la section Data\n");
                    return error;
                    }
                return attFinWord;
            }
            else if(lex->type == symb){
                /* if symb push into relocLIST */
                (pcol->data).currentOffset+= ((4-((pcol->data).currentOffset%4))%4);
                if(packagePending(pendingEtiq,TAB,*psec,(pcol->data).currentOffset)==0){return error;}
                *reloclist = addHeadR(*reloclist,(SECTION)data,(pcol->data).currentOffset,mR_MIPS_32,seekSymb(/* (char*) */(lex->data),TAB),lex);
                addHeadG(&(pcol->data),(DATAG)((char*)(lex->data)),etiqG,(pcol->data).currentOffset,lex->line);
                (pcol->data).currentOffset += 4;
            }
            else{
                printf("L'opérande de .word doit être un nombre ou une étiquette, ce n'est pas le cas ici\n");
                return error;
            }
        break;
        case attFinWord:
            if (lex->type == retourLine) return WORD;
            else if (lex->type == virgule) return attArgWord;
            else if (lex->type == commentaire) return attFinWord;
            else{
                printf("La syntaxe des opérandes n'est pas bonne\n");
                return error;}
        break;
        /* package */
        case attArgAsciiz:
            if(lex->type == string && *psec == data){
                    if(erreurDirective(state, lex->data)==0){
                        printf("Le char est trop grande pour être stockée\n");
                        return error;
                    }
                    if(packagePending(pendingEtiq,TAB,*psec,(pcol->data).currentOffset)==0) return error;
                    addHeadG(&(pcol->data),(DATAG)((char*)(lex->data)),symbG,(pcol->data).currentOffset,lex->line);
                    (pcol->data).currentOffset += strlen(lex->data)-1; /* le \0 est ajouté par addHeadG */
                    return attFinAsciiz;
            }
            else{
                printf("L'argument de Asciiz est mauvais\n");
                return error;
            }
        break;
        case attFinAsciiz:
            if (lex->type == retourLine) return ASCIIZ;
            else if (lex->type == virgule) return attArgAsciiz;
            else if (lex->type == commentaire) return attFinAsciiz;
            else{
                printf("La syntaxe des opérandes n'est pas bonne\n");
                return error;}
        break;
        /* package */
        case attArgSpace:
            if (lex->type == decimal /* || lex->type == hexa */){
                if (erreurDirective(state, lex->data)==0){
                    printf("L'opérande n'est pas un entier compris entre 0 et 32\n");
                    return(error);
                }
                unsigned int d = strtol(lex->data,NULL,0);
                if(*psec == data){
                    if(packagePending(pendingEtiq,TAB,*psec,(pcol->data).currentOffset)==0) return error;
                    addHeadG(&(pcol->data),(DATAG)d,uintG,(pcol->data).currentOffset,lex->line);
                    (pcol->data).currentOffset += d;
                }
                else if(*psec == bss){
                    packagePending(pendingEtiq,TAB,*psec,(pcol->bss).currentOffset);
                    addHeadG(&(pcol->bss),(DATAG)d,uintG,(pcol->bss).currentOffset,lex->line);
                    (pcol->bss).currentOffset += d;
                }
                else {
                    printf("La directive .space n'est gérée que par les section Data et BSS\n");
                    return error;
                    }
                return attFinSpace;
            }
            else{
                printf("L'opérande de .space doit être un nombre, ce n'est pas le cas ici\n");
                return error;}
        break;
        case attFinSpace:
            if (lex->type == retourLine) return SPACE;
            else if (lex->type == virgule) return attArgSpace;
            else if (lex->type == commentaire) return attFinSpace;
            else{
                printf("La syntaxe des opérandes n'est pas bonne\n");
                return error;}
        break;
        case error:
            printf(" Une erreur a été détectée en amont\n");
            return error;
        break;
    }
}

char isFinalG1(STATEG1 state){
	if (((int)state >= (int)TEXT)){
		return 1;
	}
	return 0;
}
