#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/wait.h>
int main(){
	pid_t ret;
	int stat;
	char *p;
	ret = fork();
	if(ret<0){
		printf("Fork failure\n");
	}
	else if(ret==0){			
		char *argv[] = {"./add",NULL};
		p = argv[0];
		printf("Program name: %s\n",p);
		execv(argv[0],argv);
	}
	else{
		wait(&stat);
		if(WIFEXITED(stat)){
			printf("Exit status %d\n",stat);		
		}
	}
	return 0;
}
