#include <stdio.h>
#include <stdlib.h>

//#define RUN 32 only needed in bubble sort
#define ARR_SIZE 10


void print_array(int *arr) {
    for (int i = 0; i < ARR_SIZE; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

//BUBBLESORT
//Wikipedia contributors. (n.d.). Timsort. In Wikipedia, The Free Encyclopedia. Retrieved March 27, 2025, from https://en.wikipedia.org/wiki/Bubble_sort
void bubble_sort_task() {
    int *arr = malloc(ARR_SIZE * sizeof(int));
    if (!arr) {
        printf("Memory error in bubble_sort\n");
        return;
    }

    for (int i = 0; i < ARR_SIZE; i++) {
        arr[i] = rand() % 10;
    }
    print_array(arr);

    for (int i = 0; i < ARR_SIZE - 1; i++) {
        for (int j = 0; j < ARR_SIZE - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int tmp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = tmp;
            }
            print_array(arr);
        }
    }

    printf("Bubble sort completed.\n");
    print_array(arr);
    free(arr);
}

int main(){
    bubble_sort_task();
    return 0;
}