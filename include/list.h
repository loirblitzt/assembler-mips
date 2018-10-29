/*list.h contains the methods used to managed general typed lists*/
/* this kind of custom list can be used to store LEX or other various variables type*/

#ifndef _LIST_H_
#define _LIST_H_

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

enum _type {
    commentaire,
    symb,
    hexa,
    decimal,
    string,
    virgule,
    retourLine,
    deuxPoints,
    point,
    etiquette,
    directive,
    parenthesed,
    parentheseg
};
typedef enum _type TYPE;

struct _list {
    void* data;
    TYPE type;                  /*define the legal types*/
    int line;
    char trueType;              /* determine if the data is stored into a char* or a int for instance for 8 */
    struct _list* suiv;
};
typedef struct _list* LIST;

LIST createList();

LIST addToList(LIST l, void* data, TYPE t, int line,char realType, char headTail);

LIST addHead(LIST l, void* data, TYPE t, int line, char realType);

LIST addTail(LIST l, void* data, TYPE t, int line,char realType);

LIST insertInList(LIST l, int i, void* data, TYPE t, int line,char realType);

LIST getElement(LIST l, int i);

size_t sizeFromType(TYPE t,void* data,char realType);

void printType(LIST l);

void printAllTypes(LIST l);

void printData(LIST l);

void printAllData(LIST l);

void freeElement(LIST l);

void freeAllElements(LIST l);

#endif