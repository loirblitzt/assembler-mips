/**
 * @file main.c
 * @author François Portet <francois.portet@imag.fr> from François Cayre
 * @brief Main entry point for MIPS assembler.
 */
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>


#include <global.h>
#include <notify.h>
#include <lex.h>
#include "list.h"
#include "gram1.h"
/**
 * @param exec Name of executable.
 * @return Nothing.
 * @brief Print usage.
 *
 */
void print_usage( char *exec ) {
    fprintf(stderr, "Usage: %s file.s\n",
            exec);
}



/**
 * @param argc Number of arguments on the command line.
 * @param argv Value of arguments on the command line.
 * @return Whether this was a success or not.
 * @brief Main entry point for MIPS assembler.
 *
 */
int main ( int argc, char *argv[] ) {

    unsigned int 	nlines 	= 0;
    char         	 *file 	= NULL;
    LIST lex = createList();
    COLG col;
    col.data=createDataCol();col.bss=createDataCol();col.text=createDataCol();
    col.data.sec=data;col.bss.sec=bss;col.text.sec=text;

    int sizeDico;
    INSTR * dico = loadDico("tests/simpledico.dico",&sizeDico);

    /* exemples d'utilisation des macros du fichier notify.h */
    /* WARNING_MSG : sera toujours affiche */
    WARNING_MSG("Un message WARNING_MSG !");

    /* macro INFO_MSG : uniquement si compilé avec -DVERBOSE. Cf. Makefile*/
    INFO_MSG("Un message INFO_MSG : Debut du programme %s", argv[0]);

    /* macro DEBUG_MSG : uniquement si compilé avec -DDEBUG (ie : compilation avec make debug). Cf. Makefile */
    DEBUG_MSG("Un message DEBUG_MSG !");

    /* La macro suivante provoquerait l'affichage du message
       puis la sortie du programme avec un code erreur non nul (EXIT_FAILURE) */
    /* ERROR_MSG("Erreur. Arret du programme"); */

/* 
    if ( argc <2 ) {
        print_usage(argv[0]);
        exit( EXIT_FAILURE );
    }
 */
    /* used to choose the file to be compiled */
    file  	= "tests/testG1data.txt";/* argv[argc-1] */;


    if ( NULL == file ) {
        fprintf( stderr, "Missing ASM source file, aborting.\n" );
        exit( EXIT_FAILURE );
    }



    /* ---------------- do the lexical analysis -------------------*/
    lex_load_file( file, &nlines, &lex );
    DEBUG_MSG("source code got %d lines",nlines);
    printAllData(lex);
    /*-------------------grammar 1 analysis------------------------*/
    G1LoadLex(lex,&col);
    printColG(col.data);
    printColG(col.bss);

    /* test pour le dico
    printf("sizedico : %d\n", sizeDico);
    printf("%d\n",searchDico("ADD",dico,sizeDico));
 */
    /* ---------------- Free memory and terminate------------------*/
    freeAllElements(lex);
    freeColG(col.data);freeColG(col.text);freeColG(col.bss);
    freeDico(dico,sizeDico);

    exit( EXIT_SUCCESS );
}

