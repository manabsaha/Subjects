#include<stdio.h>
#include<pthread.h>
#include <stdlib.h>
#include <unistd.h>

/* This function prints hello world and accepts a argument pointer of void type. 
This function is being called from a new thread. */
void print_hello(void *arg){
	pthread_t id = *(int *) arg;
    printf("Hello World ( In Thread ID %d )\n",id);
    /* exiting from thread. */
	pthread_exit(NULL);
}

// Driver Function
int main(){
    pthread_t thread_id;
    /* Beginning the new thread */
    printf("Executing the thread\n");
    pthread_create(&thread_id,NULL,print_hello,&thread_id);  // creating a thread
    /* waiting for thread execution to get finished. */
	pthread_join(thread_id, NULL);
    printf("Thread execution completed\n");
    /* Thread execution finished and exiting */
    exit(0);
}

