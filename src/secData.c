#include "secData.h"

DATACOL createDataCol(){
    DATACOL col = {NULL,none,0}; /* 0 == NULL type for datalist */
    return col ;
}

void cleanString(char* s,int size){
    char * start, *end;
    start = s;
    end = start;
    int i = 0;
    while(i<size){
        if(*end!='\\'){
            *start=*end;
            start +=1;
            end +=1;
            i++;
        }
        else{
            end +=1;
            i++;
            if(i<size){
                switch (*end){
                    case 't':
                        *start = '\t';
                    break;
                    case 'n':
                        *start = '\n';
                    break;
                    case '\\':
                        *start = '\\';
                    break;
                    case '\"':
                        *start = '\"';
                    break;
                    /* others??? */
                }
                start +=1;
                end +=1;
                i++;
            }
        }
    }
    start +=1;
    *start = '\0';
}

/*ajout*/
void addHeadG(DATACOL * col, DATAG data, TYPEG1 type, int offset, int nbline){
    DATALIST tmpl = (DATALIST)malloc(sizeof(*tmpl));

    tmpl->type= type; tmpl->offset = offset; tmpl->nbLine = nbline;tmpl->isLabel = 0;
    if (type == symbG ){
        /* hazardous work ahead : get rid of the " " at the end and beginning */
        cleanString(data.asciiz+1,strlen(data.asciiz)-2);
        (tmpl->data).asciiz = (char*)calloc(strlen(data.asciiz),sizeof(char));
        (tmpl->data).asciiz =strncpy((tmpl->data).asciiz,data.asciiz+1,strlen(data.asciiz)-2);
        /* thank you valgrind */
        /* (tmpl->data).asciiz[strlen(data.asciiz)-1] = '\0' ; */
    }
    else if(type == etiqG){
        /* this is a .word with an label in argument */
        (tmpl->data).asciiz = (char*)calloc(strlen(data.asciiz)+1,sizeof(char));
        (tmpl->data).asciiz = strcpy((tmpl->data).asciiz,data.asciiz);
    }
    else{
        tmpl->data = data; /* halla waka bah */
    }

    if(col->l == NULL){
        tmpl->suiv = tmpl;
    }
    else{
        tmpl->suiv = (col->l)->suiv;
        (col->l)->suiv = tmpl;
    }
    col->l = tmpl;/* return the head "the last in"  */
}

/* affichage */
void printElementG(DATALIST l){
    printf("---------------\n");
    switch(l->type){
        case intG:
            printf("type : int\ndata : %d\n",(l->data).word);
        break;
        case uintG:
            printf("type : uint\ndata : %d\n",(l->data).space);
        break;
        case charG:
            printf("type : char\ndata : %d\n",(l->data).byte);
        break;
        case symbG:
            printf("type : string\ndata : %s\n",(l->data).asciiz);
        break;
    }
    printf("offset : %d\nnbLine : %d\n",l->offset,l->nbLine);
    printf("---------------\n");
}
char* printsec[]={"none",
                "text",
                "data",
                "bss"};
void printSection(SECTION sec){
    printf("Collection de la section : %s\n",printsec[(int)sec]);
}

void printColG(DATACOL col){
    printSection(col.sec);
    if(col.l!=NULL){
    DATALIST l =(col.l)->suiv;
    do{
        printElementG(l);
        l = l->suiv;
    }while(l!=((col.l)->suiv)  );}
    else{
        printf("collection vide\n");
    }
}
/*suppression*/

void freeElementG(DATALIST l){
    if (l->type == symbG || l->type == etiqG){
        free((l->data).asciiz);
    }
    free(l);
}

void freeColG(DATACOL col){
    if(col.l!=NULL){
        DATALIST c = (col.l)->suiv;
        col.l->suiv = NULL;
        while(c!=NULL){
            DATALIST tmp = c->suiv;
            freeElementG(c);
            c=tmp;
        }
    }
}