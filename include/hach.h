/*
hach.h

ici tu colles ton code qui gere lutilisation dune table de hachage -- tree.h

creation
ajout element
suppresion

*/
#ifndef _hach_
#define _hach_
#include <stdlib.h>
#include <stdio.h>


#define N 100


int hachage(char *s);

enum _sectionH{
  nullH,
  textH,
  dataH,
  bssH
} ; typedef enum _sectionH SECTIONH;

struct _listh {
    char *s;
    SECTIONH section;
    int decalage;
    struct listh* next;
};
typedef struct _listh* LISTH;

LISTH seekSymbInList(char *symbole, LISTH TAB);
LISTH addToHead(char *new_s, SECTIONH new_section, int decalage, LISTH L);

char addToTab(char *c, SECTIONH sec, int deca, LISTH * TAB);
LISTH seekSymb(char * symb,LISTH * TAB);
void printL(LISTH l);
void printTab(LISTH * TAB);
void libereListH(LISTH l);
void suppTab(LISTH * tab,int taille);
#endif