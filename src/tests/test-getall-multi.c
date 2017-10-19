#include <kos_client.h>
#include <pthread.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_EL 4 // 600
#define NUM_SHARDS 2 //3
#define NUM_CLIENT_THREADS 2 //30
#define NUM_SERVER_THREADS 2 //30
#define BUF_SIZE 5 //30


#define DEBUG_PRINT_ENABLED 1  // uncomment to enable DEBUG statements
#if DEBUG_PRINT_ENABLED
#define DEBUG printf
#else
#define DEBUG(format, args...) ((void)0)
#endif

/*
	printf("client=%d shard:%d\n",client_id,j);
	int* ptrNumElem_;
	KV_t* array_ = kos_getAllKeys(0, 0, ptrNumElem_ );
	int index_;
	for(index_ = 0; index_ < *ptrNumElem_; index_++){
		printf("%s,%s\n",array_[index_].key, array_[index_].value);
	}
*/
void *client_thread(void *arg) {

	char key[KV_SIZE], value[KV_SIZE], value2[KV_SIZE];
	char* v;
	int i,j;
	int client_id=*( (int*)arg);
	//Testas All
	int ptrNumElem_;
	KV_t* array_;
	int index_;

	for (j=NUM_SHARDS-1; j>=0; j--) {	
		for (i=NUM_EL; i>=0; i--) {
			sprintf(key, "k-c%d-%d",client_id,i);
			sprintf(value, "val:%d",i);
			v=kos_put(client_id, j, key,value);
			DEBUG("C:%d  <%s,%s> inserted in shard %d. Prev Value=%s\n", client_id, key, value, j, ( v==NULL ? "<missing>" : v ) );
		}
	}	
	printf("client=%d shard:%d\n",client_id,j);
	
	array_ = kos_getAllKeys(client_id, 0, &ptrNumElem_ );
	printf(">>>>>%d\n",ptrNumElem_);
	for(index_ = 0; index_ < ptrNumElem_; index_++){
		printf("%s:%s\n",array_[index_].key, array_[index_].value);
	}
	
	
	printf("------------------- %d:1/6 ENDED INSERTING -----------------------\n",client_id);
	
	

	for (j=NUM_SHARDS-1; j>=0; j--) {	
		for (i=0; i<NUM_EL; i++) {
			sprintf(key, "k-c%d-%d",client_id,i);
			sprintf(value, "val:%d",i);
			v=kos_get(client_id, j, key);
			if (v==NULL || strncmp(v,value,KV_SIZE)!=0) {
				printf("TEST FAILED --> Error on key %s value should be %s and was returned %s",key,value,v);
				exit(1);
			}
			DEBUG("C:%d  %s %s found in shard %d: value=%s\n", client_id, key, ( v==NULL ? "has not been" : "has been" ),j,
									( v==NULL ? "<missing>" : v ) );
	
		}
	}
	
	printf("------------------ %d:2/6 ENDED READING  ---------------------\n",client_id);

	for (j=NUM_SHARDS-1; j>=0; j--) {	
		for (i=NUM_EL-1; i>=NUM_EL/2; i--) {
			sprintf(key, "k-c%d-%d",client_id,i);
			sprintf(value, "val:%d",i);
			v=kos_remove(client_id, j, key);
			if (v==NULL || strncmp(v,value,KV_SIZE)!=0) {
				printf("TEST FAILED --> Error when removing key %s value should be %s and was returned %s",key,value,v);
				exit(1);
			}
			DEBUG("C:%d  %s %s removed from shard %d. value =%s\n", client_id, key, ( v==NULL ? "has not been" : "has been" ),j,
									( v==NULL ? "<missing>" : v ) );
		}
	}
		printf("client=%d shard:%d\n",client_id,j);
	

	
	array_ = kos_getAllKeys(client_id, 0, &ptrNumElem_ );
	
	for(index_ = 0; index_ < ptrNumElem_; index_++){
		printf("%s,%s\n",array_[index_].key, array_[index_].value);
	}
	

	printf("----------------- %d-3/6 ENDED REMOVING -------------------------\n",client_id);

	for (j=NUM_SHARDS-1; j>=0; j--) {	
		for (i=0; i<NUM_EL; i++) {
			sprintf(key, "k-c%d-%d",client_id,i);
			sprintf(value, "val:%d",i);
			v=kos_get(client_id, j, key);
			if (i>=NUM_EL/2 && v!=NULL) {
				printf("TEST FAILED --> Error when gettin key %s value should be NULL and was returned %s",key,v);
				exit(1);
			}
			if (i<NUM_EL/2 && (v==NULL || strncmp(v,value,KV_SIZE)!=0) ) {
				printf("TEST FAILED --> Error on key %s value should be %s and was returned %s",key,value,v);
				exit(1);
			}
			DEBUG("C:%d  %s %s found in shard %d. value=%s\n", client_id, key, ( v==NULL ? "has not been" : "has been" ) ,j, ( v==NULL ? "<missing>" : v ) );
		}
	}

	printf("----------------- %d-4/6 ENDED CHECKING AFTER REMOVE -----------------\n",client_id);


	for (j=NUM_SHARDS-1; j>=0; j--) {	
		for (i=0; i<NUM_EL; i++) {
			sprintf(key, "k-c%d-%d",client_id,i);
			sprintf(value, "val:%d",i*10);
			sprintf(value2, "val:%d",i*1);
			v=kos_put(client_id, j, key,value);

			if (i>=NUM_EL/2 && v!=NULL) {
				printf("TEST FAILED --> Error when getting key %s value should be NULL and was returned %s",key,v);
				exit(1);
			}
			if (i<NUM_EL/2 && (v==NULL ||  strncmp(v,value2,KV_SIZE)!=0 ) ) {
				printf("TEST FAILED --> Error on key %s value should be %s and was returned %s",key,value2,v);
				exit(1);
			}


			DEBUG("C:%d  <%s,%s> inserted in shard %d. Prev Value=%s\n", client_id, key, value, j, ( v==NULL ? "<missing>" : v ) );
		}
	}
			printf("client=%d shard:%d\n",client_id,j);

	
	array_ = kos_getAllKeys(client_id, 0, &ptrNumElem_ );
	
	for(index_ = 0; index_ < ptrNumElem_; index_++){
		printf("%s,%s\n",array_[index_].key, array_[index_].value);
	}
	

	printf("----------------- %d-5/6 ENDED 2nd PUT WAVE ----------------\n",client_id);


	for (j=NUM_SHARDS-1; j>=0; j--) {	
		for (i=0; i<NUM_EL; i++) {
			sprintf(key, "k-c%d-%d",client_id,i);
			sprintf(value, "val:%d",i*10);
			v=kos_get(client_id, j, key);
			if (v==NULL || strncmp(v,value,KV_SIZE)!=0) {
				printf("TEST FAILED --> Error on key %s value should be %s and was returned %s",key,value,v);
				exit(1);
			}
			DEBUG("C:%d  %s %s found in shard %d: value=%s\n", client_id, key, ( v==NULL ? "has not been" : "has been" ),j,
									( v==NULL ? "<missing>" : v ) );
	
		}
	}
	

	printf("----------------- %d-6/6 THE END ----------------------\n",client_id);

	return NULL;
}


int main(int argc, const  char* argv[] ) {

	int i,s,ret;
	int* res;
	pthread_t* threads=(pthread_t*)malloc(sizeof(pthread_t)*NUM_CLIENT_THREADS);
	int* ids=(int*) malloc(sizeof(int)*NUM_CLIENT_THREADS);

	ret=kos_init(NUM_SERVER_THREADS, BUF_SIZE, NUM_SHARDS);


	if (ret!=0)  {
			printf("kos_init failed with code %d!\n",ret);
			return -1;
		}
		
	for (i=0; i<NUM_CLIENT_THREADS; i++) {	
		ids[i]=i;		
		
		if ( (s=pthread_create(&threads[i], NULL, &client_thread, &(ids[i])) ) ) {
			printf("pthread_create failed with code %d!\n",s);
			return -1;
		}
	}

	for (i=0; i<NUM_CLIENT_THREADS; i++) {	
               s = pthread_join(threads[i], (void**) &res);
               if (s != 0) {
                   printf("pthread_join failed with code %d",s);
			return -1;
		}
           }

	return 0;
}
