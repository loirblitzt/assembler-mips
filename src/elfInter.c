#include "elfInter.h"

int fakeMain(COLG col,RELOCLIST relocL,LIST m_strTab,char* nameOut){

    /* prepare sections*/
    section     text = NULL;
    section     data = NULL;
    section      bss = NULL;
    section shstrtab = NULL;
    section   strtab = NULL;
    section   symtab = NULL;
    section  reltext = NULL;
    section  reldata = NULL;

    /* make predefined section table*/
    shstrtab = make_shstrtab_section();

    /* make hard coded program data already in big endian */
    int sizeData,sizeText,sizeChar;
    int * text_prog;    text_prog = makeBinText(col,&sizeText);
    int * data_prog;    data_prog =  makeBinData(col,&sizeData);
    int bss_prog ;      bss_prog = (int)makeBinBss(col);
    char ** sym_char;   sym_char =  makeCharSym(m_strTab,relocL,&sizeChar);
    char* machine = "mips";
    char* name = nameOut;
    /* pelf options */
    int noreorder =1;


    /* Create text, data and bss sections*/
    text     = make_text_section(text_prog, sizeText);

    if ( !text ) {
        fprintf( stderr, "Unable to write .text section (missing information).\n" );
        return -1;
    }

    /* modified : sizeData is the number of bytes in DATA, allows that size%4!=0 */
    data = make_data_section(  data_prog, sizeData);
    if ( !data ) {
        fprintf( stderr, "Unable to write .data section (missing information).\n" );
        return -1;
    }

    bss = make_bss_section(  bss_prog);
    if ( !bss ) {
        fprintf( stderr, "Unable to write .bss section (missing information).\n" );
        return -1;
    }

    /* Write all string linked to symbols*/
    strtab   = make_strtab_section( sym_char, sizeChar);

    Elf32_Sym * syms;
    syms = makeStructSym(relocL,m_strTab,strtab,shstrtab,sizeChar);
    symtab   = make_symtab_section( shstrtab, strtab, syms,2);


    struct relSection relColection;
    relColection = makeStructReloc(relocL,strtab,shstrtab,sym_char);
    reltext  = make_rel32_section( ".rel.text", relColection.sizeRelText,relColection.text);
    reldata  = make_rel32_section( ".rel.data", relColection.sizeRelData,relColection.data);


    /*write these sections in file*/
    elf_write_relocatable( name, machine, noreorder,
                           text->start, text->sz,
                           data->start, data->sz,
                           bss->start, bss->sz,
                           shstrtab->start, shstrtab->sz,
                           strtab->start, strtab->sz,
                           symtab->start, symtab->sz,
                           reltext->start, reltext->sz,
                           reldata->start, reldata->sz);


    print_section( text );
    print_section( data );
    print_section( bss );
    print_section( strtab );
    print_section( symtab );


    /*clean up */
    free(text_prog);
    free(data_prog);
    free(bss_prog);
    free(sym_char);/* check valgrind for that */
    free(syms);
    free(relColection.data);
    free(relColection.text);

    del_section(     text );
    del_section(     data );
    del_section(      bss );
    del_section( shstrtab );
    del_section(   strtab );
    del_section(   symtab );
    del_section(  reltext );
    del_section(  reldata );

    return 0;

}