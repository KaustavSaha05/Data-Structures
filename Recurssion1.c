//Array Sum:

#include<stdio.h>

int arraySum(int arr[], int n){
    if(n<=0){
        return 0;
    }
    return arr[n-1]+arraySum(arr, n-1);
}

int main(){
    int n;
    printf("Enter array size: ");
    scanf("%d", &n);

    int arr[n];
    printf("Enter array elements: ");
    for(int i=0; i<n; i++){
        scanf("%d", &arr[i]);
    }

    printf("Array: ");
    for(int i=0; i<n; i++){
        printf("%d \n", arr[i]);
    }

    int sum = arraySum(arr, n);
    printf("The sum of elements in the array is: %d", sum);

    return 0;
}