TARGET=builds/as-mips
DIRNAME=`basename $(PWD)`
CC=`which gcc`
LD=`which gcc`
RM=`which rm` -f
DOXYGEN=`which doxygen`

SRCDIR=src
INCDIR=include
TESTDIR=testing
DOCDIR=doc

STRASM=data/testG1data.s
STRDICO=data/simpledico.dico

#for unit testing these are the file that are to be compiled
CODETESTDIR=code_test
UT_LIST=$(SRCDIR)/list.c $(CODETESTDIR)/ut_list.c
UT_HACH=$(SRCDIR)/hach.c $(CODETESTDIR)/test1.c

GARBAGE=*~ $(SRCDIR)/*~ $(INCDIR)/*~ $(TESTDIR)/*~

INCLUDE=-I$(INCDIR)

# Pour activer les sorties INFO_MSG, ajouter -DVERBOSE aux CFLAGS 
CFLAGS=-Wall -ansi $(INCLUDE)
LFLAGS=-lm

CFLAGS_DBG=$(CFLAGS) -g -DDEBUG -Wall
CFLAGS_RLS=$(CFLAGS)

SRC=$(wildcard $(SRCDIR)/*.c)

OBJ_DBG=$(SRC:.c=.dbg)
OBJ_RLS=$(SRC:.c=.rls)

all : 
	@echo "in " $(DIRNAME)
	@echo ""
	@echo "Usage:"
	@echo ""
	@echo "make debug   => build DEBUG   version"
	@echo "make release => build RELEASE vgersion"
	@echo "make clean   => clean everything"
	@echo "make archive => produce an archive for the deliverable"

debug   : $(OBJ_DBG)
	$(LD) $^ $(LFLAGS) -o $(TARGET)

release : $(OBJ_RLS)
	$(LD) $^ $(LFLAGS) -o $(TARGET)

%.dbg : %.c
	$(CC) $< $(CFLAGS_DBG) -c -o $(basename $<).dbg

%.rls : %.c
	$(CC) $< $(CFLAGS_RLS) -c -o $(basename $<).rls

docu : 
	$(DOXYGEN)

clean : 
	$(RM) $(TARGET) $(SRCDIR)/*.orig $(SRCDIR)/*.dbg $(SRCDIR)/*.rls $(GARBAGE)
	$(RM) -r $(DOCDIR)/*
	$(RM) -r builds/*

archive : 
	make clean 
	cd .. && tar -czvf as-mips-`whoami`-`date +%d-%m-%H-%M`.tgz $(DIRNAME) && cd $(DIRNAME) 
testlist :
	$(LD) $^ $(UT_LIST) $(LFLAGS) $(CFLAGS_DBG) -o builds/ut_list.exe
testhach :
	$(LD) $^ $(UT_HACH) $(LFLAGS) $(CFLAGS_DBG) -o builds/ut_hach.exe
run :
	./$(TARGET)	$(STRASM) $(STRDICO)
 #| less
#$(filter-out $@,$(MAKECMDGOALS))
