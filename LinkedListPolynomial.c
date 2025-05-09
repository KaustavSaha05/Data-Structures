#include <stdio.h>
#include <stdlib.h>

struct Node {
    int coeff;
    int exp;
    struct Node* next;
};

void create_node(int coeff, int exp, struct Node** head) {
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    new_node->coeff = coeff;
    new_node->exp = exp;
    new_node->next = *head;
    *head = new_node;
}

void add_polynomials(struct Node* poly1, struct Node* poly2, struct Node** result) {
    while (poly1 != NULL && poly2 != NULL) {
        if (poly1->exp > poly2->exp) {
            create_node(poly1->coeff, poly1->exp, result);
            poly1 = poly1->next;
        } else if (poly1->exp < poly2->exp) {
            create_node(poly2->coeff, poly2->exp, result);
            poly2 = poly2->next;
        } else {
            create_node(poly1->coeff + poly2->coeff, poly1->exp, result);
            poly1 = poly1->next;
            poly2 = poly2->next;
        }
    }

    while (poly1 != NULL) {
        create_node(poly1->coeff, poly1->exp, result);
        poly1 = poly1->next;
    }

    while (poly2 != NULL) {
        create_node(poly2->coeff, poly2->exp, result);
        poly2 = poly2->next;
    }
}

void display_polynomial(struct Node* poly) {
    while (poly != NULL) {
        printf("%dx^%d", poly->coeff, poly->exp);
        poly = poly->next;
        if (poly != NULL) {
            printf(" + ");
        }
    }
    printf("\n");
}

int main() {
    struct Node* poly1 = NULL;
    struct Node* poly2 = NULL;
    struct Node* result = NULL;

    create_node(5, 2, &poly1);
    create_node(4, 1, &poly1);
    create_node(2, 0, &poly1);

    create_node(-5, 1, &poly2);
    create_node(-5, 0, &poly2);

    printf("1st Polynomial: ");
    display_polynomial(poly1);

    printf("2nd Polynomial: ");
    display_polynomial(poly2);

    add_polynomials(poly1, poly2, &result);

    printf("Resultant Polynomial: ");
    display_polynomial(result);

    return 0;
}
