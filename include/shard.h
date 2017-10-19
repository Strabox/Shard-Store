/*
 * shard.h definition and declarion of the Shard Structure.
 */
 
#include <pthread.h>
#include <hash.h>

typedef struct shard{
  int ElementsInShardCounter; 	//Guarda a quantidade total de pares< key,value> que se encontram no shard.
  list_t** hash;				//HashMap
  pthread_mutex_t Mutex;		//Mutex: para que nao haja 2 tarefas na mesma shard (1º parte do projecto).
}Shard;

/* init_Shard - allocate memory for Shard Strucutures and initializes it. */ 
void init_Shard_structure(int num_shards);

/* ger_from_Shard - return value of given key, in shard (shardid). */
char* get_from_Shard(int shardid,char* key);

/* put_in_Shard - put in shard(shardid) the pair <key,value>. */
char* put_in_Shard(int shardid,char* key,char* value);

/* remove_from_Shard - remove from shard the pair <value,key> corresponding to key given key. */
char* remove_from_Shard(int shardid,char* key);

/*puts all the pairs existent in a shard in an array*/
KV_t* print_from_Shard(int shardid, int* key);

/*@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/
