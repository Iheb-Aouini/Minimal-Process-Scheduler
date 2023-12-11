#include<stdio.h>
#include<stdlib.h>
#include"../Data.h"
#include "../Process.h"

int NP, quantum, scheduler[1000];
unsigned int time1 = 0;
struct Process_array process_list;
rr R; 
int Te_restant[100];
typedef struct el
{
	unsigned int p;
	struct el * next;
}Q;
Q * qeue = NULL;

void addToQeue(int i)
{
	Q *n, *n1;
	n = (Q *)malloc(sizeof(Q));
	n->next = NULL;
	n->p = i;
	if(qeue == NULL)
	{
		
		qeue = n;
	}
	else
	{
		for(n1 = qeue ; n1->next!=NULL; n1=n1->next);
		n1 -> next = n;
	}
}
void addArrivedProcessesToQeue()
{
	int i;
	for(i=0; i<NP; i++)
	{
		if(process_list.proc[i].Arrival_time == time1)
		{
			addToQeue(i);
		}
	}
}
unsigned int getNextProcess()
{
	Q *n;
	int x;
	if(qeue == NULL)
	{
		return -1;
	}
	else
	{
		x = qeue -> p;
		n = qeue;
		qeue = qeue -> next;
		free(n);
		return x;
	}
}

int main(int argc, char *argv[])
{
        printf("\nThe Quantum: ");
	scanf("%d", &quantum);
	process_list=extract_process_list(argv[1]);
	NP = process_list.size;
	R.size=-1;
	int Ncomplet=0;
	for (int i = 0; i < NP; i++) //initialization of Te_restant
	  {
    		Te_restant[i] = process_list.proc[i].Burst_time;
  	  }

	unsigned int np, q, i;
	q = 0;
	addArrivedProcessesToQeue();
	while(Ncomplet!=NP)
	{
		np = getNextProcess();
		if(np == -1)
		{
		
			scheduler[time1] = -1;
			time1++;
			addArrivedProcessesToQeue();
		}
		else
		{
			q = quantum;
	      R.size=R.size+1;
	      R.tab[R.size].pos = np;
	      R.tab[R.size].deb = time;

			if(Te_restant[np] < q)
			{
				q = Te_restant[np];
			}
			
			for(i = q; i>0; i--)
			{
				scheduler[time1]=np;
				time1++;
				Te_restant[np]--;
				addArrivedProcessesToQeue();
			}
		        R.tab[R.size].fin = time1;
			if(Te_restant[np] > 0)
			{
				addToQeue(np);
			}
			else { process_list.proc[np].Response_time=time1;
			Ncomplet++;}
		}
		
	}
	puts("\t+-----+-------------+------------+---------------+");
	puts("\t|Name | Arrival Date| Burst Time | Response Time |");
puts("\t+-----+-------------+------------+---------------+");
	for (int i = 0; i < process_list.size; i++) {
      printf("\t| %3s |     %3d     |     %3d     |      %3d     |\n",
			process_list.proc[i].Name ,process_list.proc[i].Arrival_time,process_list.proc[i].Burst_time, process_list.proc[i].Response_time);

puts("\t+-----+-------------+------------+---------------+");
	}

	gantt_chart_preemptif(process_list.proc, process_list.size, R);
}
