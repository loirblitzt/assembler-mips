/* manage the dico for the instructions */

#include "dicoG1.h"

INSTR* loadDico(char * nameFile,int * pnbEl){
    FILE* f = fopen(nameFile,"r");
    char tmpC[512];
    if (f == NULL) return NULL;
    if (fscanf(f,"%d",pnbEl) !=1) return NULL;
    INSTR * tab = (INSTR*)calloc(*pnbEl,sizeof(INSTR));
    int i;
    for (i=*pnbEl-1;i>=0;i--){
        if(fscanf(f,"%s %c %c",tmpC,&(tab[i].type),&(tab[i].numOp))!=3){
            free(tab);
            return NULL;
        }
        tab[i].name = (char*)strdup(tmpC);
    }
    fclose(f);
    return tab;
}

/* return the indice , -1 overwise */
int searchDico(char* inst,INSTR * dico,int size){
    int i = -1;
    char isNotFound=1;
    while(i<size-1 || isNotFound){
        i++;
        isNotFound = strcmp(inst,dico[i].name);
    }
    if (!isNotFound)return i;
    else {return -1;}
}

void freeDico(INSTR * dico,int size){
    int i;
    for (i=0; i<size ; i++){
        free(dico[i].name);
    }
    free (dico);
}