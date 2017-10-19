/*
 * list.c - implementation of the integer list functions 
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <list.h>

/*========================================== Estrutura De uma lista simplesmente ligada ===========================================================*/

/*Funcao que inicializa e devolve um ponteiro para uma lista*/

list_t* lst_new()
{
   list_t *list;
   list = (list_t*) malloc(sizeof(list_t));
   list->first = NULL;
   return list;
}

/* Cria e ALOCA memoria para um novo "node" que contem o elemento a guardar e um ponteiro para o proximo node */

lst_iitem_t* newNode(char* value, char* key) {
  lst_iitem_t* node;
  
  node = (lst_iitem_t*) malloc(sizeof(struct lst_iitem));
  node->value = (char*) malloc(sizeof(char)*(strlen(value)+1));
  node->key = (char*) malloc(sizeof(char)*(strlen(key)+1));
  strcpy(node->key, key);
  strcpy(node->value,value);
  node->next = NULL;
  
  return node;
}

/* Funcao que procura um elemento na lista 
 * return NULL - caso nem sequer exista esse elemento na lista.
 * return char*- retorna o ponteiro para o elemento da lista.
 */

char* lst_search(list_t *list,char* key){
 
   lst_iitem_t *node;

		
   for(node = list->first; (node != NULL) && (strcmp(node->key,key) != 0); node = node->next);

   if(node == NULL)
     return NULL;
   else{
	 char* valueToReturn;
	 valueToReturn = (char*) malloc(sizeof(char)*(strlen(node->value)+1));
	 strcpy(valueToReturn, node->value);
     return valueToReturn;
  }
}

/* Funcao que liberta toda a memoria que a lista usa */

void lst_destroy(list_t *list)
{
   lst_iitem_t* node;
   lst_iitem_t* aux;
  
   for(node = list->first; node != NULL; node = aux){
    aux = node->next;
    free(node->key);
    free(node->value);
    free(node);
   }
   free(list);
   return;
}

/* Funcao que insere um elemento na lista 
 * Return NULL - Se nao existir essa key na lista 
 * Return char*- Ponteiro para o valor associado a chave que ja la existia */
char* lst_insert(list_t *list, char* value,char* key)
{
   char* auxiliar;
   lst_iitem_t *node;
   
   if(list->first == NULL)  {
      list->first = newNode(value,key);
      return NULL;
   }
   for(node = list->first; (strcmp(node->key,key) != 0) && (node->next != NULL); node = node->next);
   
   if(strcmp(node->key,key) == 0){									// Existe um elemento igual na lista retorna o valor.
   
	  auxiliar = (char*) malloc(sizeof(char)*(strlen(node->value)+1));
	  strcpy(auxiliar,node->value);
	  free(node->value);
	  node->value = (char*) malloc(sizeof(char)*(strlen(value)+1));
	  strcpy(node->value,value);								    // Substitui o value antigo pelo novo.
	 
      return auxiliar;												// Retorna o antigo.
   }  
   else{															// Nao existe nenhum elemento igual na lista  insere-se.
      node->next = newNode(value,key);
      return NULL;
   }
     
}

/* Funcao que elimina um elemento da lista */

char* lst_remove(list_t *list, char* key)
{
   lst_iitem_t* node;
   lst_iitem_t* aux;
   char* copy;
   
   for(node = list->first, aux = NULL; node != NULL;aux = node, node = node->next){
    if(strcmp(node->key,key) == 0){
     if(node == list->first) 
       list->first = node->next;
     else 
       aux->next = node->next;
     
     copy = (char*) malloc(sizeof(char)*(strlen(node->value)+1));
     strcpy(copy,node->value);
     
     free(node->key);
     free(node->value);
     free(node);
     return copy;
    } 
   
   }
   return NULL;
}

/* Função que percorre uma lista da hash e insere pares KV com campos preenchidos num array.*/
int lst_PutKVinArray(list_t *list, KV_t* array, int posInArray){
	lst_iitem_t* node;
	
	if (list->first == NULL){
		return posInArray;
	}
	for(node = list->first; node != NULL; node = node->next){
		strncpy((array+posInArray)->key, node->key, 19);
		strncpy((array+posInArray)->value, node->value, 19);
		posInArray++;
	}
	return posInArray;
}

/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!(OPTIONAL) FUNCOES DE PRINT!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */

/*void lst_print(list_t *list) //original, not recursive.
{	
   lst_iitem_t* node;
   for(node = list->first; node != NULL;node = node->next) {
    if(node->next != NULL){
      printf("%s,",node->value);}
    else
    {printf("%s\n",node->value);}
   
   }
}
*/


void lista_recursive(lst_iitem_t *list){
	if (list == NULL){
		return;}
	lista_recursive(list->next);
	if (!(list->next == NULL)) printf(",");
	printf("%s", list->value);
	return;
}

/* Funcao que imprime o conteudo da lista de tras para a frente usando recursividade */

void lst_print(list_t *list){ 				//originally lst_print_recursive
	if (list->first == NULL){
		return;
	}
	lista_recursive(list->first);
	printf("\n");
	return;
}

/*@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@END@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/
