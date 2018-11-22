#include "hach.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>



/* LISTH TAB[N]=calloc(N,sizeof(LISTH));*/

/* LISTH L[N]=calloc(N,sizeof(LISTH));*/
/*LISTH allocation pointeur */

int hachage(char *s){
  int sum=0;
  int i=0;
  for (i=0;i<strlen(s);i++){
    sum+=s[i];
  }
  return sum%N;
}

/*strcpy pour allouer*/

LISTH addToHead(char *source, SECTIONH new_section, int decal, LISTH L){
  char *new_s=calloc(strlen(source),sizeof(char));
  strcpy(new_s,source);
  int n=hachage(new_s);

  if (L==NULL) {
    LISTH new=malloc(sizeof(struct _listh));
    new->s=new_s;
    new->section=new_section;
    new->decalage=decal;
    new->next=NULL;
    return(new);
  }
  else {
  LISTH new=malloc(sizeof(struct _listh));
  new->s=new_s;
  new->section=new_section;
  new->decalage=decal;
  new->next=(L);
  /* *L=*new; */
  return(new); /* regarde l'erreur ici lucien ;) */
  }

}



char addToTab(char *c, SECTIONH sec, int deca, LISTH * TAB){
  int n=hachage(c);
  LISTH l = seekSymbInList(c,TAB[n]);
  if(l==NULL){
    TAB[n]=addToHead(c,sec,deca,TAB[n]);
  }
  else if (l->section==nullH){
    l->decalage=deca;
    l->section = sec;
  }
  else{
    return 0;
  }
  return 1;
}

void libereListH(LISTH l){
    if(l != NULL){
        libereListH(l->next);
        free(l->s);
        free(l);
    }
}

void suppTab(LISTH * tab,int taille){
    int i;
    for(i=0;i<taille;i++){
        libereListH(tab[i]);
    }
    free(tab);
}

/* return NULL if not found */
LISTH seekSymbInList(char *symbole, LISTH TAB){
  LISTH a=TAB;
  while (a!=NULL && strcmp(a->s , symbole)!=0){
    a=a->next;
  }
  return(a);
}
LISTH seekSymb(char * symb,LISTH * TAB){
  return seekSymbInList(symb,TAB[hachage(symb)]);
}

char* mesgH[]={
  "nullH",
  "textH",
  "dataH",
  "bssH"
};
void printL(LISTH l){
  LISTH p = l;
  while(p!=NULL){
    printf("\033[31m-_-_-__-_-_-_-__-_-\033[0m\n");
    printf("name : %s\n",p->s);
    printf("section : %s\n",mesgH[l->section]);
    printf("offset : %d\n",p->decalage);
    printf("\033[31m-_-_-__-_-_-_-__-_-\033[0m\n");
    p=p->next;
  }
}
void printTab(LISTH * TAB){
  printf("\033[32m_--------------------\033[0m\n");
  printf("affichage des etiquettes déclarés stockées\n");
  int i;
  for (i=0;i<N;i++){
    printL(TAB[i]);
  }
  printf("\033[32m_--------------------\033[0m\n");
}