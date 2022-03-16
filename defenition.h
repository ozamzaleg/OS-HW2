#ifndef DEFINITION_H_
#define DEFINITION_H_


#include <pthread.h>

#define NTHREADS 2
#define TEXT ".txt"



typedef struct {
	int id;					// thread id
	int  *arr; 			// shared array
	int  *max;			//shared answer for max of all elemnts
	pthread_mutex_t *mutex;	// mutex to synchronize a write to sum
	pthread_cond_t *confO;
    int* SIZE_CHUNK;
	


} ThreadParam;

#endif /* DEFINITION_H_ */