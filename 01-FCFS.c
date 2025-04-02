#include <stdio.h>

typedef struct fcfs
{
    int process; // Process Number
    int burst;   // Burst Time
    int arrival; // Arrival Time
    int tat;     // Turn Around Time
    int wt;      // Waiting Time
    int ct;      // Completion Time
} fcfs;

int sort(fcfs[], int);

int main()
{
    int n, i, temp = 0;
    float AvgTAT = 0, AvgWT = 0;

    printf("Enter Number of Processes: ");
    scanf("%d", &n);
    fcfs arr[n]; // Array of type fcfs

    for (i = 0; i < n; i++)
    {
        arr[i].process = i + 1;
        printf("Enter the P%d data\n", arr[i].process);
        printf("Enter Arrival Time: ");
        scanf("%d", &(arr[i].arrival));
        printf("Enter CPU Burst time: ");
        scanf("%d", &(arr[i].burst));
    }

    // Sorting the processes according to their arrival time
    sort(arr, n);

    printf("Process No\t Arrival Time\t Burst Time\t Completion Time\t Turn Around Time\t Waiting Time\n");
    for (i = 0; i < n; i++)
    {
        if (arr[i].arrival > temp)
        {
            temp = arr[i].arrival; // Handle idle time
        }
        temp += arr[i].burst;
        arr[i].ct = temp;
        arr[i].tat = arr[i].ct - arr[i].arrival;
        arr[i].wt = arr[i].tat - arr[i].burst;
        AvgTAT = AvgTAT + arr[i].tat;
        AvgWT = AvgWT + arr[i].wt;
        printf("%5d\t%16d\t%7d\t%17d\t%17d\t%16d\n",
               arr[i].process, arr[i].arrival, arr[i].burst,
               arr[i].ct, arr[i].tat, arr[i].wt);
    }

    printf("Average Turn Around Time: %.2f\nAverage Waiting Time: %.2f\n", AvgTAT / n, AvgWT / n);

    return 0;
}

// Bubble Sort (by arrival time)
int sort(fcfs arr[], int n)
{
    int i, j;
    fcfs k;

    for (i = 0; i < n - 1; i++)
    {
        for (j = i + 1; j < n; j++)
        {
            if (arr[i].arrival > arr[j].arrival)
            {
                k = arr[i];
                arr[i] = arr[j];
                arr[j] = k;
            }
        }
    }
    return 0;
}
