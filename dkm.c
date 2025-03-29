#include <vxWorks.h>
#include <taskLib.h>
#include <tickLib.h>
#include <taskHookLib.h>    
#include <stdio.h>
#include <stdlib.h>

#define RUN      32
#define ARR_SIZE 100000
#define MAX_TASKS 4

// Structure to track per-task CPU time and interruption count
typedef struct {
    TASK_ID taskId;
    ULONG totalCpuTicks;   // Accumulated CPU time in ticks
    ULONG lastStartTick;   // Tick count when the task was last switched in
    unsigned int preemptCount; // Number of times the task was interrupted 
} TaskCpuInfo;

// Global variables to track CPU time for tasks.
TaskCpuInfo taskCpuInfos[MAX_TASKS];
int taskCpuInfoCount = 0;

// Add task to time track array
void addTaskCpuInfo(TASK_ID tid) {
    if (taskCpuInfoCount < MAX_TASKS) {
        taskCpuInfos[taskCpuInfoCount].taskId = tid;
        taskCpuInfos[taskCpuInfoCount].totalCpuTicks = 0;
        taskCpuInfos[taskCpuInfoCount].lastStartTick = tickGet();  
        taskCpuInfos[taskCpuInfoCount].preemptCount = 0;           
        taskCpuInfoCount++;
    }
}

// Find the tracking structure for a given task.
TaskCpuInfo* findTaskCpuInfo(TASK_ID tid) {
    for (int i = 0; i < taskCpuInfoCount; i++) {
        if (taskCpuInfos[i].taskId == tid) {
            return &taskCpuInfos[i];
        }
    }
    return NULL;
}

// Task switch hook
void myTaskSwitchHook(TASK_ID oldTask, TASK_ID newTask) {
    ULONG now = tickGet();
    TaskCpuInfo *info;

    // When a task is switched update time and interupption
    if (oldTask != NULL) {
        info = findTaskCpuInfo(oldTask);
        if (info != NULL) {
            info->totalCpuTicks += now - info->lastStartTick;
            info->preemptCount++;  
        }
    }
    // When a task is switched in record new time
    if (newTask != NULL) {
        info = findTaskCpuInfo(newTask);
        if (info != NULL) {
            info->lastStartTick = now;
        }
    }
}

// BUBBLE SORT
//Wikipedia contributors. (n.d.). Bubble sort. In Wikipedia, The Free Encyclopedia. Retrieved March 27, 2025, from https://en.wikipedia.org/wiki/Bubble_sort
void bubble_sort_task() {
    addTaskCpuInfo(taskIdSelf());

    int *arr = malloc(ARR_SIZE * sizeof(int));
    if (arr == NULL) {
        printf("Memory error in bubble_sort\n");
        return;
    }
    
    for (int i = 0; i < ARR_SIZE; i++) {
        arr[i] = rand() % 1000;
    }

    for (int i = 0; i < ARR_SIZE - 1; i++) {
        for (int j = 0; j < ARR_SIZE - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int tmp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = tmp;
            }
        }
    }
    
    printf("Bubble sort completed.\n");

    TaskCpuInfo *info = findTaskCpuInfo(taskIdSelf());
    if (info != NULL) {
        printf("Bubble sort task CPU time: %lu ticks (~%lu ms), Preemptions: %u\n",
               info->totalCpuTicks, info->totalCpuTicks * 10, info->preemptCount);
    }
    
    free(arr);
}
// INSERTION SORT
// Wikipedia contributors. (n.d.). Insertion sort. In Wikipedia, The Free Encyclopedia. Retrieved March 27, 2025, from https://en.wikipedia.org/wiki/Insertion_sort
void insertion_sort_task() {
    addTaskCpuInfo(taskIdSelf());

    int *arr = malloc(ARR_SIZE * sizeof(int));
    if (arr == NULL) {
        printf("Memory error in insertion_sort\n");
        return;
    }
    
    for (int i = 0; i < ARR_SIZE; i++) {
        arr[i] = rand() % 1000;
    }
    
    // Perform insertion sort.
    for (int i = 1; i < ARR_SIZE; i++) {
        int key = arr[i];
        int j = i - 1;
        while ((j >= 0) && (arr[j] > key)) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
    
    printf("Insertion sort completed.\n");
    
    TaskCpuInfo *info = findTaskCpuInfo(taskIdSelf());
    if (info != NULL) {
        printf("Insertion sort task CPU time: %lu ticks (~%lu ms), Preemptions: %u\n",
               info->totalCpuTicks, info->totalCpuTicks * 10, info->preemptCount);
    }
    
    free(arr);
}

// RADIX SORT
// Cormen, T. H., Leiserson, C. E., Rivest, R. L., & Stein, C. (2022). Introduction to Algorithms (4th ed., pp. 219–224). The MIT Press.
void count_sort(int *arr, int n, int exp) {
    int output[n];
    int count[10] = {0};
    
    for (int i = 0; i < n; i++) {
        int index = (arr[i] / exp) % 10;
        count[index]++;
    }
    
    for (int i = 1; i < 10; i++) {
        count[i] = count[i] + count[i - 1];
    }
 
    for (int i = n - 1; i >= 0; i--) {
        int index = (arr[i] / exp) % 10;
        output[count[index] - 1] = arr[i];
        count[index]--;
    }
    
    for (int i = 0; i < n; i++) {
        arr[i] = output[i];
    }
}

void radix_sort_task() {
    addTaskCpuInfo(taskIdSelf());

    int *arr = malloc(ARR_SIZE * sizeof(int));
    if (arr == NULL) {
        printf("Memory error in radix_sort\n");
        return;
    }
    
    for (int i = 0; i < ARR_SIZE; i++) {
        arr[i] = rand() % 1000;
    }
    
    int max = arr[0];
    for (int i = 1; i < ARR_SIZE; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    
    int exp = 1;
    while ((max / exp) > 0) {
        count_sort(arr, ARR_SIZE, exp);
        exp = exp * 10;
    }
    
    printf("Radix sort completed.\n");
    
    TaskCpuInfo *info = findTaskCpuInfo(taskIdSelf());
    if (info != NULL) {
        printf("Radix sort task CPU time: %lu ticks (~%lu ms), Preemptions: %u\n",
               info->totalCpuTicks, info->totalCpuTicks * 10, info->preemptCount);
    }
    
    free(arr);
}

// TIMSORT
//Wikipedia contributors. (n.d.). Timsort. In Wikipedia, The Free Encyclopedia. Retrieved March 27, 2025, from https://en.wikipedia.org/wiki/Timsort
void merge(int *arr, int l, int m, int r) 
void insertion_sort_range(int *arr, int left, int right) {
    for (int i = left + 1; i <= right; i++) {
        int key = arr[i];
        int j = i - 1;
        while ((j >= left) && (arr[j] > key)) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void merge(int *arr, int l, int m, int r) {
    int len1 = m - l + 1;
    int len2 = r - m;
    
    int left[len1];
    int right[len2];
    
    for (int i = 0; i < len1; i++) {
        left[i] = arr[l + i];
    }
    for (int i = 0; i < len2; i++) {
        right[i] = arr[m + 1 + i];
    }
    
    int i = 0;
    int j = 0;
    int k = l;
    
    while ((i < len1) && (j < len2)) {
        if (left[i] <= right[j]) {
            arr[k] = left[i];
            i++;
        } else {
            arr[k] = right[j];
            j++;
        }
        k++;
    }
    
    while (i < len1) {
        arr[k] = left[i];
        i++;
        k++;
    }
    
    while (j < len2) {
        arr[k] = right[j];
        j++;
        k++;
    }
}

void tim_sort(int *arr, int n) {
    for (int i = 0; i < n; i += RUN) {
        int right;
        if ((i + RUN - 1) < (n - 1)) {
            right = i + RUN - 1;
        } else {
            right = n - 1;
        }
        insertion_sort_range(arr, i, right);
    }
    
    for (int size = RUN; size < n; size *= 2) {
        for (int left = 0; left < n; left += 2 * size) {
            int mid = left + size - 1;
            int right;
            if ((left + 2 * size - 1) < (n - 1)) {
                right = left + 2 * size - 1;
            } else {
                right = n - 1;
            }
            if (mid < right) {
                merge(arr, left, mid, right);
            }
        }
    }
}

void tim_sort_task() {
    addTaskCpuInfo(taskIdSelf());
    int *arr = malloc(ARR_SIZE * sizeof(int));
    if (arr == NULL) {
        printf("Memory error in tim_sort\n");
        return;
    }
    
    for (int i = 0; i < ARR_SIZE; i++) {
        arr[i] = rand() % 1000;
    }
    
    tim_sort(arr, ARR_SIZE);
    
    printf("Timsort completed.\n");

    TaskCpuInfo *info = findTaskCpuInfo(taskIdSelf());
    if (info != NULL) {
        printf("Timsort task CPU time: %lu ticks (~%lu ms), Preemptions: %u\n",
               info->totalCpuTicks, info->totalCpuTicks * 10, info->preemptCount);
    }
    
    free(arr);
}

void start(void) {
    printf("Starting sorting tasks\n");

    // Register the task switch hook.
    taskSwitchHookAdd((FUNCPTR)myTaskSwitchHook);

    taskSpawn("BubbleSortTask",     100, 0, 1048567, (FUNCPTR)bubble_sort_task,     0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
    taskSpawn("InsertionSortTask",   90,  0, 1048567, (FUNCPTR)insertion_sort_task,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
    taskSpawn("RadixSortTask",       80,  0, 1048567, (FUNCPTR)radix_sort_task,       0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
    taskSpawn("TimSortTask",         70,  0, 1048567, (FUNCPTR)tim_sort_task,         0, 0, 0, 0, 0, 0, 0, 0, 0, 0);

    printf("finished");
}
