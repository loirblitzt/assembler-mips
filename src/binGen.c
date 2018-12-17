#include "binGen.h"

void swap(union instrBin * a){
    char* c=(char*)a;
    char tmp = c[0];
    c[0] = c[3];
    c[3] = tmp;
    tmp = c[2];
    c[2] = c[1];
    c[1] = tmp;
}

int* makeBinText(COLG col,INSTR * dico ,int * size,int sizeDico,LISTH * TAB){/* TODO: penser à swap */
    int i=0;
    int j;
    LISTH pSymb = NULL;
    *size = col.text.currOffset/4;
    union instrBin * tab = (union instrBin*)calloc(*size,sizeof(union instrBin));
    /* TODO: bussiness dico needed*/
    TEXTLIST l = col.text.l -> suiv;
    int myInstr;
    do{
        myInstr = l->instr;
        switch(dico[myInstr].type){
            case 'R':
                /* link data in the TEXTLIST struct to data in the R struct with respect to the dico */
                tab[i].rInst.optcode = dico[myInstr].opcode;
                tab[i].rInst.function = dico[myInstr].function;
                for(j=0;j<dico[myInstr].numOp;j++){
                    switch(dico[myInstr].opOrder[j]){
                        case 'd':
                            tab[i].rInst.rd = strtol((l->op[j])->data+1,NULL,10);
                        break;
                        case 's':
                            tab[i].rInst.rs = strtol((l->op[j])->data+1,NULL,10);
                        break;
                        case 't':
                            tab[i].rInst.rt = strtol((l->op[j])->data+1,NULL,10);
                        break;
                    }
                }
            break;
            case 'I':
                tab[i].iInst.opcode = dico[myInstr].opcode;
                for(j=0;j<dico[myInstr].numOp;j++){
                    switch(dico[myInstr].opOrder[j]){
                        case 's':
                            tab[i].iInst.rs = strtol((l->op[j])->data +1,NULL,10);
                        break;
                        case 't':
                            tab[i].iInst.rt = strtol((l->op[j])->data +1,NULL,10);
                        break;
                        case 'i':
                            if(l->op[j]->type != symb){
                                tab[i].iInst.imm = strtol((l->op[j])->data,NULL,0);
                            }
                            else{/* possible reloc */
                                pSymb = seekSymb(l->op[j]->data,TAB);
                                if(pSymb == NULL){
                                    tab[i].iInst.imm = 0;
                                }
                                else{
                                    if(l->op[j]->trueType == 0){
                                        tab[i].iInst.imm = 0xFF & (pSymb->decalage);
                                    }
                                    else{ /* upper relocation */
                                        tab[i].iInst.imm = (pSymb->decalage)>>16;
                                    }
                                }
                            }
                        break;
                    }
                }
            break;
            case 'S':
                tab[i].rInst.optcode = dico[myInstr].opcode;
                tab[i].rInst.function = dico[myInstr].function;
                for(j=0;j<dico[myInstr].numOp;j++){
                    switch(dico[myInstr].opOrder[j]){
                        case 'd':
                            tab[i].rInst.rd = strtol((l->op[j])->data+1,NULL,10);
                        break;
                        case 'a':
                            tab[i].rInst.sa = strtol((l->op[j])->data,NULL,0);
                        break;
                        case 't':
                            tab[i].rInst.rt = strtol((l->op[j])->data+1,NULL,10);
                        break;
                    }
                }
            break;
            case 'A':
                tab[i].jInst.opcode = dico[myInstr].opcode;
                tab[i].jInst.target = strtol((l->op[0])->data,NULL,0);
            break;
            case 'L':
                tab[i].iInst.opcode = dico[myInstr].opcode;
                for(j=0;j<dico[myInstr].numOp;j++){
                    switch(dico[myInstr].opOrder[j]){
                        case 's':
                            tab[i].iInst.rs = strtol((l->op[j])->data +1,NULL,10);
                        break;
                        case 't':
                            tab[i].iInst.rt = strtol((l->op[j])->data +1,NULL,10);
                        break;
                        case 'l':
                            tab[i].iInst.imm = strtol((l->op[j])->data,NULL,0);
                        break;
                    }
                }
            break;
            case 'B':
                tab[i].iInst.opcode = dico[myInstr].opcode;
                for(j=0;j<dico[myInstr].numOp;j++){
                    switch(dico[myInstr].opOrder[j]){
                        case 's':
                            tab[i].iInst.rs = strtol((l->op[j])->data +1,NULL,10);
                        break;
                        case 't':
                            tab[i].iInst.rt = strtol((l->op[j])->data +1,NULL,10);
                        break;
                        case 'o':
                            if(l->op[j]->type == symb){/* possible reloc (same as type I instructions)*/
                                pSymb = seekSymb(l->op[j]->data,TAB);
                                if(pSymb == NULL){
                                    tab[i].iInst.imm = 0;
                                }
                                else{
                                    if(l->op[j]->trueType == 0){
                                        tab[i].iInst.imm = 0xFF & (pSymb->decalage);
                                    }
                                    else{ /* upper relocation */
                                        tab[i].iInst.imm = (pSymb->decalage)>>16;
                                    }
                                }
                            }
                            else{
                                tab[i].iInst.imm = strtol((l->op[j])->data,NULL,0);
                            }
                        break;
                    }
                }
            break;
        }
        swap(&(tab[i]));
        l = l->suiv;
        i++;
    }while(l != (col.text.l ->suiv));
    
    return tab;    
}

/* beware the size is the number of bytes in DATA */
int* makeBinData(COLG col,LISTH * TAB,int * size){
    if(col.data.l ==NULL)return NULL;
    unsigned int i = 0;
    int c;
    LISTH pList =NULL;
    *size = col.data.currentOffset;/* *size = (col.data.currentOffset/4); */
    DATALIST l = col.data.l->suiv;
/*     if ((col.data.currentOffset%4)!=0){
        *size++;
    } */
    int* tab = (int*)calloc(*size,sizeof(char));
    char* cursor=(char*)tab;
    do{
        switch(l->type){
            case uintG:/* .space */
                i = l->offset;
                for(c=0;c < l->data.space;c++){
                    cursor[i+c] = (char)0;
                }
                i+=l->data.space;
            break;
            case charG:/* .byte */
                i = l->offset;
                cursor[i]=(char)(l->data.byte);
                i+=1;
            break;
            case intG:/* .word */   
                i = l->offset;
                tab[i/4] = l->data.word;
                swap(&(tab[i/4]));
                i+=4;
            break;
            case symbG:/* asciiz */
                i = l->offset;
                for(c=0;c<=strlen(l->data.asciiz);c++){
                    cursor[i+c]=(char)((l->data.asciiz)[c]);
                }
                i += strlen(l->data.asciiz)+1;
            break;
            case etiqG:/* .word with symb */
                i= l->offset;
                pList = seekSymb(l->data.asciiz,TAB);
                if(pList == NULL){
                    tab[i/4] = 0;
                }
                else{
                    tab[i/4] = pList->decalage;
                }
            break;
        }
        l=l->suiv;
    }while(l != col.data.l->suiv);
    return tab;
}

unsigned int makeBinBss(COLG col){
    DATALIST l = col.bss.l;
    unsigned int res = 0;
    if (l == NULL)return 0;
    DATALIST cursor = l->suiv;
    do{
        res += cursor->data.space;
        cursor = cursor->suiv;
    }while(cursor != l->suiv);
    return res;/* dont swap because 0 created by the little endian machine  */
}

int isInList(LIST l,char* name){
    if(l == NULL){
        return 0;
    }
    LIST cursor = l->suiv;
    do{
        if(strcmp(name,cursor->data) == 0){
            return 1;
        }
        cursor = cursor -> suiv;
    }while(cursor != l->suiv);
    return 0;
}

char** makeCharSym(LIST * m_strTab,RELOCLIST relocL,int * size){
    RELOCLIST cursor = NULL;
    if(relocL != NULL){
        /* if not declared, add at the end of the list */
        cursor = relocL->suiv;
        do{
            if(cursor->pHach == NULL && !(isInList(*m_strTab,cursor->lex->data))){/* TODO: does this checks for doublons */
                *m_strTab = addHead2(*m_strTab,cursor->lex->data,symb,0,strlen(cursor->lex->data)+1);
            }
            cursor = cursor -> suiv;
        }while(cursor != relocL->suiv);
    }
    /* now it is added, let's count the size of the needed array */
    if(*m_strTab==NULL)return NULL;
    LIST cursorL = (*m_strTab )->suiv;
    int sizeArray = 0;
    *size = 0;
    do{
        (*size)++;
        sizeArray += strlen(cursorL->data)+1;/* 1 for the \0 */
        cursorL = cursorL -> suiv;
    }while(cursorL != (*m_strTab )->suiv);
    
    /* let's create the array now and fill it*/
    /* we could have chrunk down the size by mixing the two for loops */
    int i = 0;
    char** TAB = (char**)calloc(*size,sizeof(char*));
    TAB[0] = (char*)calloc(sizeArray,sizeof(char));
    sizeArray = 0;
    cursorL = (*m_strTab)->suiv;
    do{
        TAB[i] = &(TAB[0][sizeArray]);
        strncpy(&(TAB[0][sizeArray]),cursorL->data,strlen(cursorL->data)+1);
        sizeArray += strlen(cursorL->data)+1;
        i++;
        cursorL = cursorL -> suiv;
    }while(cursorL != (*m_strTab)->suiv);

    return TAB;
}

uint16_t getSecIndex(SECTIONH a){
    uint16_t res = 0;
    switch(a){
        case textH:
        res = 1;
        break;
        case dataH:
        res = 3;
        break;
        case bssH:
        res = 5;
        break;
    }
    return res;
}
/* Elf32 same size than strtab */
Elf32_Sym* makeStructSym(RELOCLIST relocL, LIST m_strTab,section strtab,section shstrtab, int size,LISTH * TAB){
    Elf32_Sym* res = (Elf32_Sym*)calloc(size,sizeof(Elf32_Sym));
    /* char *  from tab of all the symb */
    LIST l =m_strTab->suiv;
    /* list of all the used symb (in .word or insturctions) */
    RELOCLIST lInOrder =NULL;
    /* points to the struct info of the symbol's info */
    LISTH curTab = NULL;
    int indice = 0;
    do{
        /* ajout dans l'odre de strtab */
        LISTH curTab = seekSymb(l->data,TAB);
        lInOrder = seekWithName(l->data,relocL);/* TODO: not really needed */
        /* symb  has been defined */
        if(curTab != NULL){
            res[indice].st_name = elf_get_string_offset(strtab->start,strtab->sz,l->data);
            res[indice].st_info = ELF32_ST_INFO(STB_LOCAL,STT_NOTYPE);
            res[indice].st_value = curTab->decalage;
            /* index in the symbtab of the section where the symb is declared */
            res[indice].st_shndx = getSecIndex(curTab->section);
            res[indice].st_size = 0;
            res[indice].st_other = 0;
        }
        /* symb as not been defined */
        else if(lInOrder != NULL){
            res[indice].st_name = elf_get_string_offset(strtab->start,strtab->sz,l->data);
            res[indice].st_info = ELF32_ST_INFO(STB_GLOBAL,STT_NOTYPE);/* pas forcement pour non def etiq */
            res[indice].st_value = 0;
            res[indice].st_shndx = 0;
            res[indice].st_size = 0;
            res[indice].st_other = 0;
        }
        else{
            printf("\033[31m:ERROR IN making the symbol struct:\033[0m\n");
        }
        indice ++ ;
        l = l->suiv;
    }while(l != m_strTab->suiv);
    return res;
}

int getSymNum(LIST l,char * name){
    int res = 5;
    return res;
}
struct relSection makeStructReloc(RELOCLIST relocL,section strtab,section shstrab,section symtab, LIST m_strTab){ 
    /* pareil renvoie taille du bordel / voir aussi pour faire que data et que bss */
    /* what is the size ? */
    /* initialuisation of the struct */
    struct relSection out ;
    out.text = NULL; out.data = NULL;
    out.sizeRelText = 0;out.sizeRelData = 0;

    if(relocL == NULL)return out;
    RELOCLIST l = relocL->suiv;
    
    /* mesure the size of the array */
    do{
        if(l->sec == data)out.sizeRelData++;
        else if(l->sec == text)out.sizeRelText++;
        l = l->suiv;
    }while(l != relocL->suiv);
    /* allocation */
    out.data = (Elf32_Rel*)calloc(out.sizeRelData,sizeof(Elf32_Rel));
    out.text = (Elf32_Rel*)calloc(out.sizeRelText,sizeof(Elf32_Rel));

    l = relocL->suiv;
    int indText = 0;
    int indData = 0;
    do{/* already ordered in respect to relativ adress*/
    /* can be cleaner */
        if(l->sec == data){
            out.data[indData].r_offset = l->offset;
            if(l->pHach == NULL){
                out.data[indData].r_info = ELF32_R_INFO(getSymNum(m_strTab,l->lex->data),l->relocType);
            }
            else{
                switch(l->pHach->section){
                    case text:
                        out.data[indData].r_info = ELF32_R_INFO(elf_get_sym_index_from_name(symtab,shstrab,strtab,".text"),l->relocType);
                    break;
                    case bss:
                        out.data[indData].r_info = ELF32_R_INFO(elf_get_sym_index_from_name(symtab,shstrab,strtab,".bss"),l->relocType);
                    break;
                    case data:
                        out.data[indData].r_info = ELF32_R_INFO(elf_get_sym_index_from_name(symtab,shstrab,strtab,".data"),l->relocType);
                    break;
                }
            }            
            indData++;
        }
        else if(l->sec == text){
            out.text[indText].r_offset = l->offset;
            /* TODO: Handle the case where pHach == NULL because of declaration */
            if(l->pHach ==NULL){
                out.text[indText].r_info = ELF32_R_INFO(elf_get_sym_index_from_name(symtab,shstrab,strtab,l->lex->data),l->relocType);/* ELF32_R_INFO(getSymNum(m_strTab,l->lex->data),l->relocType); */
            }
            else{
                switch(l->pHach->section){
                    case text:
                        out.text[indText].r_info = ELF32_R_INFO(elf_get_sym_index_from_name(symtab,shstrab,strtab,".text"),l->relocType);
                    break;
                    case bss:
                        out.text[indText].r_info = ELF32_R_INFO(elf_get_sym_index_from_name(symtab,shstrab,strtab,".bss"),l->relocType);
                    break;
                    case data:
                        out.text[indText].r_info = ELF32_R_INFO(elf_get_sym_index_from_name(symtab,shstrab,strtab,".data"),l->relocType);
                    break;
                }
            }
            indText++;
        }
        l = l->suiv;
    }while(l != relocL->suiv);
    return out;
}

void free_m_TAB(char** TAB,int size){
    free(TAB[0]);
    free(TAB);
}