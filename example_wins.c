#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>
#include "lfstack.h"
#include <Windows.h>
#include <time.h>

struct timeval  tv1, tv2;
lfstack_t mystack;

#define nthreads 8
#define total_put 50000

unsigned __stdcall worker(void *);
unsigned __stdcall worker(void *arg)
{
	int i = 0;
	int *int_data;
	while (i < total_put) {
		int_data = (int*)malloc(sizeof(int));
		assert(int_data != NULL);
		*int_data = i++;
		while (lfstack_push(&mystack, int_data)) {
			printf("ENQ FULL?\n");
		}
		
		while ((int_data = lfstack_pop(&mystack)) == NULL) {
			// usleep(1000);
			printf("POP EMPTY?\n");
		}
		free(int_data);
	}
	return 0;
}

#define join_threads \
for (i = 0; i < nthreads; i++)\
WaitForSingleObject(threads[i], INFINITE);\
printf("current size= %d\n", (int) lfstack_size(&mystack) )
/*
#define detach_thread_and_loop \
for (i = 0; i < nthreads; i++)\
pthread_detach(threads[i]);\
while (1) {\
sleep(2);\
printf("current size= %zu\n", lfstack_size(&mystack) );\
}*/


int main(void)
{
	//const static int nthreads = 2;//sysconf(_SC_NPROCESSORS_ONLN); // Linux
	int i, n; 
	if (lfstack_init(&mystack) == -1)
		return -1;

	for (n = 0; n < 25; n++) {
		/* Spawn threads. */
		printf("Current running at %d, Total threads = %d\n", n, nthreads);
		clock_t start = clock();
		HANDLE threads[nthreads];

		for (i = 0; i < nthreads; i++) {
			unsigned udpthreadid;
			threads[i] = (HANDLE)_beginthreadex(NULL, 0, worker, NULL, 0, &udpthreadid);
		}

		join_threads;
		// detach_thread_and_loop;

		clock_t end = clock();

		printf("Total time = %f seconds\n", (float)(end - start) / CLOCKS_PER_SEC);

		assert(0 == lfstack_size(&mystack) && "Error, all queue should be consumed but not");

	}
	printf("Take a 4 seconds sleep \n");
	Sleep(4000);
	printf("Flush all the inactive memory \n");
	lfstack_flush(&mystack);
	printf("Press Any Key to Continue\n");
	lfstack_destroy(&mystack);
	getchar();
	return 0;
}

