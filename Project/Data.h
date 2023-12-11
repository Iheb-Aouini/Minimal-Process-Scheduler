#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Process.h"






struct Process *generate_random_processes(int number_of_processes){
    int process_priority_min;
    int process_priority_max;
    int process_arrival_time_min;
    int process_arrival_time_max;
    int process_execution_time_min;
    int process_execution_time_max;


    printf("** Required range of process arrival time ** \n");
    printf("Enter the minimum value of process arrival time \n");
    scanf("%d",&process_arrival_time_min);
    printf("Enter the maximum value of process' arrival time \n");
    scanf("%d",&process_arrival_time_max);

 
    printf("** Required the range of process execution time ** \n");
    printf("Enter the minimum value of process execution time \n");
    scanf("%d",&process_execution_time_min);
    printf("Enter the maximum value of process execution time \n");
    scanf("%d",&process_execution_time_max);


    printf("** Required the range of process priority ** \n");
    printf("Enter the minimum value of process priority \n");
    scanf("%d",&process_priority_min);
    printf("Enter the maximum value of process priority \n");
    scanf("%d",&process_priority_max);

    struct Process *processes_list = (struct Process*)malloc(number_of_processes * sizeof(struct Process));
    srand(time(0)); 
    char process_name_temp[6];
    for (int i=0;i<number_of_processes;i++){
    snprintf(process_name_temp, sizeof(process_name_temp), "P%d", i+1); 
    strcpy(processes_list[i].Name, process_name_temp);

    processes_list[i].Arrival_time= (rand() % (process_arrival_time_max - process_arrival_time_min + 1)) + process_arrival_time_min;

    processes_list[i].Burst_time= (rand() % (process_execution_time_max - process_execution_time_min + 1)) + process_execution_time_min;

    processes_list[i].Priority= (rand() % (process_priority_max - process_priority_min + 1)) + process_priority_min;

    processes_list[i].pid=i+1;
    }
    return processes_list;

}


void print_processes_list(struct Process *processes_list,int number_of_processes){
        for (int i=0;i<number_of_processes;i++){
            printf("Name : %s , Arrival time : %d , Execution time : %d , Priority : %d , PID : %d \n",processes_list[i].Name,processes_list[i].Arrival_time, processes_list[i].Burst_time , processes_list[i].Priority,processes_list[i].pid);
        }  
}



void save_processes_list_file(struct Process *processes_list,int number_of_processes){
    FILE *processes_file;
    processes_file = fopen("processes_list.txt","w");
    printf("test");

    if (processes_file == NULL) {
        printf("Error opening the file.\n");
        exit(1);
    }    

      for (int i=0;i<number_of_processes;i++){
          fprintf(processes_file,"Name : %s , Arrival time : %d , Execution time : %d , Priority : %d , PID : %d \n",processes_list[i].Name,processes_list[i].Arrival_time, processes_list[i].Burst_time , processes_list[i].Priority,processes_list[i].pid);
        }  
    fclose(processes_file);


}  


















struct Process_array extract_process_list(char input_file[20]){
  

    FILE *processes_list_file = fopen("processes_list.txt", "r");

    if (processes_list_file == NULL) {
        fprintf(stderr, "Error opening the file.\n");
        exit(1);
    }

     char line[150];
     int processes_count = 0;
        
   
    char n[50];
    int a, e, p, d;


        while (fgets(line, sizeof(line), processes_list_file) != NULL) {
      
        if (sscanf(line, "Name : %s , Arrival time : %d , Execution time : %d , Priority : %d , PID : %d",
                   n, &a, &e, &p, &d) == 5) {
            processes_count++;
        }
        }


    rewind(processes_list_file); 

    struct Process *processes_list = (struct Process*)malloc(processes_count * sizeof(struct Process));
      
 
    int i=0;
    while (fgets(line, sizeof(line), processes_list_file) != NULL) {
      
        if (sscanf(line, "Name : %s , Arrival time : %d , Execution time : %d , Priority : %d , PID : %d",
                   processes_list[i].Name,
                   &processes_list[i].Arrival_time,
                   &processes_list[i].Burst_time,
                   &processes_list[i].Priority,
                   &processes_list[i].pid) == 5){
                    i++;
                   }
                   }

    fclose(processes_list_file);
    
    struct Process_array process_array;
    process_array.proc=processes_list;
    process_array.size=processes_count;
    return process_array;
}







        
  
void gantt_chart_non_preemptif(struct Process *p, int len)
{
	int i, j;

	printf("\n\t GANTT Diagram \n\n");
	
	printf("\t ");


	for (i = 0; i < len; i++)
	{
		for (j = 0; j < p[i].Burst_time; j++)
			printf("--");

		printf(" ");
	}

	printf("\n\t|");


	for (i = 0; i < len; i++)
	{
		for (j = 0; j < p[i].Burst_time - 1; j++)
			printf(" ");

		printf("%s", p[i].Name);

		for (j = 0; j < p[i].Burst_time - 1; j++)
			printf(" ");

		printf("|");
	}

	printf("\n\t ");

	
	for (i = 0; i < len; i++)
	{
		for (j = 0; j < p[i].Burst_time; j++)
			printf("--");

		printf(" ");
	}

	printf("\n\t");

	
	
	printf("%d",p[0].Arrival_time);

	for (i = 0; i < len; i++)
	{
		for (j = 0; j < p[i].Burst_time; j++)
			printf("  ");
        if (p[i].Response_time > 9)
			printf("\b");

		printf("%d", p[i].Response_time);
		

	}

	printf("\n\n\n");
}




        

typedef struct
{
    int pos;
    int deb,fin;
    }Array;

typedef struct
{
    Array tab[50];
    int size;
    int date_debut;
    }rr; 



void gantt_chart_preemptif( struct Process *p, int len, rr r)
{
	printf("len  : %d , r.size : %d",len,r.size );
    int i, j;
    int s=r.size;

	printf("\n\t GANTT Diagram\n\n");
	
	printf("\t ");


        for (i = 0; i <= s; i++)
	{
		for (j = r.tab[i].deb ; j < r.tab[i].fin ; j++)

			printf("--");

		printf(" ");
	}

	printf("\n\t|");


	for (i = 0; i <= s; i++)
	{
		for (j = r.tab[i].deb ; j < r.tab[i].fin - 1; j++)
			printf(" ");

		printf("%s", p[r.tab[i].pos].Name);

		for (j = r.tab[i].deb; j < r.tab[i].fin - 1; j++)
			printf(" ");

		printf("|");
	}

	printf("\n\t ");

	
        for (i = 0; i <= s; i++)
	{
		for (j = r.tab[i].deb ; j < r.tab[i].fin ; j++)
			printf("--");

		printf(" ");
	}

	printf("\n\t");

	printf("%d",r.date_debut);

        for (i = 0; i <= s; i++)
	{
		for (j = r.tab[i].deb ; j < r.tab[i].fin ; j++)
			printf("  ");
        if (r.tab[i].fin > 9)
			printf("\b");

		printf("%d", r.tab[i].fin);		

	}
	

	printf("\n\n\n");
}









void Affichage_dessus(char x[20], int r)
{

    printf("\n\n");
	printf("\t");
    printf("\n");

	for (int h = 0; h < strlen(x); h++)
	{

		printf("%c", x[h]);
	}
	printf(":");

	printf("\n");
	printf("\t");
	

	printf("\n");
	printf("\n");
	printf("\t");
}

void Affichage_dessous(int r)
{
	printf("\n");
	printf("\n");

	printf("\t");
	for (int h = 0; h < r; h++)
	{
		if (h == r - 1)
			printf("|--------|");
		else
			printf("|-------");
	}

	printf("\n");
	printf("\n");
}

void Tam_Trm(float Waiting_time, float Response_time, int size)
{
    

	printf("\t");
	

	printf("\n \n");
	printf(" \t** Metrics of Multilevel Algorithm ** \n");

	printf(" \n-- Average wait time --  :%.2f \n", Waiting_time / size);

	printf("\n");
	printf("\t");
	printf(" \n-- Average turnaround time -- :%.2f \n", Response_time / size);

	printf("\n");


	printf("\n");
}



