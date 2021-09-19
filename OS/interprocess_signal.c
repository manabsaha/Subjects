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
