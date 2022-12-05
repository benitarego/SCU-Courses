#include <stdio.h>
#include "utility.h"
#include "process.h"
#include "stat.h"

void dispQueue(queue *q) {
	node * ptr = (node *)q->head;
				printf("<");
				while(ptr!=NULL) {
					printf("%c ",((process *) ptr->data)->pid);
					ptr = ptr->next;
				}
				printf(">\n");
}
int main(int argc,char **argv) {
	int counter = 0;
	//Run 5 times
	average_stats avg_fcfs[6],avg_sjf[6],avg_srf[6],avg_rr[6],avg_hpfp[6],avg_hpfnp[6],final[6];

	while (counter<5){
		//Generate Processes
		printf("*****************************************************************************************************************************\n");
		printf("Round %d\n",counter+1);
		printf("*****************************************************************************************************************************\n");

		linked_list * process_list = generate_processes(52);
		node * ptr = process_list->head;
		printf("-----------------------------------------------------------------------------------------------------------------------------\n");
		printf("Process ID | Arrival Time | Run Time | Priority |\n");
		printf("-----------------------------------------------------------------------------------------------------------------------------\n");
		while(ptr != NULL) {
			process *p = (process *)ptr->data;
			printf("%10c | %12.1f | %8.1f | %8d |\n",p->pid,p->arrival_time,p->run_time,p->priority);
			ptr = ptr->next;
		}
		printf("-----------------------------------------------------------------------------------------------------------------------------\n");
		printf("Total Number of Processes : %d\n",process_list->size);
		printf("-----------------------------------------------------------------------------------------------------------------------------\n");

		//Run FCFS
		avg_fcfs[counter] = first_come_first_serve_np(process_list);
		//Run SJF
		avg_sjf[counter] = shortest_job_first_np(process_list);
		//Run SRF
		avg_srf[counter] = shortest_remaining_time_p(process_list);
		//Run RR
		avg_rr[counter] = round_robin_p(process_list,5);
		//Run HPF P
		avg_hpfp[counter] = highest_priority_first_p(process_list);
		//Run HPF NP
		avg_hpfnp[counter] = highest_priority_first_np(process_list);
		//Run HPF P Aging
		//Run HPF NP Aging
		counter++;
	}
	// Initialiazing to 0 //
	for (int i = 0; i<6 ; i++)
	{
			final[i].avg_response_time = 0;
			final[i].avg_wait_time = 0;
			final[i].avg_turnaround = 0;
			final[i].avg_throughput = 0;
	}

	// adding average values received from all the rounds //
	for (int i = 0; i<5 ; i++)
	{
			final[0].avg_response_time += avg_fcfs[i].avg_response_time;
			final[1].avg_response_time += avg_sjf[i].avg_response_time;
			final[2].avg_response_time += avg_srf[i].avg_response_time;
			final[3].avg_response_time += avg_rr[i].avg_response_time;
			final[4].avg_response_time += avg_hpfp[i].avg_response_time;
			final[5].avg_response_time += avg_hpfnp[i].avg_response_time;

			final[0].avg_wait_time += avg_fcfs[i].avg_wait_time;
			final[1].avg_wait_time += avg_sjf[i].avg_wait_time;
			final[2].avg_wait_time += avg_srf[i].avg_wait_time;
			final[3].avg_wait_time += avg_rr[i].avg_wait_time;
			final[4].avg_wait_time += avg_hpfp[i].avg_wait_time;
			final[5].avg_wait_time += avg_hpfnp[i].avg_wait_time;

			final[0].avg_turnaround += avg_fcfs[i].avg_turnaround;
			final[1].avg_turnaround += avg_sjf[i].avg_turnaround;
			final[2].avg_turnaround += avg_srf[i].avg_turnaround;
			final[3].avg_turnaround += avg_rr[i].avg_turnaround;
			final[4].avg_turnaround += avg_hpfp[i].avg_turnaround;
			final[5].avg_turnaround += avg_hpfnp[i].avg_turnaround;

			final[0].avg_throughput += avg_fcfs[i].avg_throughput;
			final[1].avg_throughput += avg_sjf[i].avg_throughput;
			final[2].avg_throughput += avg_srf[i].avg_throughput;
			final[3].avg_throughput += avg_rr[i].avg_throughput;
			final[4].avg_throughput += avg_hpfp[i].avg_throughput;
			final[5].avg_throughput += avg_hpfnp[i].avg_throughput;
	}

	// calulating average values for all the algorithms //
	for (int i = 0; i<6 ; i++)
	{
			final[i].avg_response_time /= 5;
			final[i].avg_wait_time /= 5;
			final[i].avg_turnaround /= 5;
			final[i].avg_throughput /= 5;
	}

	//printing final statistics output //
	printf("*****************************************************************************************************************************\n");
	printf("*****************************************************************************************************************************\n");
	printf("\nThe average of the 5 runs of all algorithms is as follows:\n");
	printf("-----------------------------------------------------------------------------------------------------------------------------\n");
	printf("First Come First Serve:\n");
	printf("Average Response Time : %.1f\n",final[0].avg_response_time);
	printf("Average Wait Time : %.1f\n",final[0].avg_wait_time);
	printf("Average Turn Around Time :%.1f\n",final[0].avg_turnaround);
	printf("Average throughput :%.1f\n",final[0].avg_throughput);
	printf("-----------------------------------------------------------------------------------------------------------------------------\n");
	printf("Shortest Job First Non Preemptive:\n");
	printf("Average Response Time : %.1f\n",final[1].avg_response_time);
	printf("Average Wait Time : %.1f\n",final[1].avg_wait_time);
	printf("Average Turn Around Time :%.1f\n",final[1].avg_turnaround);
	printf("Average throughput :%.1f\n",final[1].avg_throughput);
	printf("-----------------------------------------------------------------------------------------------------------------------------\n");
	printf("Shortest Remaining Time First Preemptive:\n");
	printf("Average Response Time : %.1f\n",final[2].avg_response_time);
	printf("Average Wait Time : %.1f\n",final[2].avg_wait_time);
	printf("Average Turn Around Time :%.1f\n",final[2].avg_turnaround);
	printf("Average throughput :%.1f\n",final[2].avg_throughput);
	printf("-----------------------------------------------------------------------------------------------------------------------------\n");
	printf("Round Robbin Preemptive:\n");
	printf("Average Response Time : %.1f\n",final[3].avg_response_time);
	printf("Average Wait Time : %.1f\n",final[3].avg_wait_time);
	printf("Average Turn Around Time :%.1f\n",final[3].avg_turnaround);
	printf("Average throughput :%.1f\n",final[3].avg_throughput);
	printf("-----------------------------------------------------------------------------------------------------------------------------\n");
	printf("Highest Priority First Preemptive:\n");
	printf("Average Response Time : %.1f\n",final[4].avg_response_time);
	printf("Average Wait Time : %.1f\n",final[4].avg_wait_time);
	printf("Average Turn Around Time :%.1f\n",final[4].avg_turnaround);
	printf("Average throughput :%.1f\n",final[4].avg_throughput);
	printf("-----------------------------------------------------------------------------------------------------------------------------\n");
	printf("Highest Priority First Non Preemptive:\n");
	printf("Average Response Time : %.1f\n",final[5].avg_response_time);
	printf("Average Wait Time : %.1f\n",final[5].avg_wait_time);
	printf("Average Turn Around Time :%.1f\n",final[5].avg_turnaround);
	printf("Average throughput :%.1f\n",final[5].avg_throughput);
	printf("-----------------------------------------------------------------------------------------------------------------------------\n");
}
