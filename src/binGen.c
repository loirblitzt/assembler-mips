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

int* makeBinText(COLG col,int * size){/* TODO: penser à swap */
    int i=0;
    *size = col.text.currOffset/4;
    int* tab = (int*)calloc(*size,sizeof(int));
    /* TODO: bussiness dico needed*/
    return tab;    
}

/* beware the size is the number of bytes in DATA */
int* makeBinData(COLG col,int * size){
    if(col.data.l ==NULL)return NULL;
    unsigned int i = 0;
    int c;
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
                swap((int)tab[i/4]);
                i+=4;
            break;
            case symbG:/* asciiz */
                i = l->offset;
                for(c=0;c<=strlen(l->data.asciiz);c++){
                    cursor[i+c]=(char)((l->data.asciiz)[c]);
                }
                i += strlen(l->data.asciiz)+1;
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

char** makeCharSym(LIST * m_strTab,RELOCLIST relocL,int * size){
    if(relocL == NULL)return NULL;
    
    /* if not declared, add at the end of the list */
    RELOCLIST cursor = relocL->suiv;
    do{
        if(cursor->pHach == NULL){
            *m_strTab = addHead2(*m_strTab,cursor->lex->data,symb,0,strlen(cursor->lex->data)+1);
        }
        cursor = cursor -> suiv;
    }while(cursor != relocL->suiv);
    
    /* now it is added, let's count the size of the needed array */
    if(*m_strTab==NULL)return NULL;
    LIST cursorL = (*m_strTab )->suiv;
    int sizeArray = 0;
    *size = 0;
    do{
        (*size)++;
        sizeArray += strlen(cursorL->data)+1;/* 1 for the \0 */
        cursor = cursor -> suiv;
    }while(cursor != relocL->suiv);
    
    /* let's create the array now and fill it*/
    /* we could have chrunk down the size by mixing the for loops */
    int i = 0;
    char** TAB = (char**)calloc(sizeArray,sizeof(char*));
    sizeArray = 0;
    cursorL = (*m_strTab)->suiv;
    do{
        strncpy(TAB[sizeArray],cursorL->data,strlen(cursorL->data)+1);
        sizeArray += strlen(cursorL->data)+1;
        cursorL = cursorL -> suiv;
    }while(cursor != relocL->suiv);

    return TAB;
}

/* Elf32 same size than strtab */
Elf32_Sym* makeStructSym(RELOCLIST relocL, LIST m_strTab,section strtab,section shstrtab, int size){
    Elf32_Sym* res = (Elf32_Sym*)calloc(size,sizeof(Elf32_Sym));
    LIST l =m_strTab->suiv;
    int indice = 0;
    RELOCLIST lInOrder =NULL;
    do{
        lInOrder = seekWithName(l->data,relocL);
        res[indice].st_name = elf_get_string_offset(strtab->start,strtab->sz,l->data);
        res[indice].st_size = 0;
        res[indice].st_value = lInOrder->offset;
        res[indice].st_info = ELF32_ST_INFO(STB_LOCAL,STT_NOTYPE);
        res[indice].st_other = 0;
        res[indice].st_shndx = elf_get_string_index(shstrtab->start,strtab->sz,l->data);
        indice ++ ;
        l = l->suiv;
    }while(l != m_strTab->suiv);
    return res;
}

struct relSection makeStructReloc(RELOCLIST relocL,section strtab,section shstrab,section symtab){ 
    /* pareil renvoie taille du bordel / voir aussi pour faire que data et que bss */
    /* what is the size ? */
    struct relSection out ;
    out.text = NULL; out.data = NULL;
    out.sizeRelText = 0;out.sizeRelData = 0;
    RELOCLIST l = relocL->suiv;
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
    do{/* already ordered */
    /* can be cleaner */
        if(l->sec == data){
            out.data[indData].r_offset = l->offset;
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
            indData++;
        }
        else if(l->sec == text){
            out.text[indText].r_offset = l->offset;
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
            indText++;
        }
        l = l->suiv;
    }while(l != relocL->suiv);
    return out;
}