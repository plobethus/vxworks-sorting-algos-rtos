#include <stdio.h>
#include <stdlib.h>

#define RUN 32
#define ARR_SIZE 1000


void print_array(int *arr) {
    for (int i = 0; i < ARR_SIZE; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

void insertion_sort_range(int *arr, int left, int right) {
    printf("insertion sort\n");
    for (int i = left + 1; i <= right; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= left && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
    //print_array(arr);
}
//TIMSORT
//Wikipedia contributors. (n.d.). Timsort. In Wikipedia, The Free Encyclopedia. Retrieved March 27, 2025, from https://en.wikipedia.org/wiki/Timsort
void merge(int *arr, int l, int m, int r) {
    printf("merge\n");
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

    while (i < len1 && j < len2) {
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
    //print_array(arr);
}

void tim_sort(int *arr, int n) {
    printf("timsort\n");
    for (int i = 0; i < n; i += RUN) {
        int right = (i + RUN - 1 < n - 1) ? (i + RUN - 1) : (n - 1);
        insertion_sort_range(arr, i, right);
    }

    for (int size = RUN; size < n; size *= 2) {
        for (int left = 0; left < n; left += 2 * size) {
            int mid = left + size - 1;
            int right = (left + 2 * size - 1 < n - 1) ? (left + 2 * size - 1) : (n - 1);
            if (mid < right) {
                merge(arr, left, mid, right);
            }
        }
    }
    //print_array(arr);
}

void tim_sort_task() {
    int *arr = malloc(ARR_SIZE * sizeof(int));
    if (!arr) {
        printf("Memory error in tim_sort\n");
        return;
    }

    for (int i = 0; i < ARR_SIZE; i++) {
        arr[i] = rand() % 1000;
    }
    printf("Aray initialized to: ");
    print_array(arr);

    tim_sort(arr, ARR_SIZE);
    printf("Timsort completed.\n");
    free(arr);
    //print_array(arr);
}

int main(){
    tim_sort_task();   
    

    return 0;
}
