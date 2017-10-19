#include <stdio.h>
#include <stdlib.h>

typedef struct palavralida{		
    char* palavra;		/*Palavra a ser guardada*/
	int repeticoes;		/*Numero total de repeticoes da palavra ao longo do texto*/
	int numerodelinhas;	/*Numero total de linhas diferentes em que se encotra a palavra*/				
	int* nLinhas;		/*Vector que contem o numero das linhas em que a palavra se encontra*/ 
	int expandeBase;	
} palavralida;

typedef  char* Key;
typedef palavralida *Item;


Item NULLitem = NULL;
