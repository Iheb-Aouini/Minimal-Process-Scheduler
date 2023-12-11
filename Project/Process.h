
#ifndef PROCESS_H  
#define PROCESS_H

struct Process {
    char Name[10];  
	int Arrival_time,Burst_time,Priority,Response_time;
    int Waiting_time; 
    int key;
    int pid;
    int completed;
    int temAttente;
};


 struct Process_array
{
    struct Process *proc; 
    int size; 
    };
    


#endif 

