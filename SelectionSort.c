#include<stdio.h>

void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

void selectionsort(int arr[], int n){
    for(int i=0; i<n; i++){
        int min_idx = i;
        for(int j=i+1; j<n; j++){
            if(arr[j]<arr[min_idx]){
                min_idx=j;
            }
        }
        swap(&arr[min_idx], &arr[i]);
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

    selectionsort(arr, n);

    printf("Sorted array: ");
    for(int i=0; i<n; i++){
        printf("%d\t", arr[i]);
    }
}