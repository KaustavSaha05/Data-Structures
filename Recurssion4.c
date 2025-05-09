//Power Function:

#include<stdio.h>

int power(int base, int exponent){
    if(exponent==0){
        return 1;
    }
    if(exponent==1){
        return base;
    }
    if(exponent<0){
        return 1/power(base, -exponent);
    }
    return base * power(base, exponent-1);
}

int main(){
    int base, exponent;
    printf("Enter base: ");
    scanf("%d", &base);
    printf("Enter power: ");
    scanf("%d", &exponent);

    int result = power(base, exponent);
    printf("The result is: %d", result);

    return 0;
}