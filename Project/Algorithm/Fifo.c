#include<stdio.h>
#include<string.h>
#include"../Data.h"
#include "../Process.h"
#include "../Gui.h"









int main(int argc, char *argv[])
{
	struct Process_array process_list=extract_process_list(argv[1]);

	int i,j;
	struct Process p;
	//ordering by Arrival Date (tri)
	for(i=0;i<process_list.size;i++)
	{
	for(j=i+1;j<process_list.size;j++)
		{
		if(process_list.proc[i].Arrival_time>process_list.proc[j].Arrival_time)
		{
			p=process_list.proc[i];
			process_list.proc[i]=process_list.proc[j];
			process_list.proc[j]=p;
		}
		}
	}//end tri

	

	process_list.proc[0].Response_time=process_list.proc[0].Arrival_time + process_list.proc[0].Burst_time;
	process_list.proc[0].Waiting_time=0;

	for(i=1;i<process_list.size;i++)
	{
	if(process_list.proc[i-1].Response_time>process_list.proc[i].Arrival_time)
	{
		process_list.proc[i].Response_time = process_list.proc[i-1].Response_time + process_list.proc[i].Burst_time;
		process_list.proc[i].Waiting_time=process_list.proc[i].Response_time - process_list.proc[i].Arrival_time - process_list.proc[i].Burst_time;
	}
	else
	{
		process_list.proc[i].Response_time=process_list.proc[i].Arrival_time + process_list.proc[i].Burst_time;
		process_list.proc[i].Waiting_time=0;
	}
	}
	//for (int i = 0; i < process_list.size; i++) {
	//	process_list.proc[i].Response_time=Response_times[i];}


		puts("\t+-----+-------------+------------+---------------+---------------+");
		puts("\t|Name | Arrival Date| Burst Time | Waiting Time  | Response Time |");
		puts("\t+-----+-------------+------------+---------------+---------------+");
		for (int i = 0; i < process_list.size; i++) {
		printf("\t| %3s |     %3d     |     %3d    |      %3d      |      %3d      |\n",
				process_list.proc[i].Name ,process_list.proc[i].Arrival_time,process_list.proc[i].Burst_time, process_list.proc[i].Waiting_time, process_list.proc[i].Response_time);

		puts("\t+-----+-------------+------------+---------------+---------------+");
		}

		gantt_chart_non_preemptif(process_list.proc, process_list.size);
		char message[150]="\n Algorithm Policy : Fifo \n \n Processes list and Metrics : \n"	;
		open_gtk_IHM(process_list,message);

}
