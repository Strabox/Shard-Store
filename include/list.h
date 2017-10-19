/*
 * list.h - definitions and declarations of the integer list 
 */

#include <stdlib.h>
#include <stdio.h>
#include <kos_client.h>

/* */

/* lst_iitem - each element of the list points to the next element */

typedef struct lst_iitem {
   char* value;
   char* key;
   struct lst_iitem *next;
} lst_iitem_t;

/* list_t */
typedef struct {
   lst_iitem_t *first;
} list_t;

/* lst_new - allocates memory for list_t and initializes it */
list_t* lst_new();

/* lst_destroy - free memory of list_t and all its items */
void lst_destroy(list_t *);

/* lst_insert - insert a new item with value 'value' in list 'list' */
char* lst_insert(list_t *list, char* value,char* key);

/* lst_remove - remove first item of value 'value' from list 'list' */
char* lst_remove(list_t *list, char* value);

/* lst_print - print the content of list 'list' to standard output */
void lst_print(list_t *list);

/* lst-search - search the content of node with the key */
char* lst_search(list_t*,char*);

/*void lst_print_reverse(list_t *list); o código desta é usado pela lst_print */

/*Função que percorre uma lista da hash e insere pares KV com campos preenchidos num array.*/
int lst_PutKVinArray(list_t *list, KV_t* array, int posInArray);

/*@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/
