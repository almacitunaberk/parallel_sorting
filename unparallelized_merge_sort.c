#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void randomly_initialize_array(int array[], size_t  size);
void merge(int array[], int left, int middle, int right);
void merge_sort(int array[], int left, int right);


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
    merge_sort(array_to_be_sorted, 0, array_size-1);
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

void merge(int array[], int left, int middle, int right) {
    int i,j,k;
    int n1 = middle - left + 1;
    int n2 = right - middle;
    int temp_left[n1], temp_right[n2];
    for(i=0; i<n1; i++) {
        temp_left[i] = array[left + i];
    }
    for(j=0; j<n2; j++) {
        temp_right[j] = array[middle + 1 + j];
    }
    i = 0;
    j = 0;
    k = left;
    while(i < n1 && j < n2) {
        if (temp_left[i] <= temp_right[j]) {
            array[k] = temp_left[i];
            i++;
        } else {
            array[k] = temp_right[j];
            j++;
        }
        k++;
    }

    while(i < n1) {
        array[k] = temp_left[i];
        i++;
        k++;
    }

    while(j < n2) {
        array[k] = temp_right[j];
        j++;
        k++;
    }
}

void merge_sort(int array[], int left, int right) {
    if (left < right) {
        int middle = left + (right - left) / 2;
        merge_sort(array, left, middle);
        merge_sort(array, middle+1, right);
        merge(array, left, middle, right);
    }
}