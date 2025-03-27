#include <stdio.h>
#include <stdlib.h>

//#define RUN 32 only needed in radix sort
#define ARR_SIZE 1000 


void print_array(int *arr) {
    for (int i = 0; i < ARR_SIZE; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

// RADIXSORT
// Cormen, T. H., Leiserson, C. E., Rivest, R. L., & Stein, C. (2022). Introduction to Algorithms (4th ed., pp. 219–224). The MIT Press.
void count_sort(int *arr, int n, int exp) {
    int output[n];
    int count[10] = {0};

    for (int i = 0; i < n; i++) {
        count[(arr[i] / exp) % 10]++;
    }

    for (int i = 1; i < 10; i++) {
        count[i] += count[i - 1];
    }

    for (int i = n - 1; i >= 0; i--) {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }

    for (int i = 0; i < n; i++) {
        arr[i] = output[i];
    }
    print_array(arr);
}

void radix_sort_task() {
    int *arr = malloc(ARR_SIZE * sizeof(int));
    if (!arr) {
        printf("Memory error in radix_sort\n");
        return;
    }

    for (int i = 0; i < ARR_SIZE; i++) {
        arr[i] = rand() % 1000;
        print_array(arr);
    }

    int max = arr[0];
    for (int i = 1; i < ARR_SIZE; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
        print_array(arr);
    }

    for (int exp = 1; max / exp > 0; exp *= 10) {
        count_sort(arr, ARR_SIZE, exp);
    }

    printf("Radix sort completed.\n");
    free(arr);
}

int main(){
    radix_sort_task();
    return 0;
}