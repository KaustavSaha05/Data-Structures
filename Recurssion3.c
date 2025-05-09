//Palindrome Check:

#include <stdio.h>
#include <ctype.h>
#include <string.h>

int isPalindrome(char str[], int start, int end){
    if(start >= end){
        return 1;
    }
    if(str[start] != str[end]){
        return 0;
    }
    return isPalindrome(str, start+1, end-1);
}

void process(char str[], char processed[]){
    int j=0;
    for(int i=0; i<strlen(str); i++){
        if(isalnum(str[i])){
            processed[j++] = tolower(str[i]);
        }
    }
    processed[j]='\0';
}

int main(){
    char str[100];
    char processed[100];
    
    printf("Enter string: ");
    fgets(str, sizeof(str), stdin);
    str[strcspn(str, "\n")] = '\0';

    process(str, processed);
    int length=strlen(processed);

    if(isPalindrome(processed, 0, length-1)){
        printf("Palindrome String\n");
    }
    else{
        printf("Not a palindrome string\n");
    }

    return 0;
}