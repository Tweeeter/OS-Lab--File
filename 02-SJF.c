#include <stdio.h>

typedef struct sjf
{
    int process; // Process Number
    int burst;   // Burst Time
    int arrival; // Arrival Time
    int tat;     // Turn Around Time
    int wt;      // Waiting Time
    int ct;      // Completion Time
} sjf;

int sort(sjf[], int);

int main()
{
    int n, i, j, temp = 0, min;
    float AvgTAT = 0, AvgWT = 0;

    printf("Enter Number of Processes: ");
    scanf("%d", &n);
    sjf arr[n]; // Array of type sjf

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

    // SJF Scheduling Logic
    for (i = 0; i < n; i++)
    {
        min = i;
        for (j = i + 1; j < n; j++)
        {
            if (arr[j].arrival <= temp && arr[j].burst < arr[min].burst)
                min = j;
        }

        sjf k = arr[i];
        arr[i] = arr[min];
        arr[min] = k;

        if (arr[i].arrival > temp)
            temp = arr[i].arrival;

        temp += arr[i].burst;
        arr[i].ct = temp;
    }

    printf("Process No\t Arrival Time\t Burst Time\t Completion Time\t Turn Around Time\t Waiting Time\n");
    for (i = 0; i < n; i++)
    {
        arr[i].tat = arr[i].ct - arr[i].arrival;
        arr[i].wt = arr[i].tat - arr[i].burst;
        AvgTAT += arr[i].tat;
        AvgWT += arr[i].wt;
        printf("%5d\t%16d\t%7d\t%17d\t%17d\t%16d\n",
               arr[i].process, arr[i].arrival, arr[i].burst,
               arr[i].ct, arr[i].tat, arr[i].wt);
    }

    printf("Average Turn Around Time: %.2f\nAverage Waiting Time: %.2f\n", AvgTAT / n, AvgWT / n);
    return 0;
}

// Bubble Sort (by arrival time)
int sort(sjf arr[], int n)
{
    int i, j;
    sjf k;

    for (i = 0; i < n - 1; i++)
    {
        for (j = 0; j < n - i - 1; j++)
        {
            if (arr[j].arrival > arr[j + 1].arrival)
            {
                k = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = k;
            }
        }
    }
    return 0;
}
