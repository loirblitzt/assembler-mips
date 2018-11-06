
#include <stdlib.h>
#include <stdio.h>
#include "hach.h"



int main(){
  
  LISTH * TAB=calloc(N,sizeof(LISTH));

  /*addToTab("bonjour",2,6,L,TAB);*/
  int n=hachage("bonjour");
  int ni=hachage("bonj");
  addToTab("bonjour",2,1,TAB);
  addToTab("bonj",2,1,TAB);
  printf("%s",  TAB[n]->s);
  printf("%d",TAB[n]->section);
  printf("%s",  TAB[ni]->s);
  printf("%d",TAB[ni]->section);

  return 0;
}
