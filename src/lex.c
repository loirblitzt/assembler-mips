#define _POSIX_C_SOURCE 200112L
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <strings.h>

#include <global.h>
#include <notify.h>
#include <lex.h>
#include "fsm.h"
#include "list.h"

void translateReg(char* c , int * modSize){
    if(!isdigit(c[1])){
        if(strncmp(c,"$zero",5)==0){
            *modSize = 3;
            c[1]='0';
        }
        else if(strncmp(c,"$at",3)==0){
            *modSize = 1;
            c[1]='1';
        }
        else if(strncmp(c,"$gp",3)==0){
            *modSize = 0;
            c[1]='2';
            c[2]='8';
        }
        else if(strncmp(c,"$sp",3)==0){
            *modSize = 0;
            c[1]='2';
            c[2]='9';
        }
        else if(strncmp(c,"$fp",3)==0){
            *modSize = 0;
            c[1]='3';
            c[2]='0';
        }
        else if(strncmp(c,"$ra",3)==0){
            *modSize = 0;
            c[1]='3';
            c[2]='1';
        }
        else if(c[1]=='v'){
            *modSize = 1;
            switch(c[2]){
                case '0':
                c[1]='2';
                break;
                case '1':
                c[1]='3';
                break;
            }
        }
        else if(c[1]=='a'){
            *modSize=1;
            if(c[2]>='0' && c[2]<='3'){
                c[1]=c[2]+4;
            }
        }
        else if(c[1]=='t'){
            if(c[2]>='0' && c[2]<='1'){
                *modSize=1;
                c[1]=c[2]+8;
            }
            else if (c[2]>='2' && c[2]<='7'){
                c[1] = '1';
                *modSize = 0;
                c[2] = c[2] - 2;
            }
            else if (c[2]=='8'){
                *modSize = 0;
                c[1] = '2';
                c[2] = '4';
            }
            else if(c[2]=='9'){
                *modSize = 0;
                c[1] = '2';
                c[2] = '5';
            }
        }
        else if(c[1]=='s'){
            if(c[2]>='0'&&c[2]<='3'){
                *modSize=0;
                c[2]='1';
                c[2] = c[2]+6;
            }
            else if (c[2]>='4'&&c[2]<='7'){
                c[1] = '2';
                *modSize = 0;
                c[2] = c[2] -4;
            }
        }
        else if(c[1] == 'k'){
            if(c[2]=='0'){
                c[1] = '2';
                c[2] = '6';
            }
            else if(c[2]=='1'){
                c[1] = '2';
                c[2] = '7';
            }
        }
        else{
            exit(EXIT_FAILURE);
        }
    }
    else{
        *modSize =0;
    }
}

/* MIPS assembly supports distinctions between lower and upper case*/ 
char* getNextToken(char** token, char* current_line,LIST* lex,int nline) {
    char* start = current_line; 
    char* end=NULL; 
    int token_size=0;
    STATE fsm = 0; /* zero value for the enum*/
    char ret = '\n\0';
    int modSize = 0;
    /* check input parameter*/ 
    if (current_line ==NULL) return NULL;

    /* eats any blanks before the token*/
    while (condStart(*start,&fsm)){ 
	start++;
    }	
    /* go till next blank or end*/ 
    end=start; 

    while (condEnd(*end,&fsm)){
	end++; 
    }
    if (needMoreChar(fsm,start,end)) end++;
    if(fsm == REGISTRE)translateReg(start,&modSize);
    /*compute size : if zero there is no more token to extract*/ 	
    token_size=end-start-modSize;
    /*package the token*/
    if (token_size>0){
    free(*token);
	*token 	= calloc(token_size+1,sizeof(*start));
	strncpy(*token,start,token_size);
	(*token)[token_size]='\0';
    *lex = addHead(*lex, *token, (TYPE)(fsm - COM),nline,0);
    return end;
    }
    /* if the token's size is 0 this means it is the end of the line
    and therefore it ought add retourLine to the list */ 
    *lex = addHead(*lex, &ret, retourLine,nline,0);
    return NULL;
}


void lex_read_line( char *line, int nline,LIST* lex) {
    char* token = NULL;
    char* current_address=line;
    while( (current_address= getNextToken(&token, current_address,lex,nline)) != NULL){ 
       /*  puts(token); */
    }
    free(token);
    return;
}

void lex_load_file( char *file, unsigned int *nlines,LIST* lex ) {

    FILE        *fp   = NULL;
    char         line[STRLEN]; /* original source line */



    fp = fopen( file, "r" );
    if ( NULL == fp ) {
        /*macro ERROR_MSG : message d'erreur puis fin de programme ! */
        ERROR_MSG("Error while trying to open %s file --- Aborts",file);
    }

    *nlines = 0;

    while(!feof(fp)) {

        /*read source code line-by-line, STRLEN is the maximum size a line can be*/
        if ( NULL != fgets( line, STRLEN-1, fp ) ) {
            
            if (line[strlen(line)-1] == '\n'){ /* not every line finishies with '\n' */
                line[strlen(line)-1] = '\0';  /* eat final '\n' */
            }
            (*nlines)++; /* increment the line number returned by pointer */

            if ( 0 != strlen(line) ) {
                lex_read_line(line,*nlines,lex);
            }
        }
    }

    fclose(fp);
    return;
}



