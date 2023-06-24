#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct process
{
    char name[50];
    int arrivalTime;
    int burstTime;
    int turnaroundTime;
    int waitingTime;
    int completeTime;
} process;

int main()
{
    // Taking process number
    int processesNumber;
    printf("Enter the number of processes: ");
    scanf("%d", &processesNumber);

    // allocating memory for storing processes
    process *processes = (process *)calloc(processesNumber, sizeof(process));

    // Taking processes input
    for (int i = 0; i < processesNumber; i++)
    {
        fflush(stdin);
        printf("Enter the name of process %d: ", i + 1);
        fgets((processes + i)->name, sizeof((processes + i)->name), stdin);
        (processes + i)->name[(strlen((processes + i)->name) - 1)] = '\0'; // removing newline part at end of this string
        printf("Enter the arrival time of the process: ");
        scanf("%d", &(processes + i)->arrivalTime);
        printf("Enter the cpu burst time of the process: ");
        scanf("%d", &(processes + i)->burstTime);
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

    int totalWaitingTime = 0, totalTurnaroundTime = 0;
    // printing the table;
    printf("_________________________________________________________________________________________________________________\n");
    printf("|Processes\t\t|Arrival Time\t\t|Burst Time\t\t|Turnaround Time\t|Waiting Time\t|\n");
    printf("|_______________________|_______________________|_______________________|_______________________|_______________|\n");
    for (int i = 0; i < processesNumber; i++)
    {
        totalTurnaroundTime += (processes + i)->turnaroundTime;
        totalWaitingTime += (processes + i)->waitingTime;
        printf("|%s\t\t\t|%d\t\t\t|%d\t\t\t|%d\t\t\t|%d\t\t|\n", (processes + i)->name, (processes + i)->arrivalTime, (processes + i)->burstTime, (processes + i)->turnaroundTime, (processes + i)->waitingTime);
    }
    printf("|_______________________|_______________________|_______________________|_______________________|_______________|\n");
    // printing the average.
    printf("Average Waiting Time: %0.3f\n", (float)totalWaitingTime / processesNumber);
    printf("Average Turnaround Time: %0.3f\n", (float)totalTurnaroundTime / processesNumber);
}