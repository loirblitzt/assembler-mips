/* manage the dico for the instructions */

#include "dicoG1.h"

/* NOTE works !!! */
INSTR* loadDico(char * nameFile,int * pnbEl){
    FILE* f = fopen(nameFile,"r");
    char tmpC[512];
    if (f == NULL) return NULL;
    if (fscanf(f,"%d",pnbEl) !=1) return NULL;
    INSTR * tab = (INSTR*)calloc(*pnbEl,sizeof(INSTR));

    char opCharCode[7];
    char opCharFunc[7];
    int i;
    int j;
    for (i=*pnbEl-1;i>=0;i--){
        if(fscanf(f,"%s %c %d",tmpC,&(tab[i].type),&(tab[i].numOp))!=3){
            free(tab);
            return NULL;
        }
        tab[i].name = (char*)strdup(tmpC);
        for (j=0;j<tab[i].numOp;j++){
            fscanf(f," %c ",&(tab[i].opDef[j]));
        }
        for (j=0;j<tab[i].numOp;j++){
            fscanf(f," %c ",&(tab[i].opOrder[j]));
        }
        fscanf(f,"%s , %s",opCharCode,opCharFunc);
        opCharCode[6] = '\0';
        opCharFunc[6] = '\0';
        tab[i].opcode = strtol(opCharCode,NULL,2);
        tab[i].function = strtol(opCharFunc,NULL,2);
    }
    fclose(f);
    return tab;
}

/* return the indice , -1 overwise */
int searchDico(char* inst,INSTR * dico,int size){
    int i = -1;
    char isNotFound=1;
    while(i<size-1 && isNotFound){
        i++;
        isNotFound = strcasecmp(inst,dico[i].name);
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