/*
 * buffer.h definition and declaration of the buffer.
 */
 
#include <semaphore.h>
#include <kos_client.h>

struct buffer{
  char* key;			// Key dada pelo cliente (OBRIGATORIO).
  char* value;			// Value dado pelo cliente (OPCIONAL).
  int 	shardId;		// Shard em que se tem que fazer a operacao(OBRIGATORIO).
  int 	operacao;		// Indica que operacao realizar (OBRIGATORIO).
  char* res;			// Onde a tarefa servidora deixa o resultado do pedido/operacao.
  KV_t* vec;			// Onde a tarefa servidora deixa o array caso seja essa a operacao.
  int* ptrNEL;			// Onde é guardado o ponteiro para o número de elementos fornecido pela getAllKeys.
  sem_t cliente;		// Semaforo para sincronizar Cliente.
  sem_t servidor;		// Semaforo para sincronizar Servidor.
};

typedef struct buffer Buffer;

/* init_Buffer - allocate memory for buffers and initializes it. */
void init_Buffer(int buffer_size);

/* get_res - Returns the result of buffer. */
char* get_res(int clientid);

/* request - (Used by client threads) put the request in buffer. */
char* request(int shardid,int clientid,char* key,char* value, int operacao);

/* request_pairs - (Used by client threads) put the request about KV_t array in buffer. */
KV_t* request_pairs(int shardid,int clientid,int* dim,int operacao);

/* atten_request - (Used by server threads) to attend the request from client threads. */
void *attend_request(void* arg);

/*@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/
