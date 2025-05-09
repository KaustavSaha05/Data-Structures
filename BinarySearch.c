#include <stdio.h>

// Function to perform binary search
int binarySearch(int arr[], int left, int right, int x) {
    while (left <= right) {
        int mid = left + (right - left) / 2;

        // Check if x is present at mid
        if (arr[mid] == x)
            return mid;

        // If x is greater, ignore the left half
        if (arr[mid] < x)
            left = mid + 1;

        // If x is smaller, ignore the right half
        else
            right = mid - 1;
    }

    // If the element is not present in the array
    return -1;
}

// Function to print the array
void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

// Main function to test binary search with user input
int main() {
    int n, x;

    printf("Enter the number of elements: ");
    scanf("%d", &n);

    int arr[n];

    printf("Enter the elements of the sorted array:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    printf("Enter the element to search for: ");
    scanf("%d", &x);

    printf("Array: ");
    printArray(arr, n);

    int result = binarySearch(arr, 0, n - 1, x);

    if (result != -1) {
        printf("Element found at index %d\n", result);
    } else {
        printf("Element not found in the array\n");
    }

    return 0;
}
