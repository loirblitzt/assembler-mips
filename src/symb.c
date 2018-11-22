#include "symb.h"

char addToPending(LISTH * pl,char * name){
    if(seekSymbInList(name,*pl)==NULL){
        *pl = addToHead(name,nullH,-1,*pl);
        return 1;
    }
    return 0;
}

char packagePending(LISTH * pl,LISTH * TAB,SECTIONH sec,int offset){
    LISTH cursor = *pl;
    while(cursor != NULL){
        if(addToTab(cursor->s,sec,offset,TAB)==0) return 0;
        cursor = cursor->next;
    }
    libereListH(*pl);
    *pl =NULL;/* safe ? my answer : yes bc *pl as not been malloced*/
}