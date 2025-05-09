#include <stdio.h>
#include<math.h>
#include <stdlib.h>

// Structure for a polynomial term
struct Term {
    int coeff;              // Coefficient
    int exp;                // Exponent
    struct Term* next;      // Pointer to the next term
};

// Function to create a new term
struct Term* createTerm(int coeff, int exp) {
    struct Term* newTerm = (struct Term*)malloc(sizeof(struct Term));
    newTerm->coeff = coeff;
    newTerm->exp = exp;
    newTerm->next = NULL;
    return newTerm;
}

// Function to insert a new term into the polynomial in the correct position (sorted by exponent)
void insertTerm(struct Term** poly, int coeff, int exp) {
    struct Term* newTerm = createTerm(coeff, exp);
    
    // If the list is empty or the new term has a higher exponent than the first term
    if (*poly == NULL || (*poly)->exp < exp) {
        newTerm->next = *poly;
        *poly = newTerm;
    } else {
        struct Term* temp = *poly;
        
        // Traverse to find the correct position for insertion
        while (temp->next != NULL && temp->next->exp > exp) {
            temp = temp->next;
        }
        
        // If a term with the same exponent exists, add the coefficients
        if (temp->next != NULL && temp->next->exp == exp) {
            temp->next->coeff += coeff;
            free(newTerm);
        } else {
            newTerm->next = temp->next;
            temp->next = newTerm;
        }
    }
}

// Function to create a polynomial from user input
void createPolynomial(struct Term** poly) {
    int n, coeff, exp;
    printf("Enter the number of terms in the polynomial: ");
    scanf("%d", &n);
    
    for (int i = 0; i < n; i++) {
        printf("Enter coefficient and exponent of term %d: ", i + 1);
        scanf("%d %d", &coeff, &exp);
        insertTerm(poly, coeff, exp);
    }
}

// Function to display a polynomial
void displayPolynomial(struct Term* poly) {
    struct Term* temp = poly;
    while (temp != NULL) {
        printf("%dx^%d", temp->coeff, temp->exp);
        if (temp->next != NULL && temp->next->coeff > 0) {
            printf(" + ");
        }
        temp = temp->next;
    }
    printf("\n");
}

// Function to add two polynomials
struct Term* addPolynomials(struct Term* poly1, struct Term* poly2) {
    struct Term* result = NULL;

    while (poly1 != NULL && poly2 != NULL) {
        if (poly1->exp == poly2->exp) {
            insertTerm(&result, poly1->coeff + poly2->coeff, poly1->exp);
            poly1 = poly1->next;
            poly2 = poly2->next;
        } else if (poly1->exp > poly2->exp) {
            insertTerm(&result, poly1->coeff, poly1->exp);
            poly1 = poly1->next;
        } else {
            insertTerm(&result, poly2->coeff, poly2->exp);
            poly2 = poly2->next;
        }
    }

    // Add remaining terms of poly1 or poly2
    while (poly1 != NULL) {
        insertTerm(&result, poly1->coeff, poly1->exp);
        poly1 = poly1->next;
    }

    while (poly2 != NULL) {
        insertTerm(&result, poly2->coeff, poly2->exp);
        poly2 = poly2->next;
    }

    return result;
}

// Function to multiply two polynomials
struct Term* multiplyPolynomials(struct Term* poly1, struct Term* poly2) {
    struct Term* result = NULL;
    
    // Multiply each term of poly1 with each term of poly2
    struct Term* temp1 = poly1;
    while (temp1 != NULL) {
        struct Term* temp2 = poly2;
        while (temp2 != NULL) {
            int coeff = temp1->coeff * temp2->coeff;
            int exp = temp1->exp + temp2->exp;
            insertTerm(&result, coeff, exp);
            temp2 = temp2->next;
        }
        temp1 = temp1->next;
    }
    
    return result;
}

// Function to evaluate a polynomial for a given value of x
int evaluatePolynomial(struct Term* poly, int x) {
    int result = 0;
    struct Term* temp = poly;

    while (temp != NULL) {
        result += temp->coeff * pow(x, temp->exp);
        temp = temp->next;
    }

    return result;
}

int main() {
    struct Term* poly1 = NULL;
    struct Term* poly2 = NULL;
    struct Term* sum = NULL;
    struct Term* product = NULL;
    int x;

    printf("Creating first polynomial:\n");
    createPolynomial(&poly1);
    printf("First Polynomial: ");
    displayPolynomial(poly1);

    printf("Creating second polynomial:\n");
    createPolynomial(&poly2);
    printf("Second Polynomial: ");
    displayPolynomial(poly2);

    // Addition
    sum = addPolynomials(poly1, poly2);
    printf("Sum of Polynomials: ");
    displayPolynomial(sum);

    // Multiplication
    product = multiplyPolynomials(poly1, poly2);
    printf("Product of Polynomials: ");
    displayPolynomial(product);

    // Evaluation
    printf("Enter the value of x for evaluation: ");
    scanf("%d", &x);
    printf("Evaluation of first polynomial at x = %d: %d\n", x, evaluatePolynomial(poly1, x));

    return 0;
}
