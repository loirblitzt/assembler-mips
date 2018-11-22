/*

	symb.h

gere les ajout dans hach.h des etiquettes quand on sait pas encore quel est le decalage

garder en mémoire les etiquettes 
les envoyer dans la table de hachage
checker si une etiquette existe

*/
#ifndef _symb_
#define _symb_

#include "hach.h"

char addToPending(LISTH * l,char * name);

char packagePending(LISTH * pl,LISTH * TAB,SECTIONH sec, int deca);

#endif