/* fsm.h*/

#ifndef _FSM_H_
#define _FSM_H_

#include <ctype.h>
/* final states are written in ALL_CAPS */
enum _state {
	init =1,
	nombre,
	attFinCom,
	attFinSymb,
	attFinDirective,
	attFinString,
	attNombre,
	attFinDecimal,
	tempString,
	attFinHexa,
	ETATFINAL, /* if state > ETATFINAL then he is final */
	COM,
	SYMB,
	HEXA,
	DECIMAL,
	STRING,
	VIRGULE,
	RETOURLINE,
	DEUXPOINTS,
	POINT,
	ETIQUETTE,
	DIRECTIVE,
	PARENTHESED,
	PARENTHESEG
};
typedef enum _state STATE;

char isFinalState(STATE fsm);

char condStart(char c, STATE* pFsm);

char condEnd(char c, STATE* pFsm);

STATE updateState(char c, STATE fsm);

char needMoreChar(STATE fsm, char* start, char* end);
#endif