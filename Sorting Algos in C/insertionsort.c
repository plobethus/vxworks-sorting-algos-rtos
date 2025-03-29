#include <stdio.h>
#include <stdlib.h>

#define ARR_SIZE 500000


void print_array(int *arr) {
    for (int i = 0; i < ARR_SIZE; i++)
        printf("%d ", arr[i]);
    printf("\n");
}
//INSERTIONSORT 
// Wikipedia contributors. (n.d.). Insertion sort. In Wikipedia, The Free Encyclopedia. Retrieved March 27, 2025, from https://en.wikipedia.org/wiki/Insertion_sort

void insertion_sort_task() {
    int *arr = malloc(ARR_SIZE * sizeof(int));
    if (!arr) {
        printf("Memory error in insertion_sort\n");
        return;
    }

    for (int i = 0; i < ARR_SIZE; i++) {
        arr[i] = rand() % 1000;
    }
    //print_array(arr);
    printf("array initialized");

    for (int i = 1; i < ARR_SIZE; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
        //print_array(arr);
    }

    printf("Insertion sort completed.\n");
    //print_array(arr);
    free(arr);
}

int main(){
    insertion_sort_task();
    return 0;
}