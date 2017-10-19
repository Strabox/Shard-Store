/*@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ KOS @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/
/* LOG:
 * 
 * DONE:
 * -> Estrutura das Listas [TESTED]: Tive que as modificar porque tem que se guardar 2 strings <Key,Value>
 * Os retornos também tiveram que ser modificados para ajustar certas funcionalidades.
 * 
 * -> Estrutura da HashMap [TESTED]: Esta funciona apoiada nas listas porque é por (encadeamente externo).
 * 
 * -> Estrutura do KOS     [TESTED]: Ja funciona e passa em todos os testes tanto multi como single.
 *  
 * MISSING:
 * -> Falta resolver os memoty leaks, que andam por ai devido aos char* que vao sendo passados.
 * 
 * -> Falta tambem implementar a ultima funcao kos_Get_All_Keys.
 * 
 * -> !!!!!CUIDADO TEM QUE SE DESTRUIR OS MUTEXES/SEMANAFOROS!!!!!!!!!.
*/

#include <buffer.h>
#include <kos_client.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <shard.h>
#include <string.h>

/*=========================================== FUNCOES DO KOS ==================================================*/

int kos_init(int num_server_threads, int buf_size, int num_shards) {
	int i,s;
	
	init_Shard_structure(num_shards);						// Inicializa o Shards System.
	init_Buffer(buf_size);									// Inicializa o Buffer.
	
	pthread_t* threads=(pthread_t*)malloc(sizeof(pthread_t)*num_server_threads);	
	int* ids=(int*) malloc(sizeof(int)*num_server_threads);						
	
	for (i=0; i<num_server_threads; i++) {	
		ids[i]=i;		
		
		if ( (s=pthread_create(&threads[i], NULL, &attend_request, &(ids[i])) ) ) { //Lança os threads servidores.
			printf("pthread_create failed with code %d!\n",s);
			return -1;
		}
	}
	return 0;

}

char* kos_get(int clientid, int shardId, char* key) {
	if (key==NULL) return NULL;
	return request(shardId,clientid,key,NULL,1);
}


char* kos_put(int clientid, int shardId, char* key, char* value) {
    if ((key==NULL)||(value==NULL)||(strcmp(key,"")==0)) return NULL;
	return request(shardId,clientid,key,value,2);
}


char* kos_remove(int clientid, int shardId, char* key) {
	if (key==NULL) return NULL;
	return request(shardId,clientid,key,NULL, 3);
}

KV_t* kos_getAllKeys(int clientid, int shardId, int* dim) {	
	
	return request_pairs(shardId,clientid,dim ,4);
}


/*@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ END @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/
