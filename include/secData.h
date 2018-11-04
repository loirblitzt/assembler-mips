/*

	secData.h
gere la collection de .data
reste à definir la sttructure de la collection

en soit cest juste une liste
*/
enum _typeG1{
	int16
}; typedef enum _typeG1 TYPEG1;

enum _directive{
	space,
	byte,
	word,
	ascizz
}; typedef enum _directive DIRG1;

enum _section {
	none,
	text,
	data,
	bss
}; 
typedef enum _section SECTION;

struct _dataList {
	/* void* ou union valeur */
	/* TYPEG1 type; */
	DIRG1 dir; /* avec le nom de la dir on peut
	savoir la taille de la donne et ou son utilite
	 */
	int offset;
	int nbLine;
	struct _dataList* suiv;
}; 
typedef struct _dataList* DATALIST;

struct _dataColection {
	DATALIST l;
	SECTION sec;
	int currentOffset; /* curent offset kept in memory */
};
typedef struct _dataColection DATACOL;
/*creation*/

/*ajout*/

/*suppression*/
