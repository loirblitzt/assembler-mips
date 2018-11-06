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
  *L=*new;
  return(L);
  }

}



void addToTab(char *c, SECTIONH sec, int deca, LISTH * TAB){
  int n=hachage(c);
  TAB[n]=addToHead(c,sec,deca,TAB[n]);
}

/*void suppTab(LISTH l,LISTH L){
  if (l->next==NULL){
    free(l);
  }
  else {
    int n=hachage(l->s);
    *(L+n)=*(l->next);
    free(l);
  }
}*/


LISTH seekSymb(char *symbole, LISTH *TAB){
  int n=hachage(symbole);
  if(TAB[n]->next==NULL){
    return(TAB[n]);
  }
  else {
    LISTH a=TAB[n]->next;
    while (strcmp(a->s , symbole)){
      a=a->next;
    }
    return(a);
  }
}
