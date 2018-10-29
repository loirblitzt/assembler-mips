/**
 * @file lex.h
 * @author François Portet <francois.portet@imag.fr>
 * @brief Lexem-related stuff.
 *
 * Contains lexem types definitions, some low-level syntax error codes,
 * the lexem structure definition and the associated prototypes.
 */

#ifndef _LEX_H_
#define _LEX_H_


#include <stdio.h>
#include "fsm.h"
#include "list.h"

void	lex_read_line( char *, int,LIST*);
void	lex_load_file( char *, unsigned int *,LIST* );
char* 	getNextToken( char** , char* ,LIST*,int);

#endif /* _LEX_H_ */

