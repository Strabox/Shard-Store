/*
 * hash.h definition and declaration of HasMap.
 */

#include <list.h>
#include <kos_client.h>

/* hash - hash function*/
int hash(char* key);

/* ht_Init - Initializes the hashmap. */
list_t** ht_Init();

/* ht_Insert - Insert the pair <key,value> in the hashmap. */
char* ht_Insert(list_t** Hash,char* key, char* value);

/* ht_Remove - Removes from hashmap the pair <key,value> correspondig to the given key. */
char* ht_Remove(list_t** Hash,char* key);

/* ht_Search - Search in hashmap the pair <key,value> corresponding to the given key.   */
char* ht_Search(list_t** Hash,char* key);

/* ht_Destroy - Release all memory used by hashmap. */
void ht_Destroy(list_t** Hash);

/* ht_PutKVinArray - Insert all pairs <key,value> in KV_t* array */
void ht_PutKVinArray(list_t** Hash, KV_t* array);

/*@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/
