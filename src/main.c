#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>


#include <global.h>
#include <notify.h>
#include <lex.h>
#include "list.h"
#include "gram1.h"
#include "elfInter.h"
/**
 * @param exec Name of executable.
 * @return Nothing.
 * @brief Print usage.
 *
 */
void print_usage( char *exec ) {
    fprintf(stderr, "Usage: %s file.s dico.dico\n",
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
    char *           namedico = NULL;
    char *          outputFileName = NULL;
    int sizeDico;
    LIST m_strTab = createList();
    LIST lex = createList();
    COLG col;
    col.data=createDataCol();col.bss=createDataCol();col.text=createTextCol();
    col.data.sec=data;col.bss.sec=bss;

    LISTH * TAB=calloc(N,sizeof(LISTH));

    RELOCLIST reloclist = NULL;

    INSTR * dico;

    /* --------------setting up the arguments------------------------- */

    if ( argc <2 ) {/* default mode */
        print_usage(argv[0]);
            file  	= strdup("data/testG1data.s");/* argv[argc-2]; */
            dico = loadDico("data/simpledico.dico",&sizeDico);
    }
    else if(argc < 3){
        /* used to choose the file to be compiled */
        file  	= argv[argc-1];
        /* use default dico */
        dico = loadDico("data/simpledico.dico",&sizeDico);
    }
    else{
        file  	= argv[argc-2];
        namedico = argv[argc-1];
        dico = loadDico(namedico,&sizeDico);
    }

    /* -----------------reading the dico -----------------------------*/
    if(dico == NULL){
        printf("Not able to read dico \n");
        exit( EXIT_FAILURE);
    }
    if ( NULL == file/*  || NULL == dico */) {
        fprintf( stderr, "Missing ASM source file, aborting.\n" );
        exit( EXIT_FAILURE );
    }

    /* ---------------- do the lexical analysis -------------------*/

    lex_load_file( file, &nlines, &lex );
    DEBUG_MSG("source code got %d lines",nlines);
    printAllData(lex);

    /*-------------------grammar 1 & 2 analysis------------------------*/
    int flag = 0;
    G1LoadLex(lex,&col,dico,sizeDico,TAB,&reloclist,&m_strTab,&flag);
    if(flag==1)exit(EXIT_FAILURE);
    updateReloc(reloclist, TAB);

    printColG(col.data);
    printColG(col.bss);
    printColT(col.text,dico);
    printTab(TAB);
    printAllElR(reloclist);

    /* generation of the binaries */

    outputFileName = file;
    outputFileName[strlen(outputFileName)-1] = 'o';
    fakeMain(col,reloclist,m_strTab,outputFileName,TAB, dico , sizeDico);

    /* ---------------- Free memory and terminate------------------*/

    if(lex!=NULL)freeAllElements(lex);
    if(m_strTab!=NULL)freeAllElements(m_strTab);
    freeColG(col.data);freeColT(col.text);freeColG(col.bss);
    freeDico(dico,sizeDico);
    suppTab(TAB,N);
    freeListR(reloclist);
    if ( argc <2 ) {
        free(file);
    }
    /* !!! hey !!! */

    exit( EXIT_SUCCESS );
}






    /*
    WARNING_MSG("Un message WARNING_MSG !");
    INFO_MSG("Un message INFO_MSG : Debut du programme %s", argv[0]);

    DEBUG_MSG("Un message DEBUG_MSG !"); */
