#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "targil2.h"
#include "defenition.h"
#include "function.h"


	void *do_work(void *param) {

	int start, end, tid;
	int *sizechunk;
	int  *arr, *max;
	pthread_mutex_t *mutex;
	pthread_cond_t *confO;


	// Thread ID, array, mutex and global sum
	tid = ((ThreadParam *) param)->id;
	arr = ((ThreadParam *) param)->arr;
	mutex = ((ThreadParam *) param)->mutex;
	max = ((ThreadParam *) param)->max;
	confO = ((ThreadParam *) param)->confO;
	sizechunk = ((ThreadParam *) param)->SIZE_CHUNK;
	start = tid * (*sizechunk);
	end = start + (*sizechunk);
	


	pthread_mutex_lock(mutex);
	
	while(arr[0] == 0){
	pthread_cond_wait(confO,mutex);
	}


	*max = getMax(arr, start, end);

	pthread_mutex_unlock(mutex);
	pthread_exit(NULL);
 
}

int main(int argc, char *argv[]) {
	char letter = ' ';
	int len = 8;
	int SIZE_HUNK;
	int max = 0;
	pthread_cond_t confO;
	pthread_t threads[NTHREADS];
	pthread_mutex_t max_mutex;
	ThreadParam params[NTHREADS];

	char* fileName = getNameFile(argv, argc); 

	FILE *file = fopen(fileName, "r");
		if (!file)
	{
		printf("%s", "cant open the file");
		exit(EXIT_FAILURE);
	}

	int *array = readArrFromFile(file , &letter, &len);

	SIZE_HUNK = len/NTHREADS;


	for (int i = 0; i < NTHREADS; i++) {
		params[i].arr = array;
		params[i].SIZE_CHUNK = &SIZE_HUNK;
		params[i].id = i;
		params[i].mutex = &max_mutex;
		params[i].confO = &confO;
		params[i].max = &max;
		

		SIZE_HUNK = len - SIZE_HUNK;
		
		if(SIZE_HUNK %2 != 0){
			SIZE_HUNK = SIZE_HUNK +1;
		}
	
		
		pthread_create(&threads[i], NULL, do_work, (void *) &params[i]);
	}
		


			readElementFromFile(file,len,array);
			fclose(file);
			for(int i=0; i< NTHREADS; i++){
				pthread_cond_signal(&confO);
			}
			// pthread_cond_broadcast(&confO);


	/* Wait for all threads to complete then print global sum */
	for (int i = 0; i < NTHREADS; i++) {
		pthread_join(threads[i], NULL);
	}


	max = (*(params[0].max) > *(params[1].max)) ? *(params[0].max) : *(params[1].max);

	printf("\nThe of the array is: %d", max);

	/* Clean up and exit */
	pthread_mutex_destroy(&max_mutex);
	pthread_cond_destroy(&confO);
	pthread_exit(NULL);      
}


