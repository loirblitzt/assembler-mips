/*
	fsmG1.h
	
interpreter les lexemes (les rassembler en structure logique) determiner dans quoi les mettres

!!!pas les noms definitifs il fauit les changer!!! peut evoluer !!!
conddebutg1
condEndG1
updatefsmG1state

gere .bss .data .text en me temps mais check apres coup si cest valide
*/

char condStartG1(...);

char condEndG1(...);

/*creer lenum detat stateG1*/
STATEG1 updateSTATEG1(...);
