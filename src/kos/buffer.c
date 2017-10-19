/*
 * buffer.c implementation of bufer.
 */

#include <buffer.h>
#include <shard.h>

/*=============================================== BUFFER ============================================================*/

/* Ponteiro para a estrutura do Buffer (Array de struct buffers) */
Buffer* BufferStructure;

/* Funcao que inicializa o buffer*/
void init_Buffer(int buffer_size){

  int cont;
  
  BufferStructure = (Buffer*) malloc(sizeof(struct buffer)*buffer_size);
  
  for(cont = 0; cont < buffer_size; cont++){	
      (BufferStructure + cont)->key = NULL;
      (BufferStructure + cont)->value = NULL;
      (BufferStructure + cont)->res = NULL;
      (BufferStructure + cont)->ptrNEL = NULL;
      (BufferStructure + cont)->vec = NULL;
      (BufferStructure + cont)->shardId = 0;
      (BufferStructure + cont)->operacao = 0;
      sem_init(&(BufferStructure + cont)->cliente,0,0);		//Inicializacao do semaforo cliente.
      sem_init(&(BufferStructure + cont)->servidor,0,0);	//Inicializacao do semaforo servidor.
  }
  
  return;
}

/* Funcao que vai buscar o resultado ao buffer depois do servidor ja ter sinalizado que acabou*/
char* get_res(int clientid){
 
  return (BufferStructure + (clientid))->res;
  
}

/* Funcao para que as tarefas clientes peçam para inserir pares <key,value> no KOS. Ou seja os pedidos ao sistema. 
 */

char* request(int shardid,int clientid,char* key,char* value, int operacao){
  
  (BufferStructure + (clientid))->key = key;
  (BufferStructure + (clientid))->value = value; 			
  (BufferStructure + (clientid))->shardId = shardid;
  (BufferStructure + (clientid))->operacao = operacao;

  sem_post(&((BufferStructure + (clientid))->servidor));
  
  sem_wait(&((BufferStructure + (clientid))->cliente));
  
  return get_res(clientid);
}



/* Funcao de request para obtenção dos pares <key,value> de uma shard */
KV_t* request_pairs(int shardid,int clientid,int* dim,int operacao){
	
	(BufferStructure + (clientid))->shardId = shardid;
	(BufferStructure + (clientid))->operacao = operacao;
	(BufferStructure + (clientid))->ptrNEL = dim;
	
	sem_post(&((BufferStructure + (clientid))->servidor));
  
	sem_wait(&((BufferStructure + (clientid))->cliente));
	
	return ((BufferStructure + (clientid))->vec);
}

/*Funcao usada pelas threadas servidoras para atender os pedidos */

void *attend_request(void* arg ){
  
  int id=*( (int*)arg);
  
  while(1){
  
  sem_wait(&((BufferStructure + (id))->servidor));
  
  if((BufferStructure + (id))->operacao == 1)
    (BufferStructure + (id))->res = get_from_Shard((BufferStructure + (id))->shardId,(BufferStructure + (id))->key);
  else if((BufferStructure + (id))->operacao == 2)
    (BufferStructure + (id))->res = put_in_Shard((BufferStructure + (id))->shardId,(BufferStructure + (id))->key,(BufferStructure + (id))->value);
  else if((BufferStructure + (id))->operacao == 3)
    (BufferStructure + (id))->res = remove_from_Shard((BufferStructure + (id))->shardId,(BufferStructure + (id))->key);
  else if((BufferStructure + (id))->operacao == 4){
	(BufferStructure + (id))->vec = print_from_Shard((BufferStructure + (id))->shardId, (BufferStructure + (id))->ptrNEL);
  }
  
  sem_post(&((BufferStructure + (id))->cliente));
	
  }
  
  return NULL;
}

/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ END @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
