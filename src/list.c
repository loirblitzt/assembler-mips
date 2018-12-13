#include "list.h"

LIST createList(){
    return 0;
}


LIST addToList (LIST l, void* data , TYPE t, int line,char realType, char headTail){
    LIST a = (LIST)malloc(sizeof(*l));
	
	/* initialization of the struct element */
	a -> data = malloc(sizeFromType(t,data,realType)+1);
	if(a->data == NULL){return l;}
	memcpy((a -> data),data,sizeFromType(t,data,realType)); /* copy the data onto the struct */
	((char*)(a->data))[sizeFromType(t,data,realType)]='\0';
	if(l == NULL){
		a-> suiv  = a;
	}
	else{
		a -> suiv = l -> suiv;
		l-> suiv = a;
	}
	a -> type = t;
	a -> line = line;
	a -> trueType = realType;

	if (headTail == 0){return a;}
	
	else if (headTail== 1)
	{
		return l;
	}
	return NULL;
}

LIST addHead(LIST l, void* data, TYPE t, int line,char realType){
	return addToList(l,data,t,line,realType,0);
}
/* special fonction that specifie the size (taille) of a string */
LIST addHead2(LIST l, void* data, TYPE t, int line,int taille){
	LIST a = (LIST)malloc(sizeof(*l));
	
	/* initialization of the struct element */
	a -> data = malloc(taille*sizeof(char));
	memcpy((a -> data),data,taille*sizeof(char)); /* copy the data onto the struct */
	((char*)(a->data))[taille-1]='\0';
	if(l == NULL){
		a-> suiv  = a;
	}
	else{
		a -> suiv = l -> suiv;
		l-> suiv = a;
	}
	a -> type = t;
	a -> line = line;
	a -> trueType = 0;

	return a;
}

LIST addTail(LIST l, void* data, TYPE t, int line,char realType){
	return addToList(l,data,t,line,realType,1);
}

/* returns the ith element registered in the list( by addhead)
	doesnt  delete or free the element.
 */
LIST getElement(LIST l, int i){
	LIST c = l-> suiv;
	int a;
	for (a=0;a<i;a++){
		c = c->suiv;
	}
	return c;
}

/* maintenir cette fonction a chaque changement dans TYPE */
size_t sizeFromType(TYPE t, void* data,char realType){
	if(!realType){
		return strlen((char*)data)*sizeof(char);
	}
	switch(t){
		/* manage all string format */
		case commentaire:
		case symb:
		case string:
		case etiquette:
		case directive:
			return (strlen((char*)data))*sizeof(char);
		break;
		case virgule:
		case retourLine:
		case deuxPoints:
		case point:
			return sizeof(char);
			break;
		case decimal:
		case hexa:
			return sizeof(int);
			break;
	}
	/* if not implemented*/
	return 0; 
}

char* stringType[] = {
	"commentaire",
	"symb",
    "hexa",
    "decimal",
    "string",
    "virgule",
    "retourLine",
    "deuxPoints",
    "point",
    "etiquette",
    "directive",
	"parenthese de droite",
	"parenthese de gauche",
	"registre"
};
void printType(LIST l){
	/* if (l->type > parentheseg){
		printf("ERROR dont reconnize this type");
		return;
	} */
	printf("Type of : %s \n",stringType[l->type]);
}
void printAllTypes(LIST l){
	LIST c = l->suiv;
	do{
		printType(c);
		c =c -> suiv;
	}while ((l->suiv) != c);
}

void printData(LIST l){
	printf("\033[34;1m----------------------------\033[0m\n");
	printType(l);
	printf("line : %d \n",l->line);
	if(!(l->trueType)){
		printf("data : %s\n",((char*)(l->data)));
	}
	else{
		switch(l->type){
		case commentaire :
		case symb :
		case string :
		case virgule :
		case retourLine :
		case deuxPoints :
		case point :
		case etiquette :
		case directive :
			printf("data : %s\n",((char*)(l->data)));
		break;
		case hexa :
		case decimal :
			printf("data : %d\n",*(int*)(l->data));
		break;		
		}
	}
	printf("\033[34;1m----------------------------\033[0m\n");
}

void printAllData(LIST l){
	if(l==NULL) {printf("\033[31merror : liste vide\033[0m\n");return;}
	LIST cursorL = l->suiv;
	do{
		printData(cursorL);
		cursorL = cursorL->suiv;
	} while ((l->suiv) != cursorL);
}
void freeElement(LIST l){
	free(l->data);
	free(l);
}

void freeAllElements(LIST l){
	if(l==NULL) {printf("\033[31merror : liste vide\033[0m\n");return;}
	LIST c = l-> suiv;
	l->suiv = NULL;
	while (c != NULL){
		LIST tmp = c -> suiv;
		freeElement(c);
		c = tmp;
	}
}

/* checks if is the number is the begining of a 
	number - ( - register - )
	pattern */
char isNumberOk(LIST l){
	if (l == NULL) return 0;
	if ((l->type == decimal || l->type == hexa)
		&& l->suiv != NULL && (l->suiv)->type == parentheseg
		&& (l->suiv->suiv) != NULL &&(l->suiv->suiv)->type == registre
		&& l->suiv->suiv->suiv != NULL && l->suiv->suiv->suiv->type == parenthesed){
			return 1;
		}
	else{
		return 0;
	}
}