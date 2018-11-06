/*
hach.h

ici tu colles ton code qui gere lutilisation dune table de hachage -- tree.h

creation
ajout element
suppresion

*/
#include <stdlib.h>
#include <stdio.h>

#define N 1000


int hachage(char *s);

enum _section{
  textH,
  dataH,
  bssH
} ; typedef enum _section SECTIONH;

struct _listh {
    char *s;
    SECTIONH section;
    int decalage;
    struct listh* next;
};
typedef struct _listh* LISTH;

LISTH addToHead(char *new_s, SECTIONH new_section, int decalage, LISTH L);

void addToTab(char *c, SECTIONH sec, int deca, LISTH * TAB);
LISTH seekSymb(char *symbole, LISTH *TAB);

void suppTab(LISTH l, LISTH L);
