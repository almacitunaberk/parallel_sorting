#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <omp.h>

#define TASK_SIZE 100

void randomly_initialize_array(int array[], size_t  size);
int partition(int array[], int low, int high);
void quick_sort(int array[], int low, int high);

int main() {
    srand(time(0));
    int array_to_be_sorted[10];
    size_t array_size = sizeof(array_to_be_sorted) / sizeof(array_to_be_sorted[0]);
    randomly_initialize_array(array_to_be_sorted, array_size);
    printf("Array to be sorted: \n");
    int i;
    for(i=0; i<array_size; i++) {
        printf("%d ", array_to_be_sorted[i]);
    }
    struct timeval stop, start;
    gettimeofday(&start, NULL);
    omp_set_nested(1);
    omp_set_dynamic(0);
    #pragma omp parallel num_threads(4)
    {
        #pragma omp single
        quick_sort(array_to_be_sorted, 0, array_size-1);
    }
    gettimeofday(&stop, NULL);
    printf("\n Array after sorting: \n");
    for(i=0; i<array_size; i++) {
        printf("%d ", array_to_be_sorted[i]);
    }
    printf("Time elapsed: %lu", (stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec);
}

void randomly_initialize_array(int array[], size_t size) {
    int i;
    for (i = 0; i < size; i++) {
        array[i] = rand() % 100;
    }
}

void quick_sort(int array[], int low, int high) {
    if (low < high) {
        int pivot = partition(array, low, high);
        #pragma omp task shared(array) if (pivot - low > TASK_SIZE)
        quick_sort(array, low, pivot-1);
        #pragma omp task shared(array) if (high - pivot > TASK_SIZE)
        quick_sort(array, pivot+1, high);
    }
}

int partition(int array[], int low, int high) {
    int pivot = array[high];
    int i = low - 1;
    int j;
    for(j=low; j<=high-1; j++) {
        if (array[j] < pivot) {
            i++;
            int temp = array[j];
            array[j] = array[i];
            array[i] = temp;
        }
    }
    int temp = array[i+1];
    array[i+1] = array[high];
    array[high] = temp;
    return i+1;
}