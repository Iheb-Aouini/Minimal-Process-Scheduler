#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
#include "../Data.h"
#include "../Process.h"


rr findWaitingTime(struct Process proc[], int n, int Waiting_time[])
{
	rr R;
	R.size = -1;
	int rt[n];
	R.date_debut = proc[0].Arrival_time;

	
	for (int i = 0; i < n; i++)
	{
		rt[i] = proc[i].Burst_time;
		if (proc[i].Arrival_time < R.date_debut)
		{
			R.date_debut = proc[i].Arrival_time;
		}
	}

	int complete = 0, t = 0, minm = INT_MAX;
	int shortest = 0, finish_time;
	bool check = false;


	while (complete != n)
	{


		for (int j = 0; j < n; j++)
		{
			if ((proc[j].Arrival_time <= t) && (rt[j] < minm) && rt[j] > 0)
			{
				minm = rt[j];
				shortest = j;
				check = true;
			}
		}

		if (check == false)
		{
			t++;
			continue;
		}
		else
		{
	
			rt[shortest]--;

			R.size = R.size + 1;
			R.tab[R.size].pos = shortest;
			R.tab[R.size].deb = t;
			R.tab[R.size].fin = t + 1;
		
			minm = rt[shortest];
			if (minm == 0)
				minm = INT_MAX;

		
			if (rt[shortest] == 0)
			{

			
				complete++;
				check = false;

			
				finish_time = t + 1;

			
				Waiting_time[shortest] = finish_time - proc[shortest].Burst_time - proc[shortest].Arrival_time;

				if (Waiting_time[shortest] < 0)
					Waiting_time[shortest] = 0;
			}
	
			t++;
		}
	}
	return R;
}


void findTurnAroundTime(struct Process proc[], int n, int Waiting_time[], int tat[])
{

	for (int i = 0; i < n; i++)
		tat[i] = proc[i].Burst_time + Waiting_time[i];
}

void findavgTime(struct Process proc[], int n)
{
	int Waiting_time[n], tat[n];
	rr r = findWaitingTime(proc, n, Waiting_time);
	findTurnAroundTime(proc, n, Waiting_time, tat);
	puts("\t+-----+-------------+------------+---------------+---------------+");
	puts("\t|Name | Arrival Date| Burst Time | Waiting Time  | Response Time |");
	puts("\t+-----+-------------+------------+---------------+---------------+");
	for (int i = 0; i < n; i++)
	{
		printf("\t| %3s |     %3d     |     %3d    |      %3d      |      %3d      |\n",
			   proc[i].Name, proc[i].Arrival_time, proc[i].Burst_time, Waiting_time[i], tat[i] + proc[i].Arrival_time);

		puts("\t+-----+-------------+------------+---------------+---------------+");
	}

	gantt_chart_preemptif(proc, n, r);
}


int main(int argc, char *argv[])
{
	struct Process_array p1 = extract_process_list(argv[1]);
	findavgTime(p1.proc, p1.size);
	return 0;
}
