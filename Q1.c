#include <stdio.h>
#include <stdlib.h>
void swap(int *a, int *b);
void rearrangeIterative(int arr[], int size);
void rearrangeRecursive(int arr[], int left, int right);

int main() {
    int arr[] = {12, 17, 70, 15, 22, 65, 21, 90};
    int size = sizeof(arr) / sizeof(arr[0]);

    rearrangeIterative(arr, size);

    printf("Rearranged array: \n");
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}


void rearrangeIterative(int arr[], int size) {
    int left = 0;
    int right = size - 1;
    
    while (left < right) {

        while (left < right && arr[left] % 2 != 0) {
            left++;
        }

        while (left < right && arr[right] % 2 == 0) {
            right--;
        }

        if (left < right) {
            swap(&arr[left], &arr[right]);
            left++;
            right--;
        }
    }
}

void rearrangeRecursive(int arr[], int left, int right) {

    if (left >= right) {
        return;
    }
    
    while (left < right && arr[left] % 2 != 0) {
        left++;
    }
    
    while (left < right && arr[right] % 2 == 0) {
        right--;
    }
    
    if (left < right) {
        swap(&arr[left], &arr[right]);
        rearrangeRecursive(arr, left + 1, right - 1);
    }
}