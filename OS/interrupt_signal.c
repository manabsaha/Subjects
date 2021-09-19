#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<signal.h>

/* This is the signal handler function for SIGINT */
void handler(int num){
    pid_t ret_id;
    /* Creates a new child process */
    ret_id = fork();
    /* Failed Fork */
    if(ret_id<0){
        printf("Failed to create process\n");
    }
    /* Child Process */
    else if(ret_id==0){
        printf("\n**** In the child process ****\n");
        printf("The process ID is: %d\n",getpid());
        printf("The parent process ID is: %d\n",getppid());
    }
    /* Parent Process */
    else{
        wait(NULL);
        printf("\n**** In the parent process ****\n");
        printf("The process ID is: %d\n",getpid());
        printf("The parent process ID is: %d\n",getppid());
    }
    exit(0);
}

// Driver Function
int main()
{
	printf("Current process ID is: %d\n",getpid());
	/* signal() system call */
    signal(SIGINT,handler);
    /* This keeps on running until Ctrl + C is pressed on the keyboard or until signal is received */
	while(1){
        printf("Waiting for interrupt...\n");
        sleep(1);
    }
    return 0;
}
