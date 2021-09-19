#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<signal.h>

/* Signal handler function */
void handler(int num){
	/* File descriptor */
	int fd[2];
	/* Fail pipe */
	if(pipe(fd) == -1){
		printf("An error occured...!!");
		exit(0);
	}
	/* Creating a child process */
	int id = fork();
	/* Fail fork */
	if(id<0){
		printf("Failed fork \n");
	}
	/* Child process */
	else if(id==0){
		int n,term1 = 0, term2 = 1,next,i;
		pid_t c_id = getpid();
		pid_t p_id = getppid();
		/* Closing read */
		close(fd[0]);
		/* Writing child process id */
		write(fd[1],&c_id,sizeof(int));
		/* Writing parent process id */
		write(fd[1],&p_id,sizeof(int));
		printf("\nEnter the range (greater than 1):");
		scanf("%d",&n);
		/* Writing the range of fibonacci numbers */
		write(fd[1],&n,sizeof(int));
		/* Writing first two fibonacci numbers */
		write(fd[1],&term1,sizeof(int));
		write(fd[1],&term2,sizeof(int));
		/* For loop for generating rest of the series */
		for(i=2;i<n;i++){
		    next = term1+term2;
		    /* Writing the next number in the series */
		    write(fd[1],&next,sizeof(int));
		    term1 = term2;
		    term2 = next;
		}
		/* Closing write */
		close(fd[1]);
	}
	/* Parent process */
	else{
		/* Waiting for child */
		wait(NULL);
		/* Closing write */
		close(fd[1]);
		int data,range,i;
		/* Reading child process id */
		read(fd[0],&data,sizeof(int));
		printf("Child Process ID: %d \n",data);
		/* Reading parent process id */
		read(fd[0],&data,sizeof(int));
		printf("Parent Process ID: %d \n",data);
		/* Reading the range */
		read(fd[0],&range,sizeof(int));
		printf("Fibonacci Sequence of length %d \n",range);
		/* For loop for printing the series */
		for(i=0;i<range;i++){
			/* Reading items of the series */
		    read(fd[0],&data,sizeof(int));
		    printf("%d \t",data);
		}
		/* CLosing read */
		close(fd[0]);
	}
	/* exiting */
	exit(0);
}

int main(){
    printf("Press Ctrl+C to Interrupt \n");
    /* waiting for interrupt */
	signal(SIGINT,handler);
    while(1){
        continue;
    }
    return 0;
}
