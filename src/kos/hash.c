/*
 * hash.c implementation of hashmap <string(key),string(value)>.
 */
 
#include <unistd.h>
#include <hash.h>

#define HT_SIZE 10	/* Tamanho da HashTable */

/*========================================= Estrutura Da Hash Table Por Encadeamento Externo=======================================*/

/* Funcao hash que devolve o indice onde se guarda o elemento */

int hash(char* key) {
     
    int i=0;
 
    if (key == NULL)
        return -1;
 
    while (*key != '\0') {
        i+=(int) *key;
        key++;
    }
 
    i=i % HT_SIZE;
 
    return i;
}

/* Funcao que inicializa e devolve um ponteiro para uma HashTable do tipo (list_t** hash) */

list_t** ht_Init(){
  int a;
  list_t** hash;
  
  hash = (list_t**) malloc(sizeof(list_t*)*HT_SIZE);
  
  for(a = 0; a < HT_SIZE; a++){
    *(hash + a) = lst_new();
  }
    
  return hash;
  
}

/* Funcao que insere o elemento na HashTable
 * return NULL - Caso nao haja nenhum elemento com essa key
 * return char*- Retorna o value do par <value,key> caso exista essa key */

char* ht_Insert(list_t** Hash,char* key, char* value){
  int indice;
  
  indice = hash(key);
  
  return lst_insert(*(Hash + indice),value,key);
  
}

/* Funcao que elimina um elemento da HashTable */
 
char* ht_Remove(list_t** Hash,char* key){
  int indice;
  
  indice = hash(key);
  
  return lst_remove(*(Hash + indice),key);
}

/* Funcao de procura de um elemento no HashMap 
*  Devolve o ponteiro para o valor caso encontre e NULL caso nao esteja no HashMap*/
char* ht_Search(list_t** Hash,char* key){
  int indice;
  
  indice = hash(key);
  
  return lst_search(*(Hash + indice), key);
  
}

/*(OPTIONAL) Funcao que liberta toda a memoria associada a HashTable*/

void ht_Destroy(list_t** Hash){
  int a;
  
  for(a = 0; a < HT_SIZE;a++){
    lst_destroy(*(Hash + a));
  }
  free(Hash);
}

/*Função que recorre às listas da hash para inserir pares KV num array.*/
void ht_PutKVinArray(list_t** Hash, KV_t* array){
	int posInArray=0;
	int listIndex;
	for(listIndex = 0; listIndex < HT_SIZE; listIndex++){
		posInArray= lst_PutKVinArray(*(Hash + listIndex), array, posInArray);
	}
	return;	
}

/*===================================================================END===============================================================================*/
