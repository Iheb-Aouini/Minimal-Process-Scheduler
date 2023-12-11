#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "./Data.h"

typedef struct
{
    char algorithm_name[50];
} Algo_Array;


int main(int argc, char *argv[])
{

    char input_algorithm_answer[20];
    bool trouve = false;
    Algo_Array algorithms_list[100];
    int n = 0;
    printf("\n");
    printf("\n                 ________________________________________________________\n");

    printf("\n                  Ｍｉｎｉｍａｌ Ｐｒｏｃｅｓｓ Ｓｃｈｅｄｕｌｅｒ Ｖ１.０	\n");
    printf("                 ________________________________________________________\n");

    char answer;
    printf("\n \nDo you want to generate a random process list [Y] , or keep the same process list [N]\n");
    scanf("%c", &answer);
    if (answer == 'Y')
    {
        int number_of_processes;
        // setting number of tasks
        printf("Enter the number of process you want to schedule \n");
        scanf("%d", &number_of_processes);
        struct Process *processes_list = generate_random_processes(number_of_processes);
        print_processes_list(processes_list, number_of_processes);
        save_processes_list_file(processes_list, number_of_processes);
        free(processes_list);
    }
    // Generate a dynamic menu

    system("ls Algorithm/ | sed 's/.c//g'> List.txt");

    FILE *f1 = fopen("List.txt", "r");
    if (f1 == NULL)
    {
        fputs("Error! file note found\n", stderr);
        return 0;
    }
    else
    {

        char line[250];
        char temp_algo_name[20];

        while (fgets(line, sizeof line, f1))
        {

            if (sscanf(line, "%s", temp_algo_name) == 1)
            {
                if (temp_algo_name[0] != '/' && temp_algo_name[1] != '/') // Comments Controls
                {
                    strcpy(algorithms_list[n].algorithm_name, temp_algo_name);
                    n++;
                }
            }
        }

        fclose(f1), f1 = NULL;

        puts("\n\n");
        puts("\t\t\t________________________________________");
        puts("\t\t\t   |       APPLICATION MENU       |   ");
        puts("\t\t\t________________________________________");
        for (int i = 0; i < n; i++)
        {
            printf("\t\t                         %s                  \n", algorithms_list[i].algorithm_name);

            puts("\t\t\t____________________________________");
        }
    }
    puts("\n\n");

    printf("\t\t      Please choose a Sceduling Algorithm: \n");
    scanf("%s", input_algorithm_answer);

    for (int k = 0; k < n; k++)
    {
        if (strcmp(algorithms_list[k].algorithm_name, input_algorithm_answer) == 0) // compare two strings if they are equal the function will return 0 
        {
            trouve = true;
            break;
        }
    }

    if (trouve == true)
    {
        printf("\n\n\n");
        char command[100] = "./Exe/";
        strcat(command, input_algorithm_answer); // par exemple ./Exe/Fifo
        strcat(command, " ");
        char process_list_file_name[50];
        strcpy(process_list_file_name, argv[1]);
        strcat(command, process_list_file_name);
        system(command);
    }
    // If the input (input_algorithm_answer ) is not found in the list , then execute by default Fifo
    else
    {
        char command[50] = "./Exe/Fifo ";
        char process_list_file_name[50];
        strcpy(process_list_file_name, argv[1]);
        strcat(command, process_list_file_name);
        system(command);
    }

    return 0;
}
