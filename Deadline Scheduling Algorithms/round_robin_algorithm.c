#include <stdio.h>
#include <stdlib.h>

typedef struct process
{
    char name[50];
    int id;
    int arrivalTime;
    int burstTime;
    int turnaroundTime;
    int waitingTime;
    int completeTime;
} process;

// global variables
int queueIndex = 0;
int *readyQueue;
int completedProcessCount = 0;

void addToReadyQueue(int id)
{
    *(readyQueue + queueIndex) = id;
    queueIndex++;
}

int shiftReadyQueue()
{
    int id = *readyQueue;
    for (int i = 0; i < queueIndex; i++)
    {
        *(readyQueue + i) = *(readyQueue + i + 1);
    }
}

int main()
{
    // Taking process number
    int processesNumber, quantumTime, currentTime = 0;
    printf("Enter the number of processes: ");
    scanf("%d", &processesNumber);
    printf("Enter the Quantum Time for each process: ");
    scanf("%d", &quantumTime);

    // allocating the maximum size of the ready queue
    readyQueue = calloc(processesNumber, sizeof(int));

    // allocating memory for storing processes
    process *processes = (process *)calloc(processesNumber, sizeof(process));

    // Taking processes input
    for (int i = 0; i < processesNumber; i++)
    {
        fflush(stdin);
        printf("Enter the name of process %d: ", i + 1);
        fgets((processes + i)->name, sizeof((processes + i)->name), stdin);
        printf("Enter the arrival time of the process: ");
        scanf("%d", &(processes + i)->arrivalTime);
        printf("Enter the cpu burst time of the process: ");
        scanf("%d", &(processes + i)->burstTime);
        processes->id = i + 1;
    }

    // arranging the process in ascending order on the basis of the arrival time.

    for (int i = 0; i < processesNumber; i++)
    {
        for (int j = i; j < processesNumber; j++)
        {
            if ((processes + i)->arrivalTime > (processes + j)->arrivalTime)
            {
                process temp;
                temp = *(processes + i);
                *(processes + i) = *(processes + j);
                *(processes + j) = temp;
            }
        }
    }

    int completetimeTrack = 0;
    // calculating complete time of each process
    for (int i = 0; i < processesNumber; i++)
    {
        completetimeTrack += (processes + i)->burstTime;
        (processes + i)->completeTime = completetimeTrack;
    }

    // calculating the turnaroundtime and waiting time

    for (int i = 0; i < processesNumber; i++)
    {
        (processes + i)->turnaroundTime = (processes + i)->completeTime - (processes + i)->arrivalTime;
        (processes + i)->waitingTime = (processes + i)->turnaroundTime - (processes + i)->burstTime;
    }

    // printing the table;
    printf("Processes\t\tArrival Time\t\tBurst Time\t\tTurnaround Time\t\tWaiting Time\n");
    for (int i = 0; i < processesNumber; i++)
    {
        printf("%s\t\t\t%d\t\t\t%d\t\t\t%d\t\t\t%d\n", (processes + i)->name, (processes + i)->arrivalTime, (processes + i)->burstTime, (processes + i)->turnaroundTime, (processes + i)->waitingTime);
    }
}