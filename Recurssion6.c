#include <stdio.h>
#include <string.h>

// Function to swap characters at position i and j in the string
void swap(char *x, char *y) {
    char temp;
    temp = *x;
    *x = *y;
    *y = temp;
}

// Recursive function to generate all permutations of the string
void permute(char *str, int l, int r) {
    int i;
    if (l == r){
        printf("%s\n", str);
    } 
    
    else{
        for (i = l; i <= r; i++){
            swap((str + l), (str + i));    // Swap the current element with the element at the current index
            permute(str, l + 1, r);        // Recursively call permute for the next level
            swap((str + l), (str + i));    // Backtrack to restore the original string
        }
    }
}

int main() {
    char str[] = "abc";   // Input string
    int n = strlen(str);
    permute(str, 0, n - 1);  // Call the permutation function
    return 0;
}
