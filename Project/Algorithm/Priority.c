#include <stdio.h>
#include <string.h>
#include "../Data.h"
#include "../Process.h"
#include "../Gui.h"

int main(int argc, char *argv[])
{

	struct Process_array process_list = extract_process_list(argv[1]);
	int sizeof_process_array = process_list.size;
	struct Process p;
	int i, j, T[50], k;

	for (i = 0; i < sizeof_process_array; i++)
	{
		for (j = i + 1; j < sizeof_process_array; j++)
		{
			if (process_list.proc[i].Arrival_time > process_list.proc[j].Arrival_time)
			{
				p = process_list.proc[i];
				process_list.proc[i] = process_list.proc[j];
				process_list.proc[j] = p;
			}
		}
		process_list.proc[i].completed = 0; 
	}
	int debut = process_list.proc[0].Arrival_time;
	int Ncomplet = sizeof_process_array;
	int pos;
	while (Ncomplet != 0)
	{
		j = -1;
		for (i = 0; i < sizeof_process_array; i++)
		{
			if (process_list.proc[i].Arrival_time <= debut && process_list.proc[i].completed == 0)
			{
				j++;
				T[j] = i;
			}
		}
		if (j != -1)
		{
			for (i = 0; i <= j; i++) 
			{
				for (k = i + 1; k <= j; k++)
				{
					if (process_list.proc[T[i]].Priority < process_list.proc[T[k]].Priority)
					{
						pos = T[i];
						T[i] = T[k];
						T[k] = pos;
					}
				}
			}

			process_list.proc[T[0]].completed = 1;
			Ncomplet = Ncomplet - 1;
			debut = debut + process_list.proc[T[0]].Burst_time;
			process_list.proc[T[0]].Response_time = debut;
		}

		else
		{
			debut++;
		}
	}

	for (i = 0; i < sizeof_process_array; i++) 
	{
		for (j = i + 1; j < sizeof_process_array; j++)
		{
			if (process_list.proc[i].Response_time > process_list.proc[j].Response_time)
			{
				p = process_list.proc[i];
				process_list.proc[i] = process_list.proc[j];
				process_list.proc[j] = p;
			}
		}
	}
	printf("\nsize :%d", sizeof_process_array);
	printf("\n\n\n");

	puts("\t+-----+-------------+------------+---------------+---------------+");
	puts("\t| Name| Arrival Date| Burst Time |    Priority   | Response Time |");
	puts("\t+-----+-------------+------------+---------------+---------------+");
	for (int i = 0; i < sizeof_process_array; i++)
	{
		printf("\t| %3s |     %3d     |     %3d    |      %3d      |      %3d      |\n",
			   process_list.proc[i].Name, process_list.proc[i].Arrival_time, process_list.proc[i].Burst_time, process_list.proc[i].Priority, process_list.proc[i].Response_time);

		puts("\t+-----+-------------+------------+---------------+---------------+");
	}

	gantt_chart_non_preemptif(process_list.proc, sizeof_process_array);
			
	char message[150]="\n Algorithm Policy : Priority \n \n Processes list and Metrics : \n"	;


	open_gtk_IHM(process_list,message);
}
