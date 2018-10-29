/* fsm.c */
#include "fsm.h"

char condStart(char c, STATE* pFsm){
	if (c!='\0' && isblank(c)){ return 1;}
	*pFsm = init; /* initialisation of the state variable */
	return 0;
}

/* returns 0 if the state is terminal */
char condEnd(char c, STATE* pfsm){
	*pfsm = updateState(c,*pfsm);
	/* the loop continue if it is not the final state */
	return !isFinalState(*pfsm);
}

STATE updateState(char c,STATE fsm){
	if (isFinalState(fsm)) return fsm;
	switch(fsm){
	case init :
		switch(c){
			case '#':
				return attFinCom;
			break;
			case '.': 
				return attFinDirective; /* à discuter */
			break;
			case '(':
				return PARENTHESEG;
			break;
			case ')':
				return PARENTHESED;
			break;
			case '\0': /* because of the getlinefunction */
				return RETOURLINE;
			break;
			case ':':
				return DEUXPOINTS;
			break;
			case ',':
				return VIRGULE;
			break;
			case '"':
				return attFinString;
			break;
			case '-':
				return attNombre;
			break;
			case '$':
				return attFinReg;
			break;
			default:
				if(isdigit(c)){
					return nombre;
				}
				else if((c=='_') || isalpha(c)/* ||c=='$' */){
					return attFinSymb;
				}
				else{
					/* ERROR */
					printf ("\033[31m ERROR or lexeme not implemented yet\033[0m\n");
				}
			break;
		}
	break;
	case attFinReg:
		if(isblank(c) || c == '\0'){
			return REGISTRE;
		}
		else{
			return attFinReg;
		}
	break;
	case attFinDirective:
		if (isblank(c) || c == '\0'){
			return DIRECTIVE;
		}
		else{
			return attFinDirective;
		}
	break;
	case attFinCom :
		if(c == '\0'){
			return COM;
		}
		return attFinCom;
	break;
	case nombre :
		if(isdigit(c)){
			return attFinDecimal;
		}
		else if(c=='x'){
			return attFinHexa;
		}
		else if (isblank(c)||c=='\0'){
			return DECIMAL;
		}
		printf ("\033[31m ERROR or lexeme not implemented yet\033[0m\n");
	break;
	case attNombre:
		if (isblank(c)){
			return attNombre;
		}
		else if (isdigit(c)){
			return nombre;
		}
	printf ("\033[31m ERROR or lexeme not implemented yet\033[0m\n");
	break;
	case attFinDecimal:
		if (isdigit(c)){
			return attFinDecimal;
		}
		else if(isblank(c) || c=='(' || c==','|| c=='#'||c=='\0'){
			return DECIMAL;
		}
	printf ("\033[31m ERROR or lexeme not implemented yet\033[0m\n");
	break;
	case attFinHexa :
		if (isdigit(c)|| (c>='a'&& c<='f')|| (c>='A' && c<='F')){
			return attFinHexa;
		}
		else if (isblank(c) || c=='(' || c==','|| c=='#'||c=='\0'){
			return HEXA;
		}
	printf ("\033[31m ERROR or lexeme not implemented yet\033[0m\n");
	break;
	case attFinSymb:
		if ( isalnum(c) || c=='_'){
			return attFinSymb;
		}
		else if( isblank(c) || c=='\0' || c=='.' || c==':' || c==')'|| c==','){
			return SYMB;
		}
	printf ("\033[31m ERROR or lexeme not implemented yet\033[0m\n");
	break;
	case attFinString :
		if(c=='\\'){
			return tempString;
		}
		else if(c != '\0',c!='"'){
			return attFinString;
		}
		else{
			return STRING;
		}
	break;
	case tempString :
		if (c !='\0'){
			return attFinString;
		}
	break;
	}
}

/* works perfectly */
char isFinalState(STATE fsm){
	if (((int)fsm > (int)ETATFINAL)){
		return 1;
	}
	return 0;
}

/* 
if the condition to end the fsm is a character which belong to the lexeme 
the string need to be 1 char longer
NB: a number can be a single char exemple : 8 
a last case has been implemented
*/
char needMoreChar(STATE fsm,char * start, char * end){
	switch(fsm){
		case POINT:
		case DEUXPOINTS:
		case VIRGULE:
		case STRING:
		case PARENTHESED:
		case PARENTHESEG:
		return 1;
		break;
		case DECIMAL:
			if ((end-start)==0){
				return 1;
			}
	}
	return 0;
}
