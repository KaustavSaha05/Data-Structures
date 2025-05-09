#include<stdio.h>

void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

void bubblesort(int arr[], int n){
    for(int i=0; i<n-1; i++){
        for(int j=0; j<n-i-1; j++){
            if(arr[j] > arr[j+1]){
                swap(&arr[j], &arr[j+1]);
            }
        }
    }
}

int main(){
    int n;
    printf("Enter size of array: ");
    scanf("%d", &n);
    int arr[n];
    for(int i=0; i<n; i++){
        printf("Enter element: ");
        scanf("%d", &arr[i]);
    }

    printf("Original array: ");
    for(int i=0; i<n; i++){
        printf("%d\t", arr[i]);
    }
    printf("\n");

    bubblesort(arr, n);

    printf("Sorted array: ");
    for(int i=0; i<n; i++){
        printf("%d\t", arr[i]);
    }
}