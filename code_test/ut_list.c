/* test for the circular list */

#include <stdio.h>
/* #include "ut_list.h" */
#include "list.h"

char* message = "#hello world";
int a =10;
char semiColon = ';';
char* notTrueType = "- 1000";

void main(){
    /* \033[0m is reset and \033[32;1m is green */
    printf ("\033[33;1m Test of the list struct ! \033[0m\n");
    LIST lTest = createList();
    printf ("\033[33;1m adds one decimal to the list\033[0m\n");
    printf("size decimal : %d \n",sizeFromType(decimal,&a,1));
    lTest = addHead(lTest, &a , decimal,0,1);
    printAllTypes(lTest);

    printf ("\033[33;1m adds a char to the list\033[0m\n");
    printf("size char : %d \n",sizeFromType(deuxPoints,&semiColon,1));
    lTest = addHead(lTest, &semiColon , deuxPoints ,1,1);
    printAllTypes(lTest);

    printf ("\033[33;1m prints element -1's data\033[0m\n");
    printData(lTest);

    printf ("\033[33;1m prints all the data\033[0m\n");
    printAllData(lTest);

    printf ("\033[33;1maddtail test\033[0m\n");
    lTest = addTail(lTest,message,commentaire,-1,1);
    printAllData(lTest);

    printf ("\033[33;1mtrue type off test\033[0m\n");
    lTest = addTail(lTest,notTrueType,decimal,-1,0);
    printAllData(lTest);
    /* mandatory, release the DATA */
    freeAllElements(lTest);

    /*
        as expected the next line throw a core dumped error
    printAllData(lTest); 
    */
}