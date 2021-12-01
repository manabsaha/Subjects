Assignment 1(a)
--------------
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

Assignment 1(b)
--------------
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

Assignment 1(c)
-------------
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/wait.h>
int main(){
	pid_t ret;
	int status;
	char *program;
	ret = fork();
	if(ret<0){
	printf("Fork failure\n");
	}
	else if(ret==0){
	printf("\nChild process\n");
	printf("Child process ID: %d\n",getpid());
	printf("Child process parent ID: %d\n",getppid());
	//calling another program
	char *argv[] = {"./divide",NULL};
	program = argv[0];
	printf("\nNew program name: %s\n",program);
	execv(argv[0],argv);
	}
	else{
	wait(&status);
	if(WIFEXITED(status)){
	printf("\nExit status of child: %d\n",status);
	}
	printf("\nParent process\n");
	printf("Process ID: %d\n",getpid());
	printf("Process parent ID: %d\n",getppid());
	}
	return 0;
}

Assignment 3(a)
-------------
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

Assignment 3(a modified)
------------
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

// Driver Function
int main()
{
    /* Getting the process ID to send signal to this process - Question 3(b) */
	printf("Current process ID is: %d\n",getpid());
    /* This keeps on running until signal is received from another process */
	while(1){
        printf("Waiting for signal from another processs...\n");
        sleep(1);
    }
    return 0;
}

Assignment 3(b)
-------------
#define _POSIX_SOURCE
#include<stdio.h>
#include <stdlib.h>
#include<signal.h>
#include<unistd.h>
#include<unistd.h>
#include<sys/types.h>

// Driver Function
int main()
{
	pid_t PROCESS_ID;   /* Stores the Process ID to send signal */
    int SIGNAL_NUM;    /* Stores the Signal Number */
    printf("Enter a Process ID: ");
    scanf("%d",&PROCESS_ID);
    printf("SIGHUP - 1 \n");   /* Hangup the process */
    printf("SIGINT - 2 \n");   /* Interrupt the process */
    printf("SIGQUIT - 3 \n");   /* Quit the process */
    printf("SIGILL - 4 \n");   /* Illegal instruction. */
    printf("SIGTRAP - 5 \n");   /* Trace trap. */
    printf("SIGABRT - 6 \n");   /* Abort. */
    printf("Enter a signal value: ");
    scanf("%d",&SIGNAL_NUM);
    /* Sending signal to another process */
    kill(PROCESS_ID,SIGNAL_NUM);
    return 0;
}

Assignment 3(c)
-------------
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

Assignment 4(a)
-------------
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

Assignment 5(a)
-------------
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
    int fd;

    /* FIFO file path */
    char *myfifo = "/tmp/myfifo";

    // Creating the named file(FIFO) using mkfifo(<pathname>, <permission>)
    mkfifo(myfifo, 0666); /* 0666 - Read Write Permission */

    /* Character array for storing the inputs of two programs */
	char str1[80], str2[80]; 

    while (1)
    {
        /* Opening FIFO in read mode */
        printf("\nWaiting for Program 2 to write... \n");
        fd = open(myfifo,O_RDONLY);
        
        /* Reading from FIFO */
		read(fd, str1, 80);

        /* Print the read string and sleep */
        printf("\nProgram 2: %s\n", str1);
        sleep(fd);
	
		/* Take a String from the user */
		printf("Input a string (Program 1):");
        fgets(str2, 80, stdin);
        
        /* Opening FIFO in write mode */
        fd = open(myfifo,O_WRONLY);
        
        /* Writing the string taken from user to FIFO and sleep */
        write(fd, str2, strlen(str2)+1);
        sleep(fd);
    }

    return 0;
}

Assignment 5(b)
-------------
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
    int fd;

    /* FIFO file path */
    char * myfifo = "/tmp/myfifo";

    /* Creating the named file(FIFO) using mkfifo(<pathname>,<permission>) */
    mkfifo(myfifo, 0666); /* 0666 - Read Write Permission */

	/* Character array for storing the inputs of two programs */
    char str1[80], str2[80];

    while (1)
    {
        /* Take a String from the user */
        printf("Input a string (Program 2):");
        fgets(str2, 80, stdin);

		/* Opening FIFO in write mode */
        fd = open(myfifo, O_WRONLY);

        /* Writing the string taken from user to FIFO and close */
        write(fd, str2, strlen(str2)+1);
        close(fd);

		/* Opening FIFO in read mode */
        printf("\nWaiting for Program 1 to write... \n");
        fd = open(myfifo, O_RDONLY);

        /* Reading from FIFO */
        read(fd, str1, sizeof(str1));

        /* Print the read string and close */
        printf("\nProgram 1: %s\n", str1);
        close(fd);
    }

    return 0;
}

Assignment 6(a_1)
-------------
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
int main()
{
    // ftok to generate unique key
    key_t key = ftok("shmfile",65);

    // shmget returns an identifier in shmid
    int shmid = shmget(key,1024,0666|IPC_CREAT);

    // shmat to attach to shared memory
    char *str = (char*) shmat(shmid,(void*)0,0);

    printf("Enter the string: ");
    fgets(str,100,stdin);

    printf("Data in the shared memory: %s\n",str);

    //detach from shared memory
    shmdt(str);

    return 0;
}

Assignment 6(a_2)
---------------
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>


int main()
{
	// ftok to generate unique key
	key_t key = ftok("shmfile",65);

	// shmget returns an identifier in shmid
	int shmid = shmget(key,1024,0666|IPC_CREAT);

	// shmat to attach to shared memory
	char *str = (char*) shmat(shmid,(void*)0,0);

	printf("Data read from memory: %s\n",str);

	//detach from shared memory
	shmdt(str);

	// destroy the shared memory
	shmctl(shmid,IPC_RMID,NULL);

	return 0;
}

Assignment 6(b)
-------------
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/times.h>
#include <time.h>

int main(){

    struct tms before,after;

     // Start recording time
    times(&before);

    /* Creating child processes and making them do dummy work to elapse time */
    pid_t pid;
    if((pid=fork())<0){
        printf("fork error\n");
    }
    else if(pid==0){
        printf("Wait for 20 sec: \n");
        long int i;
        for(i=0;i<100000;i++){
            printf("%ld \n",i);
        }
        exit(0);
    }
    else {
        wait(NULL);
    }

    // End recoding time
    times(&after);

    long double clktck=sysconf(_SC_CLK_TCK); //system clock tick

    /* Times are calculated. user time is real or wall clock time ,
    and system is cpu time minus i/o and wait times
    divided by system clock time time to get actual time in seconds
    instead of clock pulses */

    double user=(after.tms_utime-before.tms_utime)/(double)clktck;
    double system=(after.tms_stime-before.tms_stime)/(double)clktck;
    double cuser=(after.tms_cutime-before.tms_cutime)/(double)clktck;
    double csystem=(after.tms_cstime-before.tms_cstime)/(double)clktck;

    FILE *fptr;
    fptr = fopen("output.txt","w"); //accessing file in write mode

    if(fptr == NULL){
    printf("File Error!");
    exit(1);
    }

    //writing to file.
    fprintf(fptr,"Parent USER time: %lfs \n",user);
    fprintf(fptr,"Parent SYSTEM time: %lfs \n",system);
    fprintf(fptr,"Child USER time : %lfs \n",cuser);
    fprintf(fptr,"Child SYSTEM time: %lfs \n",csystem);
    printf("Output written in the file SUCESSFULLY!!\n");

    return 0;
}


Assignment 11(server)
------------------
// C Program for Message Queue (Writer Process)
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#define MAX 100

// structure for message queue
struct mesg_buffer {
	long mesg_type;
	char mesg_text[100];
} message;

int main()
{
	key_t key;
	int msgid;

	// ftok to generate unique key
	key = ftok("progfile", 65);

	// msgget creates a message queue and returns identifier
	msgid = msgget(key, 0666 | IPC_CREAT);
	message.mesg_type = 1;

	// printing the message queue ID
	printf("Message Queue ID is: %d \n", msgid);

	// Taking message as input
	printf("Enter the message: ");
	fgets(message.mesg_text, MAX, stdin);

	// msgsnd to send message
	msgsnd(msgid, &message, sizeof(message), 0);

	// Displaying the sent message
	printf("Sent data to client: %s \n", message.mesg_text);

	return 0;
}

Assignment 11(client)
------------------
// C Program for Message Queue (Reader Process)
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>

// structure for message queue
struct mesg_buffer {
	long mesg_type;
	char mesg_text[100];
} message;

int main()
{
	key_t key;
	int msgid;

	// ftok to generate unique key
	key = ftok("progfile", 65);

	// msgget creates a message queue and returns identifier
	msgid = msgget(key, 0666 | IPC_CREAT);

	// Printing the message queue ID
	printf("Message Queue ID is: %d \n", msgid);

	// msgrcv to receive message
	msgrcv(msgid, &message, sizeof(message), 1, 0);

	// Displaying the message
	printf("Data Received from server : %s \n", message.mesg_text);

	// Removing the message queue
	printf("Removing the queue. \n");
	msgctl(msgid, IPC_RMID, NULL);

	return 0;
}

Assignment 2(a)
--------------
#include<stdio.h>
#include<stdlib.h>

/* Question 2(a) - LJF */
void longest_job_first(int at[], int bt[], int process)
{
	printf("\n**** LONGEST JOB FIRST ALGORITHM ****\n");
	int temp[100];
	int y=process,largest=99,i;
	int count = 0,time,waiting=0,turnaround=0,end;
	float avg_wt,avg_tat;
	
	for(i=0;i<process;i++){
		temp[i] = bt[i];
	}
	
	temp[largest] = -1;
	
	printf("\nGannt Chart:\n");
	for(time=0; count!=process; ){
		largest = 99;
		for(i=0; i<process;i++){
			if(at[i]<=time && temp[i]>temp[largest] && temp[i]>0){
				largest = i;
			}
		}

		time+=temp[largest];
		printf("Process: %d - Current CPU Time: %d \n",largest+1,time);
		temp[largest] = 0;

		count++;
        waiting = waiting + time - at[largest] - bt[largest];
        turnaround = turnaround + time - at[largest];
	}
	
	avg_wt = waiting*1.0/process;
	avg_tat = turnaround*1.0/process;
    printf("\nAverage waiting time = %f \n",avg_wt);
    printf("Average Turnaround time = %f \n",avg_tat);
    return;
}

/* Question 2(a) - SRTF */
void srtf(int at[], int bt[], int process)
{
	printf("\n**** SRTF ALGORITHM ****\n");
	int temp[100];
	int waiting=0,turnaround=0;
    int i,smallest=99,count=0,time,n,end;
    float avg_wt,avg_tat;
    
	for(i=0; i<process; i++){
        temp[i]=bt[i];
	}

    printf("\nGantt Chart\n");
	
	temp[smallest]=9999;
	
	for(time=0; count!=process; time++){
        smallest=99;
        for(i=0; i<process; i++){
            if(at[i]<=time && temp[i]<temp[smallest] && temp[i]>0 )
                smallest=i;
        }
        
        temp[smallest]--;
        printf("Process: %d - Current CPU Time: %d \n",smallest+1,time+1);

        if(temp[smallest]==0){
            count++;
            end=time+1;
            waiting = waiting + end - at[smallest] - bt[smallest];
            turnaround = turnaround + end - at[smallest];
        }
    }

	avg_wt = waiting*1.0/process;
	avg_tat = turnaround*1.0/process;
    printf("\nAverage waiting time = %f \n",avg_wt);
    printf("Average Turnaround time = %f \n",avg_tat);
    return;
}

/* Question 2(b) - Round Robin */
void round_robin(int at[], int bt[], int process)
{
	printf("\n**** ROUND ROBIN ALGORITHM ****\n");
	int temp[100],y=process,i;
	int quant,waiting=0,sum=0,count=0,turnaround=0;
	float avg_wt, avg_tat; 
	for(i=0;i<process;i++){
		temp[i] = bt[i];
	}

	printf("Enter the Time Quantum for the process: ");  
	scanf("%d", &quant);  
	
	printf("\nGannt Chart:\n");
	
	sum = 0;
	i = 0;
	while(y!=0){
		if(temp[i] <= quant && temp[i] > 0){
		    sum = sum + temp[i];
		    temp[i] = 0;
		    count=1;
		    printf("Process: %d - Current CPU Time: %d \n",i+1,sum);
	    }
	    else if(temp[i] > 0){
	        temp[i] = temp[i] - quant;
	        sum = sum + quant;
	        printf("Process: %d - Current CPU Time: %d \n",i+1,sum);
	    }  
	    
	    if(temp[i]==0 && count==1){ 
	        y--;
	        waiting += sum-at[i]-bt[i];  
	        turnaround += sum-at[i];  
	        count =0;     
	    }  
	    
	    if(i==process-1){  
	        i=0;  
	    }  
	    else if(at[i+1]<=sum){
	        i++;  
	    }
	    else{  
	        i=0;  
	    }  
	}  
	  
	avg_wt = waiting * 1.0/process;
	avg_tat = turnaround * 1.0/process;
	printf("\nAverage Turn Around Time: %f \n", avg_wt);
	printf("Average Waiting Time: %f \n", avg_tat);
	return;
}

/* Question 2(c) - Priority (Non preemptive) */
void priority_non_preemptive(int at[], int bt[], int process)
{
	printf("\n**** PRIORITY ALGORITHM (Non Preemptive) ****\n");
	int priority[100];
	int i,count=0,highest=99,time;
	int waiting=0,turnaround=0;
	float avg_wt, avg_tat; 
	
	for(i=0;i<process;i++){
		printf("Enter priority of Process %d: ",i+1);
		scanf("%d",&priority[i]);
	}
	
	priority[highest] = -1;
	
	printf("\nGannt Chart:\n");
	
	for(time=0; count!=process; ){
		highest = 99;
		for(i=0; i<process; i++){
			if(at[i]<=time && priority[i]>priority[highest]){
				highest = i;
			}
		}

		time+=bt[highest];
		printf("Process: %d - Current CPU Time: %d \n",highest+1,time);
		priority[highest] = -1;

		count++;
        waiting += time - at[highest] - bt[highest];
        turnaround += time - at[highest];
	}

	avg_wt = waiting * 1.0/process;
	avg_tat = turnaround * 1.0/process;
	printf("\nAverage Turn Around Time: %f \n", avg_wt);
	printf("Average Waiting Time: %f \n", avg_tat);
	return;
}

/* Question 2(c) - Priority (Preemptive) */
void priority_preemptive(int at[], int bt[], int process)
{
	printf("\n**** PRIORITY ALGORITHM (Preemptive) ****\n");
	int priority[100],temp[100];
	int i,count=0,highest=99,time,end;
	int waiting=0,turnaround=0;
	float avg_wt, avg_tat; 
	
	for(i=0;i<process;i++){
		printf("Enter priority of Process %d: ",i+1);
		scanf("%d",&priority[i]);
		temp[i] = bt[i];
	}
	
	priority[highest] = -1;
	
	for(time=0; count!=process; time++){
		highest = 99;
		for(i=0; i<process; i++){
			if(at[i]<=time && priority[i]>priority[highest] && temp[i]>0){
				highest = i;
			}
		}

		temp[highest]--;
		printf("Process: %d - Current CPU Time: %d \n",highest+1,time+1);

		if(temp[highest]==0){
            count++;
            end=time+1;
            waiting += end - at[highest] - bt[highest];
            turnaround += end - at[highest];
        }
	}
	
	avg_wt = waiting * 1.0/process;
	avg_tat = turnaround * 1.0/process;
	printf("\nAverage Turn Around Time: %f \n", avg_wt);
	printf("Average Waiting Time: %f \n", avg_tat);
	return;
}

/* Driver Function */
int main()
{
    int num_of_process,i;
    int at[100], bt[100]; 
    int ch;
    int c;
    
	printf(" Total number of process in the system (Maximum 99): ");  
    scanf("%d", &num_of_process);
  
	//Enter the Arrival time and the Burst Time of the processes
	printf("Enter the Arrival Time and Burst Time\n");
	for(i=0;i<num_of_process;i++){  
		printf("PROCESS %d \n", i+1);  
		printf("Arrival time is: ");
		scanf("%d", &at[i]);
		printf("Burst time is: ");
		scanf("%d", &bt[i]);
	}

	//scheduling algorithms - choice
	while(1){
		printf("\n1. Longest Job First\n");
		printf("2. Shortest Remaining Time First\n");
		printf("3. Round Robin\n");
		printf("4. Priority (Non Preemptive)\n");
		printf("5. Priority (Preemptive)\n");
		printf("6. Exit\n");
		printf("Enter your choice: ");
		scanf("%d",&ch);
		switch(ch){
			case 1: longest_job_first(at,bt,num_of_process); break;
			case 2: srtf(at,bt,num_of_process); break;
			case 3: round_robin(at,bt,num_of_process); break;
			case 4: priority_non_preemptive(at,bt,num_of_process); break;
			case 5: priority_preemptive(at,bt,num_of_process); break;
			case 6: exit(0);
			default: printf("\nWrong Choice\n"); break;
		}
		printf("\n*************************\n");
		printf("Do you wish to try another algorithm? \nPress 1 to continue or any key to exit: ");
		scanf("%d",&c);
		if(c!=1){
			break;
		}
	}
	return 0;
}
-------------
