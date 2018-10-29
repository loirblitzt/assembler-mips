

/**
 * @file lex.c
 * @author François Portet <francois.portet@imag.fr>
 * @brief Lexical analysis routines for MIPS assembly syntax.
 *
 * These routines perform the analysis of the lexeme of an assembly source code file.
 */

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


/**
 * @param token The pointeur to the lexeme to be extracted.
 * @param current_line The address from which the analysis must be performed.
 * @return the address at which the analysis stopped or NULL if the analysis is terminated.  
 * @brief This function get an input line, extracts a token from it and return the pointeur to the next place where the analysis should continue. 
 */

/* note that MIPS assembly supports distinctions between lower and upper case*/ 
char* getNextToken(char** token, char* current_line,LIST* lex,int nline) {
    char* start = current_line; 
    char* end=NULL; 
    int token_size=0;
    STATE fsm = 0; /* zero value for the enum*/
    char ret = '\n\0';

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
    /*compute size : if zero there is no more token to extract*/ 	
    token_size=end-start;
    /*package the token*/
    if (token_size>0){
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




/**
 * @param line String of the line of source code to be analysed.
 * @param nline the line number in the source code.
 * @return should return the collection of lexemes that represent the input line of source code.
 * @brief This function performs lexical analysis of one standardized line.
 *
 */
void lex_read_line( char *line, int nline,LIST* lex) {
    char* token = NULL;
    char* current_address=line;
    while( (current_address= getNextToken(&token, current_address,lex,nline)) != NULL){ 
        puts(token);
    }
    return;
}

/**
 * @param file Assembly source code file name.
 * @param nlines Pointer to the number of lines in the file.
 * @return should return the collection of lexemes
 * @brief This function loads an assembly code from a file into memory.
 *
 */
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



