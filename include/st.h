#include <string.h>
#include "Item.h"
#include "hash.h"

#define key(i) (i->palavra)
#define less(v,t) (strcmp(v,t)<0)
#define eq(v,t) (strcmp(v,t)==0)
#define NLINHASBASE 40    					/*Numero de Linhas que se pode guardar inicialmente para cada palavra ESTAVA 10*/

typedef struct STnode* link;

struct STnode { Item item; link l, r; int N; };

static link head, z;

/*A arvore aqui usada guardas as estruturas palavralida que contem informacao acerca da palavra processada
a arvore guarda alfabeticamente as palavras o que e uma enorme vantagem*/ 

link NEW(Item item, link l, link r, int N) {
	link x = malloc(sizeof(struct STnode));
	x->item = item;
	x->l = l;
	x->r = r;
	x->N = N;
	return x;
}

void STinit() {
	head = (z = NEW(NULLitem, NULL, NULL, 0));
}

void visit(link h){
	if ((h->item != NULLitem) && (STHsearch(h->item->palavra) == NULL)){
		printf("%s %d\n", h->item->palavra, h->item->repeticoes);}
}

void traverseR(link h)
{
	if (h == NULL)
		return;
	traverseR(h->l);
	visit(h);
	traverseR(h->r);
}

void traverse(){
	traverseR(head);
}


Item searchR(link h, Key v) {
	Key t;
	if (h == z)
		return NULLitem;
	t = key(h->item);
	if (eq(v, t))
		return h->item;
	if (less(v, t))
		return searchR(h->l, v);
	else
		return searchR(h->r, v);
}

Item STsearch(Key v) {			/*Insere um elemento na arvore*/
	return searchR(head, v);
}

link insertR(link h, Item qitem) {
    int i;
	Key v = key(qitem), t;
	
	if (h == z) 
		return NEW(qitem, z, z, 1);
	t = key(h->item);
	if (eq(v,t)){  /* Se a palavra nova for igual, incrementa-se o numero de repeticoes da mesma, e adiciona-se
					* a lista de linhas em a a palavra esta presente, a linha correspondente.*/
		i = h->item->numerodelinhas;
		h->item->repeticoes++; 
			
	
		 /*Se o valor de repeticoe ultrapassar o valor de linhas base estabelecido, é aumentado para o quadrado*/
		if(i == (NLINHASBASE)){   
			h->item->expandeBase = i;                      
			h->item->nLinhas = realloc(h->item->nLinhas, sizeof(int)* (NLINHASBASE) * h->item->expandeBase);   
		}
			/*A partir dai, sempre que expandir multiplica por 10*/
		else if(i == ((NLINHASBASE) * h->item->expandeBase)){
			h->item->expandeBase *= 50;
			h->item->nLinhas = realloc(h->item->nLinhas, sizeof(int)* (NLINHASBASE) * h->item->expandeBase);
		}

    	if(h->item->nLinhas[i-1] < qitem->nLinhas[0]){   /*coloca-se no topo da lista de linhas o numero da nova linha guardado em qitem*/
			h->item->nLinhas[i] = qitem->nLinhas[0];
			h->item->numerodelinhas++;					/*Incrementa-se o numero total de linhas em que a palavra se encontra*/
		}
		free(qitem);
		
		return h;
	}				
	if (less(v, t))
		h->l = insertR(h->l, qitem);
	else
		h->r = insertR(h->r, qitem);
	(h->N)++;
	return h;
}

void STinsert(Item item) {
	head = insertR(head, item);
}
