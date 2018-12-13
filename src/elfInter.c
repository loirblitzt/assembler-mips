#include "elfInter.h"

int fakeMain(COLG col,RELOCLIST relocL,LIST m_strTab){

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
    char* machine = "mips";/* TODO:les faire passer par argument */
    char* name = "exemple.o";
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


    Elf32_Rel text_reloc[1];
    text_reloc[0].r_offset =4;
    text_reloc[0].r_info=ELF32_R_INFO(elf_get_sym_index_from_name(symtab, shstrtab, strtab,".text"),R_MIPS_LO16);
    Elf32_Rel data_reloc[1];
    data_reloc[0].r_offset =0;
    data_reloc[0].r_info=ELF32_R_INFO(elf_get_sym_index_from_name(symtab, shstrtab,strtab,".bss"),R_MIPS_32);


    reltext  = make_rel32_section( ".rel.text", text_reloc,1);
    reldata  = make_rel32_section( ".rel.data", data_reloc,1);


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