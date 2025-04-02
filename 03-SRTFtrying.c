#include <stdio.h>

typedef struct srtf
{
    int process;   // Process Number
    int burst;     // Burst Time
    int arrival;   // Arrival Time
    int remaining; // Remaining Time
    int tat;       // Turn Around Time
    int wt;        // Waiting Time
    int ct;        // Completion Time
} srtf;1

int sort(srtf[], int);

int main()
{
    int n, i, time = 0, completed = 0, shortest;
    float AvgTAT = 0, AvgWT = 0;

    printf("Enter Number of Processes: ");
    scanf("%d", &n);
    srtf arr[n];

    // Input processes with arrival and burst times
    for (i = 0; i < n; i++)
    {
        arr[i].process = i + 1;
        printf("Enter the P%d data\n", arr[i].process);
        printf("Enter Arrival Time: ");
        scanf("%d", &(arr[i].arrival));
        printf("Enter CPU Burst Time: ");
        scanf("%d", &(arr[i].burst));
        arr[i].remaining = arr[i].burst; // Initialize remaining time
    }

    // Sorting the processes according to their arrival time
    sort(arr, n);

    printf("Process No\t Arrival Time\t Burst Time\t Completion Time\t Turn Around Time\t Waiting Time\n");

    // SRTF Scheduling Loop
    while (completed != n)
    {
        shortest = -1;
        // Find the process with shortest remaining time that has arrived
        for (i = 0; i < n; i++)
        {
            if (arr[i].arrival <= time && arr[i].remaining > 0)
            {
                if (shortest == -1 || arr[i].remaining < arr[shortest].remaining)
                {
                    shortest = i;
                }
            }
        }

        if (shortest == -1)
        {
            time++; // CPU idle if no process available
        }
        else
        {
            arr[shortest].remaining--;
            time++;

            // Process completes when remaining time reaches 0
            if (arr[shortest].remaining == 0)
            {
                completed++;
                arr[shortest].ct = time;
                arr[shortest].tat = arr[shortest].ct - arr[shortest].arrival;
                arr[shortest].wt = arr[shortest].tat - arr[shortest].burst;
                AvgTAT += arr[shortest].tat;
                AvgWT += arr[shortest].wt;

                // Print process details upon completion
                printf("%5d\t%16d\t%7d\t%17d\t%17d\t%16d\n",
                       arr[shortest].process, arr[shortest].arrival, arr[shortest].burst,
                       arr[shortest].ct, arr[shortest].tat, arr[shortest].wt);
            }
        }
    }

    // Calculate and display averages
    printf("Average Turn Around Time: %.2f\nAverage Waiting Time: %.2f\n", AvgTAT / n, AvgWT / n);
}

// Sorts processes by arrival time using bubble sort
int sort(srtf arr[], int n)
{
    int i, j;
    srtf temp;

    for (i = 0; i < n - 1; i++)
    {
        for (j = 0; j < n - i - 1; j++)
        {
            if (arr[j].arrival > arr[j + 1].arrival)
            {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
    return 0;
}
