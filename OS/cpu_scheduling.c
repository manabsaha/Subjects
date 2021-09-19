/*ASSIGNMENT 2 - OS LAB
@CSM20012
Recommended to view the output in full screen, else some of the result gets omitted due to length of the window. */

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
