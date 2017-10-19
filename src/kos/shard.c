/*
 * shard.c implementation of shard system.
 */
 
#include <shard.h>
#include <delay.h>
#include <string.h>


/*============================================================ SHARD SYSTEM =======================================================*/

/* Ponteiro para a estrutura de shards (Array de shards) */
Shard* ShardStructure;

void init_Shard_structure(int num_shards){						// Inicializa os Shards todos e as suas respectivas hashmaps.
  int cont;		
  
  ShardStructure = (Shard*) malloc(sizeof(struct shard)*num_shards);
  
  for(cont = 0; cont < num_shards; cont++){
    (ShardStructure + cont)->ElementsInShardCounter = 0;
    (ShardStructure + cont)->hash = ht_Init();					//Inicializa a hash do shard.
    pthread_mutex_init(&(ShardStructure + cont)->Mutex, NULL); 	//Inicializa o Mutex (1º Parte Projecto). 
  }
  return;
}

char* get_from_Shard(int shardid,char* key){					//Funcao que vai buscar um valor ao shard dado.
  char* res;
  
  pthread_mutex_lock(&(ShardStructure + (shardid))->Mutex);
  //delay();
  res = ht_Search((ShardStructure + (shardid))->hash, key);
  
 pthread_mutex_unlock(&(ShardStructure + (shardid))->Mutex);
  
  return res;
}

char* put_in_Shard(int shardid,char* key,char* value){			// Funcao que coloca um pare <value,key> no shard dado.
  char* res;
  
  pthread_mutex_lock(&(ShardStructure + (shardid))->Mutex);
  //delay();
  res = ht_Insert((ShardStructure + (shardid))->hash,key,value);
  
  if (res==NULL) (ShardStructure + (shardid))->ElementsInShardCounter++;
  
 pthread_mutex_unlock(&(ShardStructure + (shardid))->Mutex);
  
  return res;
}

char* remove_from_Shard(int shardid,char* key){						// Funcao que remove um elemento no shard dado.
  char* res;
  
  pthread_mutex_lock(&(ShardStructure + (shardid))->Mutex);
  //delay();
  res= ht_Remove((ShardStructure + (shardid))->hash,key);
  
  if (res!=NULL) (ShardStructure + (shardid))->ElementsInShardCounter--;
  
  pthread_mutex_unlock(&(ShardStructure + (shardid))->Mutex);
  
  return res;
} 


KV_t* print_from_Shard(int shardid, int* dim){
  KV_t* array;
  
  pthread_mutex_lock(&(ShardStructure + (shardid))->Mutex);
  //delay();	
  *dim = (ShardStructure + (shardid))->ElementsInShardCounter; 						//poe o numero de elementos na shard na posicao de memoria indicada pelo cliente
 
  array = (KV_t*) malloc(sizeof(KV_t)*( (ShardStructure + (shardid))->ElementsInShardCounter)); //cria o vector de pares key,value
 
  ht_PutKVinArray((ShardStructure + (shardid))->hash,array); 						//no array sao postos os pares

  pthread_mutex_unlock(&(ShardStructure + (shardid))->Mutex);
  
  return array;
}

/*@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ END @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/
