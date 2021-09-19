#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/wait.h>
int main(){
	pid_t ret;
	ret = fork();
	if(ret<0){
		printf("Fork failure\n");
	}
	else if(ret==0){
		printf("\nChild process\n");
		printf("Child process ID: %d\n",getpid());
		printf("Child process parent ID: %d\n",getppid());
		int a,b;
		printf("\nEnter the dividend: ");
		scanf("%d",&a);
		printf("\nEnter the divisor: ");
		scanf("%d",&b);
		if(b==0){
			printf("Divisor cannot be zero\n");
			exit(1);		
		}
		else{
			printf("\nThe result is: %d\n",a/b);
			exit(0);		
		}
	}
	else{
		wait(NULL);
		printf("\nParent process\n");
		printf("Process ID: %d\n",getpid());
		printf("Process parent ID: %d\n",getppid());
	}
	return 0;
}
