/*  gram1.h  */

/*interpreter la liste de lexeme
_lire un à un les lexemes
_envoyer dans la machine à etat
_sortir ce quil faut mettre dans une collection
-renvoyer le resultat du livrable 2
*/
#include "list.h"
#include "fsmG1.h"
#include "secData.h"
/*appelle la fsmG1 toussa*/
LIST getNextTokenG1(LIST lex,LIST curLex,SECTION* sec);

/*appelle getNextTokenG1*/
void G1LoadLex(LIST lex);
