#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define keys(A) (A)

typedef struct Estrutura* linkH;

struct Estrutura {char* palavra; linkH proxima;}; 
typedef  char* Keys;
typedef char* ItemP;

static linkH *heads;
static int M;
int hash(Keys v,int M){					/*Funcao de Dispersao*/
	int i=0;
	int acc =0;
	 
	while(*(v+i) != '\0'){
		acc += *(v+i);
		i++; 
	}
	acc = acc % M;
	return acc;
} 

void STHinit(int max) {						/*Interface*/
	int i;
	M = max;
	heads = (linkH*)malloc(M*sizeof(linkH));
	for (i = 0; i < M; i++) heads[i] = NULL;
}

/*=====================================================*/
ItemP searchList(linkH headLista ,Keys v){
	linkH aux;
	for(aux=headLista; aux != NULL;aux=aux->proxima){
		if (strcmp(aux->palavra,v)==0)
			return aux->palavra;
	}
	return NULL;
}

ItemP STHsearch(Keys v) {					/*Interface*/
	return searchList(heads[hash(v, M)], v);
}
/*====================================================*/

linkH NEWH(ItemP item){													
	linkH x = (linkH) malloc(sizeof(struct Estrutura));
	x->palavra = item;
	x->proxima = NULL;
	return x;
}

linkH insertBeginList(linkH headLista,ItemP item){
	linkH aux;
	
	if (headLista == NULL) 
		return NEWH(item);	
	for(aux = headLista; aux->proxima != NULL;aux=aux->proxima);
	aux->proxima = NEWH(item);
	
	return headLista;
}

void STHinsert(ItemP item) {				/*Interface*/
	int i = hash(keys(item), M);
	heads[i] = insertBeginList(heads[i], item);
}
