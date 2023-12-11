#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Process.h"
#include "../Data.h"

int main(int argc, char *argv[])
{

	struct Process_array process_list = extract_process_list(argv[1]);
	int k = 0;
	printf("Enter the quantum : ");

	scanf("%d", &k);
	printf("\n");
	PRIP(process_list.proc, process_list.size, k);

}
void PRIP(struct Process tab[], int m, int qu)
{

	printf("\n");
	float Waiting_time = 0;
	float Response_time = 0;
	int r = 0, u = 0, Priority, x, y;
	int v = 0;
	int n = 0;
	int k = 0;
	char ch1[50];
	char ch2[100];
	char ch3[100];
	struct Process aux;
	struct Process tab2[50];
	struct Process tab3[50];

	for (int h = 0; h < m; h++)
	{
		tab2[h] = tab[h];
	}
	for (int o = 0; o < m - 1; o++)
	{
		for (int h = o + 1; h < m; h++)
		{
			if (tab2[o].Priority < tab2[h].Priority)
			{
				aux = tab2[h];
				tab2[h] = tab2[o];
				tab2[o] = aux;
			}
		}
	}

	for (int h = 0; h < m; h++)
	{
		tab3[h] = tab[h];
	}
	for (int o = 0; o < m - 1; o++)
	{
		for (int h = o + 1; h < m; h++)
		{
			if (tab3[o].Arrival_time > tab3[h].Arrival_time)
			{
				aux = tab3[h];
				tab3[h] = tab3[o];
				tab3[o] = aux;
			}
		}
	}
	strncpy(ch1, "", sizeof(ch1));
	int h = 0;
	int p = 0;
	int nb1 = 0;
	int time = 0;
	ch3[0] = 0;

	while (p != m)
	{
		while (tab2[h].Burst_time != 0)
		{

			if (tab2[h].Arrival_time <= time)
			{
				Waiting_time += time - tab2[h].Arrival_time;
				tab[h].Waiting_time += time - tab2[h].Arrival_time;
				time++;
				tab2[h].Burst_time--;
				if (tab2[h].Burst_time == 0)
				{
					for (int w = 0; w < m; w++)
					{
						if (tab3[w].pid == tab2[h].pid)
						{
							Response_time += time - tab3[w].Arrival_time;
							tab[w].Response_time += time - tab3[w].Arrival_time;

							break;
						}
					}
				}
				tab2[h].Arrival_time = time;
				ch1[r] = tab2[h].pid;
				x = tab2[h].pid;
				y = tab2[h].Priority;

				n = h;
				nb1 = 0;
				v = 0;

				k = 0;
				for (int c = 0; c < m; c++)
				{
					if ((tab2[c].Priority == y) && (tab2[c].Burst_time > 0))
					{
						v++;
					}
				}
				if (v > 1)
				{
					int g = 0;

					while (tab2[k].Priority >= y)
					{
						if ((tab2[k].Arrival_time <= time) && (tab2[k].Priority > y) && (tab2[k].Burst_time > 0))
							g++;
						if ((tab2[k].Arrival_time <= time) && (tab2[k].Priority == y))
							nb1++;
						k++;
					}
					if ((nb1 > 1) && (tab2[n].Burst_time > 0) && (g == 0))
					{

						y = qu - 1;

						if (tab2[n].Burst_time >= y)
						{

							for (int j = 0; j < y; j++)
							{
								r++;
								ch1[r] = tab2[n].pid;
								time++;
								tab2[n].Burst_time--;
								tab2[h].Arrival_time = time;
								u++;
							}
						}
						else
						{

							for (int j = 0; j < tab2[n].Burst_time; j++)
							{
								r++;
								u++;
								tab2[n].Burst_time--;
								ch1[r] = tab2[n].pid;
								time++;
							}
						}
					}
				}

				u++;

				p = 0;
				r++;
				h = 0;
				tab2[n].Arrival_time++;
				for (int o = 0; o < m - 1; o++)
				{
					for (int cn = o + 1; cn < m; cn++)
					{
						if ((tab2[o].Priority == tab2[cn].Priority))
						{
							if (tab2[o].Arrival_time > tab2[cn].Arrival_time)
							{
								aux = tab2[cn];
								tab2[cn] = tab2[o];
								tab2[o] = aux;
							}
						}
					}
				}

				for (int c = 0; c < m; c++)
				{
					if (tab2[c].pid == x)
					{
						tab2[c].Arrival_time--;
					}
				}
			}
			else
			{
				int nb = 0;
				for (int f = 0; f < m; f++)
				{
					if ((tab2[f].Arrival_time <= time) && (tab2[f].Burst_time > 0))
					{
						nb++;
					}
				}
				if (nb == 0)
				{
					for (int f = 0; f < m; f++)
					{
						if (tab3[f].Arrival_time > time)
						{
							while (tab3[f].Arrival_time > time)
							{
								time++;
								ch1[r] = 0;

								r++;
								u++;
							}
							h = 0;
							p = 0;
							break;
						}
					}
				}

				else
				{

					h++;
					if (h == m)
						h = 0;
				}
			}
		}
		h++;
		if (h == m)
			h = 0;

		p++;
	}
	int s = 0;
	h = 0;
	while (h < u)
	{

		if (ch1[h] == ch1[h + 1])
		{
			h++;
		}
		else
		{

			ch2[s] = ch1[h];
			ch3[s + 1] = h + 1;
			s++;
			h++;
		}
	}

	puts("\t+-----+-------------+------------+---------------+");
	puts("\t| Name| Arrival Date| Burst Time |    Priority   |");
	puts("\t+-----+-------------+------------+---------------+");
	
	for (int i = 0; i < m; i++)
	{
		printf("\t| %3s |     %3d     |     %3d    |      %3d     |\n",
			   tab[i].Name, tab[i].Arrival_time, tab[i].Burst_time, tab[i].Priority);

		puts("\t+-----+-------------+------------+---------------+");
	}


	printf("\nChosen Quantum is : %d \n",qu);
	printf("\n NB : IDLE means that the cpu has no processes to execute in a particular time \n \n");


	Affichage_dessus("Multilevel ", r);

	for (int h = 0; h < s; h++)
	{
		if (ch2[h] == 0)
			printf(" IDLE ");
		else
			printf("   p %d", ch2[h]);
		printf("\t");
	}

	printf("\n");
	printf("\n");
	printf("\t");
	for (int h = 0; h <= s; h++)
	{
		printf("%d ", ch3[h]);
		printf("\t");
	}
	Affichage_dessous(s);

	Tam_Trm(Waiting_time, Response_time, m);








}
