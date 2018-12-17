#include "elfInter.h"

int fakeMain(COLG col,RELOCLIST relocL,LIST m_strTab,char* nameOut,LISTH * TAB ,INSTR * dico ,int sizeDico){
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
    /* sizeText = 3; int text_prog[]= {0x20106400,0x04006220,0xFEFF4310}; */
    int * text_prog;    text_prog = makeBinText(col,dico,&sizeText,sizeDico,TAB);
    int * data_prog;    data_prog =  makeBinData(col,TAB,&sizeData);
    int bss_prog ;      bss_prog = (int)makeBinBss(col);
    char ** sym_char;   sym_char =  makeCharSym(&m_strTab,relocL,&sizeChar);
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
    syms = makeStructSym(relocL,m_strTab,strtab,shstrtab,sizeChar,TAB);
    symtab   = make_symtab_section( shstrtab, strtab, syms,sizeChar);


    struct relSection relColection;
    relColection = makeStructReloc(relocL,strtab,shstrtab,symtab,m_strTab);
    reltext  = make_rel32_section( ".rel.text", relColection.text,relColection.sizeRelText);
    reldata  = make_rel32_section( ".rel.data", relColection.data,relColection.sizeRelData);


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
    print_section( reltext);
    print_section( reldata);

    /*clean up */
    free(text_prog);
    free(data_prog);
    /* free(sym_char); *//* check valgrind for that */
    free(syms);
    free(relColection.data);
    free(relColection.text);

    free_m_TAB(sym_char,sizeChar);

    if(text !=NULL){del_section(     text );}
    if(data !=NULL){del_section(     data );}
    if(bss != NULL){ del_section(      bss );}
    del_section( shstrtab );
    del_section(   strtab );
    del_section(   symtab );
    del_section(  reltext );
    del_section(  reldata );

    return 0;

}
