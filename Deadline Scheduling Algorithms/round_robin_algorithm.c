#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct process
{
    char name[50];
    int id;
    int arrivalTime;
    int burstTime;
    int turnaroundTime;
    int waitingTime;
    int completeTime;
    int remainingTime;
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
    queueIndex--;
    return id;
}

int main()
{
    // Taking process number
    int processesNumber, quantumTime, currentTime = 0, numberOfProcessesPushed = 0;
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
        (processes + i)->name[(strlen((processes + i)->name) - 1)] = '\0'; // removing newline part at end of this string
        printf("Enter the arrival time of the process: ");
        scanf("%d", &(processes + i)->arrivalTime);
        printf("Enter the cpu burst time of the process: ");
        scanf("%d", &(processes + i)->burstTime);
        (processes + i)->id = i + 1;
        (processes + i)->remainingTime = (processes + i)->burstTime;
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

    // getting the minimum time which is the time of the first process as the processes are now arranged on the basis of the arrival time.
    int arrivalTimeToGetPushedToReadyQueue = processes->arrivalTime;
    int previousArrivalTimeLimit = -1; // just negative to match the condition for below condition check in case the first arrival time is 0.

    process *currentProcess = NULL; // process to run
    int currentId;                  // variable to store the id of the elemnent in the first of queue
    // looping until all the process is completed
    while (completedProcessCount != processesNumber)
    {
        // pushing the arrived process to the ready queue
        for (int i = 0; i < processesNumber; i++)
        {
            if ((processes + i)->arrivalTime <= arrivalTimeToGetPushedToReadyQueue && (processes + i)->arrivalTime > previousArrivalTimeLimit)
            {
                addToReadyQueue((processes + i)->id);
            }
        }
        // after adding the process
        if (currentProcess != NULL)
        {
            if (currentProcess->remainingTime != 0)
                addToReadyQueue(currentId);
        }
        previousArrivalTimeLimit = arrivalTimeToGetPushedToReadyQueue;

        // poping out the first process id
        currentId = shiftReadyQueue();
        // selecting the process with this id
        for (int i = 0; i < processesNumber; i++)
        {
            if ((processes + i)->id == currentId)
            {
                currentProcess = (processes + i);
                break;
            }
        }
        if (currentProcess->remainingTime > quantumTime)
        {
            arrivalTimeToGetPushedToReadyQueue += quantumTime;
            currentProcess->remainingTime -= quantumTime;
        }
        else
        {
            arrivalTimeToGetPushedToReadyQueue += currentProcess->remainingTime;
            currentProcess->remainingTime = 0;
            currentProcess->completeTime = arrivalTimeToGetPushedToReadyQueue;
            completedProcessCount++;
        }
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