#include <string.h>
#include "Item.h"
#include "hash.c"

#define key(i) (i->palavra)
#define less(v,t) (strcmp(v,t)<0)
#define eq(v,t) (strcmp(v,t)==0)
#define NLINHASBASE 20			/*Numero de Linhas que se pode guardar inicialmente para cada palavra*/

typedef struct STnode* link;

struct STnode { Item item; link l, r; int N; };

static link head, z;

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

int STcount() {
	return head->N;
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

Item STsearch(Key v) {
	return searchR(head, v);
}

link insertR(link h, Item qitem) {
    int i, j;
	Key v = key(qitem), t;
	int *temp;
	
	j=1;
	if (h == z) 
		return NEW(qitem, z, z, 1);
	t = key(h->item);
	if (eq(v,t)){
		h->item->repeticoes++;
		for(i=0; h->item->nLinhas[i] != -1; i++)
		while(i>=(NLINHASBASE*j)){
			j++;
			temp = realloc(h->item->nLinhas, sizeof(int)*(NLINHASBASE)*j);
			h->item->nLinhas = temp;
			free(temp);
		}
    	if(h->item->nLinhas[i-1] < qitem->nLinhas[0]){
			h->item->nLinhas[i] = qitem->nLinhas[0];
			h->item->nLinhas[i+1] = -1;
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
