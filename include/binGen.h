/* misc functions to adapt previous code to lib elf */

#include "make_mips.h"
#include "gram1.h"

struct R{
    unsigned int function:6,
    sa:5,
    rd:5,
    rt:5,
    rs:5,
    optcode:6;
};

struct I{
    unsigned int imm:16,
    rt:5,
    rs:5,
    opcode:6;
};

struct J{
    unsigned int target:26,
    opcode:6;
};

union instrBin{
    struct R rInst;
    struct I iInst;
    struct J jInst;
    char code[4];
};

struct relSection{
    Elf32_Rel * text;
    Elf32_Rel * data;
    int sizeRelText,sizeRelData;
};

void swap(union instrBin * a);

int* makeBinText(COLG col,INSTR * dico ,int * size,int sizeDico,LISTH * TAB);

int* makeBinData(COLG col,LISTH * TAB,int * size);

unsigned int makeBinBss(COLG col);

char** makeCharSym(LIST * m_strTab,RELOCLIST relocL,int * size);

Elf32_Sym* makeStructSym(RELOCLIST relocL, LIST m_strTab,section strtab,
                        section shstrtab, int size,LISTH * TAB); 

struct relSection makeStructReloc(RELOCLIST relocL,section strtab,section shstrab,section symtab, LIST m_strTab); /* pareil renvoie taille du bordel / voir aussi pour faire que data et que bss */

void free_m_TAB(char** TAB,int size);